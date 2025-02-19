#include "xparameters.h"      // Contains definitions for device IDs, memory map
#include "xaxidma.h"          // AXI DMA driver
#include "xil_printf.h"       // For xil_printf
#include "xil_cache.h"        // For cache flush/invalidate

/**************************************************** 
 * Adjust these definitions based on your system
 ****************************************************/
#define DMA_DEV_ID          XPAR_AXI_DMA_0_BASEADDR  // AXI DMA device ID
#define DDR_BASE_ADDR       XPAR_PS7_DDR_0_BASEADDRESS
#define MEM_BASE_ADDR       (DDR_BASE_ADDR + 0x1000000)

// We’ll define transmit and receive buffer regions with some offset.
// Make sure these addresses do not overlap with other system uses.
#define TX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00300000)

// Number of bytes to transfer
#define MAX_PKT_LEN         256

// Return codes
#define TEST_SUCCESS        0
#define TEST_FAILURE        1


int main(void)
{
    XAxiDma AxiDma;
    XAxiDma_Config *CfgPtr;
    int Status;
    int i;

    // Pointers to Tx and Rx buffers
    u8 *TxBufferPtr = (u8 *)TX_BUFFER_BASE;
    u8 *RxBufferPtr = (u8 *)RX_BUFFER_BASE;

    xil_printf("\r\n--- Entering DMA Test Application ---\r\n");

    /****************************************
     * 1. Initialize the DMA driver
     ****************************************/
    CfgPtr = XAxiDma_LookupConfig(DMA_DEV_ID);
    if (!CfgPtr) {
        xil_printf("ERROR: No DMA config found for device id %d\r\n", DMA_DEV_ID);
        return TEST_FAILURE;
    }

    Status = XAxiDma_CfgInitialize(&AxiDma, CfgPtr);
    if (Status != XST_SUCCESS) {
        xil_printf("ERROR: DMA CfgInitialize failed with %d\r\n", Status);
        return TEST_FAILURE;
    }

    // Check if the DMA engine is in Scatter-Gather mode
    if (XAxiDma_HasSg(&AxiDma)) {
        xil_printf("ERROR: DMA configured in SG mode. This example is for Simple mode.\r\n");
        return TEST_FAILURE;
    }

    /****************************************
     * 2. Prepare Tx and Rx Buffers
     ****************************************/
    // Invalidate cache before we write data (avoid stale data).
    Xil_DCacheInvalidateRange((UINTPTR)TxBufferPtr, MAX_PKT_LEN);
    Xil_DCacheInvalidateRange((UINTPTR)RxBufferPtr, MAX_PKT_LEN);

    // Fill the Tx buffer with known pattern; clear Rx buffer
    for (i = 0; i < MAX_PKT_LEN; i++) {
        TxBufferPtr[i] = (u8)(i & 0xFF);  // Simple pattern
        RxBufferPtr[i] = 0;
    }

    // Flush caches so the DMA sees our updated data
    Xil_DCacheFlushRange((UINTPTR)TxBufferPtr, MAX_PKT_LEN);
    Xil_DCacheFlushRange((UINTPTR)RxBufferPtr, MAX_PKT_LEN);

    /****************************************
     * 3. Set up and start DMA transfers
     ****************************************/
    // Setup the receive channel (PS side buffer)
    Status = XAxiDma_SimpleTransfer(
        &AxiDma,
        (UINTPTR)RxBufferPtr,
        MAX_PKT_LEN,
        XAXIDMA_DEVICE_TO_DMA
    );
    if (Status != XST_SUCCESS) {
        xil_printf("ERROR: RX transfer setup failed with %d\r\n", Status);
        return TEST_FAILURE;
    }

    // Setup the transmit channel (PL side buffer)
    Status = XAxiDma_SimpleTransfer(
        &AxiDma,
        (UINTPTR)TxBufferPtr,
        MAX_PKT_LEN,
        XAXIDMA_DMA_TO_DEVICE
    );
    if (Status != XST_SUCCESS) {
        xil_printf("ERROR: TX transfer setup failed with %d\r\n", Status);
        return TEST_FAILURE;
    }

    /****************************************
     * 4. Wait for DMA to complete
     ****************************************/
    // Poll the DMA status
    while (
        (XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA)) ||
        (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE))
    ) {
        // Wait/Do nothing. In a real application, you might want
        // to implement a timeout or check for errors.
    }

    // Invalidate Rx buffer cache so we can see the data written by DMA
    Xil_DCacheInvalidateRange((UINTPTR)RxBufferPtr, MAX_PKT_LEN);

    /****************************************
     * 5. Verify the data
     ****************************************/
    for (i = 0; i < MAX_PKT_LEN; i++) {
        if (RxBufferPtr[i] != (u8)(i & 0xFF)) {
            xil_printf("ERROR: Data mismatch at index %d: Rx = 0x%02X, Expected = 0x%02X\r\n",
                       i, RxBufferPtr[i], (u8)(i & 0xFF));
            return TEST_FAILURE;
        }
    }

    xil_printf("DMA Test PASSED! Data transferred correctly.\r\n");
    return TEST_SUCCESS;
}

