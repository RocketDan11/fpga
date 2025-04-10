#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void dma_memcpy(volatile uint32_t *src, volatile uint32_t *dst, uint32_t length);

#ifdef __cplusplus
}
#endif

#define ARRAY_SIZE 1024

int main() {
    uint32_t src[ARRAY_SIZE];
    uint32_t dst[ARRAY_SIZE];
    int error = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        src[i] = (uint32_t)i;
        dst[i] = 0;
    }

    dma_memcpy((volatile uint32_t *)src, (volatile uint32_t *)dst, ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (dst[i] != src[i]) {
            printf("Mismatch at index %d: src = %u, dst = %u\n", i, src[i], dst[i]);
            error++;
        }
    }

    if (error == 0) {
        printf("Test Passed: All data copied correctly.\n");
        return 0;
    } else {
        printf("Test Failed: %d mismatches found.\n", error);
        return 1;
    }
}

