#include "xparameters.h"
#include "xil_io.h"  // for Xil_In32/Xil_Out32
#include "xil_printf.h" // for xil_printf

#define BRAM0_BASE XPAR_AXI_BRAM_CTRL_0_BASEADDR // Source BRAM base
#define BRAM1_BASE XPAR_AXI_BRAM_CTRL_1_BASEADDR  // Destination BRAM base
#define DMA_BASE   XPAR_DMA_COPY_0_BASEADDR // DMA control base

#define DMA_SRC_REG    (DMA_BASE + 0x10)  // Source address low 32 bits
#define DMA_SRC_REG_H  (DMA_BASE + 0x14)  // Source address high 32 bits
#define DMA_DST_REG    (DMA_BASE + 0x1C)  // Dest address low 32 bits
#define DMA_DST_REG_H  (DMA_BASE + 0x20)  // Dest address high 32 bits
#define DMA_LEN_REG    (DMA_BASE + 0x28)  // Length (number of words)
#define DMA_CTRL_REG   (DMA_BASE + 0x00)  // Control (ap_start, ap_done, etc.)

int main() {
    uint32_t length = 256;  // number of words to transfer
    for (uint32_t i = 0; i < length; ++i) {
        Xil_Out32(BRAM0_BASE + i*4, 0xABCD0000 | i);  // write a pattern
        // Alternatively: *((volatile uint32_t*)(BRAM0_BASE + i*4)) = some_value;
    }
    // Optional: clear destination BRAM
    for (uint32_t j = 0; j < length; ++j) {
        Xil_Out32(BRAM1_BASE + j*4, 0xDEADBEEF);  // fill dest with dummy data
    }


    // Write source address (low 32 bits; high 32 bits not needed for Zynq-7000)
    Xil_Out32(DMA_SRC_REG, BRAM0_BASE);
    Xil_Out32(DMA_SRC_REG_H, 0x0);        // high bits = 0
    // Write destination address
    Xil_Out32(DMA_DST_REG, BRAM1_BASE);
    Xil_Out32(DMA_DST_REG_H, 0x0);
    // Write length
    Xil_Out32(DMA_LEN_REG, length);
    // Start the DMA (ap_start = 1)
    Xil_Out32(DMA_CTRL_REG, 0x1);

    // Poll for completion
    uint32_t ctrl;
    do {
        ctrl = Xil_In32(DMA_CTRL_REG);
    } while ((ctrl & 0x2) == 0);  // wait until bit 1 (done) is set
    // Optionally, read and clear done
    Xil_In32(DMA_CTRL_REG); // reading it clears the done flag in some implementations


    int success = 1;
    for (uint32_t k = 0; k < length; ++k) {
        uint32_t src_val = Xil_In32(BRAM0_BASE + k*4);
        uint32_t dst_val = Xil_In32(BRAM1_BASE + k*4);
        if (src_val != dst_val) {
            xil_printf("Mismatch at index %d: src=0x%08X, dst=0x%08X\r\n", k, src_val, dst_val);
            success = 0;
            break;
        }
    }
    if (success) {
        xil_printf("DMA transfer completed successfully. %d words copied.\r\n", length);
    } else {
        xil_printf("DMA transfer failed.\r\n");
    }
    
    return 0;
}

