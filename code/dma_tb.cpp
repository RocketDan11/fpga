#include <iostream>
#include "simple_dma.h"

int main() {
    const int num_elements = 10;
    int* src = new int[num_elements];
    int* dest = new int[num_elements];

    // Initialize source array
    for(int i = 0; i < num_elements; i++) {
        src[i] = i;
    }

    // Call the function
    simple_dma(src, dest, num_elements);

    // Check the destination array
    bool passed = true;
    for(int i = 0; i < num_elements; i++) {
        if(dest[i] != src[i]) {
            passed = false;
            break;
        }
    }

    if(passed) {
        std::cout << "Test passed." << std::endl;
    } else {
        std::cout << "Test failed." << std::endl;
    }

    delete[] src;
    delete[] dest;

    return 0;
}
