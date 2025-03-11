#include <iostream>
#include <cstdint>
#include <cstring>

// Prototype DMA function (ensure matches your DMA function signature)
void dma_copy(volatile uint32_t *src, volatile uint32_t *dst, uint32_t length);

#define MEM_SIZE 1024

int main() {
    // Define source and destination arrays
    uint32_t src[MEM_SIZE];
    uint32_t dst[MEM_SIZE];

    const uint32_t length = 256; // Number of words to transfer

    // Initialize source array with known data, destination with zeros
    for (uint32_t i = 0; i < length; i++) {
        src[i] = 0xDEADBEEF + i; // Pattern data
        dst[i] = 0;              // Clear destination
    }

    // Perform the DMA transfer simulation
    dma_copy(src, dst, length);

    // Verify transferred data
    bool mismatch = false;
    for (uint32_t i = 0; i < length; i++) {
        if (dst[i] != src[i]) {
            std::cout << "Mismatch at [" << i << "]: src=0x" 
                      << std::hex << src[i] 
                      << ", dst=0x" << dst[i] << std::endl;
            mismatch = true;
        }
    }

    if (!mismatch)
        std::cout << "DMA transfer SUCCESSFUL." << std::endl;
    else
        std::cout << "DMA transfer FAILED." << std::endl;

    return mismatch ? 1 : 0;
}

