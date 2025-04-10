#include <stdint.h>
#define BURST_LEN 16  // example burst length (can tune as needed)

// Top-level HLS function for DMA
void dma_copy(volatile uint32_t *src, volatile uint32_t *dst, uint32_t length) {
#pragma HLS INTERFACE m_axi port=src  offset=slave bundle=AXI_SRC depth=1024
#pragma HLS INTERFACE m_axi port=dst  offset=slave bundle=AXI_DST depth=1024
#pragma HLS INTERFACE s_axilite port=src   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=dst   bundle=CTRL
#pragma HLS INTERFACE s_axilite port=length bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
//#pragma HLS PIPELINE II=1   // (optional) pipeline loop for better burst performance

    // Simple memory copy loop
    for (uint32_t i = 0; i < length; ++i) {
        uint32_t data = src[i];
        dst[i] = data;
    }
}

