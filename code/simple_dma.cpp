void simple_dma(int* src, int* dest, int num_elements) {
    #pragma HLS INTERFACE m_axi port=src depth=10 max_read_burst_length=256 offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=dest depth=10 max_write_burst_length=256 offset=slave bundle=gmem
    #pragma HLS INTERFACE s_axilite port=num_elements bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    for(int i = 0; i < num_elements; i++) {
        #pragma HLS PIPELINE II=1
        dest[i] = src[i];
    }
}
