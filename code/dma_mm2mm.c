#include "xil_printf.h"
#include "xil_io.h"

// Define base addresses
#define DMA_BASE_ADDR 0x40400000
#define SRC_ADDR 0xC0000000      // DMA source address for BRAM0
#define DST_ADDR 0xC0000000      // DMA destination address for BRAM1
#define TRANSFER_LENGTH 1024     // Bytes to transfer

int main() {
    volatile u32 *dma_base = (volatile u32 *)DMA_BASE_ADDR;

    xil_printf("Starting DMA test\r\n");

    // Note: Cannot write to BRAM0 from PS; assume BRAM0 has pre-initialized data
    xil_printf("Assuming BRAM0 has known data at 0x%08X\r\n", SRC_ADDR);

    // Configure MM2S: Set source address and length
    dma_base[0x18/4] = SRC_ADDR; // MM2S_SA at offset 0x18
    dma_base[0x28/4] = TRANSFER_LENGTH; // MM2S_LENGTH at offset 0x28
    // Start MM2S: Set Run/Stop bit
    dma_base[0x00/4] |= 0x1; // MM2S_DMACR at offset 0x00, bit 0

    // Configure S2MM: Set destination address and length
    dma_base[0x48/4] = DST_ADDR; // S2MM_DA at offset 0x48
    dma_base[0x58/4] = TRANSFER_LENGTH; // S2MM_LENGTH at offset 0x58
    // Start S2MM: Set Run/Stop bit
    dma_base[0x30/4] |= 0x1; // S2MM_DMACR at offset 0x30, bit 0

    // Wait for MM2S to complete
    xil_printf("Waiting for MM2S to complete...\r\n");
    while (dma_base[0x04/4] & (1 << 12)) { // Check MM2S_DMASR busy bit
        xil_printf("MM2S busy...\r\n");
    }
    xil_printf("MM2S completed\r\n");

    // Wait for S2MM to complete
    xil_printf("Waiting for S2MM to complete...\r\n");
    while (dma_base[0x34/4] & (1 << 12)) { // Check S2MM_DMASR busy bit
        xil_printf("S2MM busy...\r\n");
    }
    xil_printf("S2MM completed\r\n");

    // Check for errors (example: halted or idle bits)
    u32 mm2s_status = dma_base[0x04/4];
    u32 s2mm_status = dma_base[0x34/4];
    if ((mm2s_status & 0x1) || (s2mm_status & 0x1)) {
        xil_printf("Error: DMA halted, MM2S status: 0x%08X, S2MM status: 0x%08X\r\n", mm2s_status, s2mm_status);
    } else {
        xil_printf("Transfer likely successful, no errors detected\n");
    }

    return 0;
}
