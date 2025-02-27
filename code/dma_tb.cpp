#include <iostream>
#include "simple_dma.h"

int main() {
    const int num_elements = 10;
    int* src = new int[num_elements];
    int* dest = new int[num_elements];
    for(int i = 0; i < num_elements; i++) src[i] = i;
    simple_dma(src, dest, num_elements);
    bool passed = true;
    for(int i = 0; i < num_elements; i++) if(dest[i] != src[i]) passed = false;
    std::cout << (passed ? "Test passed." : "Test failed.") << std::endl;
    delete[] src; delete[] dest;
    return 0;
}
