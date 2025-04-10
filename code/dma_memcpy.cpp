#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void dma_memcpy(volatile uint32_t *src, volatile uint32_t *dst, uint32_t length) {
    #pragma HLS INTERFACE m_axi port=src   offset=slave bundle=GMEM depth=1024
    #pragma HLS INTERFACE m_axi port=dst   offset=slave bundle=GMEM depth=1024
    #pragma HLS INTERFACE s_axilite port=src   bundle=CONTROL
    #pragma HLS INTERFACE s_axilite port=dst   bundle=CONTROL
    #pragma HLS INTERFACE s_axilite port=length bundle=CONTROL
    #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL

    // Use memcpy to perform the DMA memory copy
    memcpy((void *)dst, (const void *)src, length * sizeof(uint32_t));
}

#ifdef __cplusplus
}
#endif
