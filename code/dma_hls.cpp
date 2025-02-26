void simple_dma(int* src, int* dest, int num_elements) {
   
        #pragma HLS INTERFACE m_axi port=src max_read_burst_length=256
	#pragma HLS INTERFACE m_axi port=dest max_write_burst_length=256
	for(int i = 0; i < num_elements; i++) {
        #pragma HLS PIPELINE II=1
        dest[i] = src[i];
    }
}
