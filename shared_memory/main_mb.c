#include "xparameters.h"
#include "sleep.h"

// Function to read the switches (2-bit value)
uint8_t read_switches() {
    volatile uint32_t *switch_data = (volatile uint32_t *)(XPAR_SWITCHES_BASEADDR);
    return *switch_data & 0x03;  // Read and mask to get only the lowest 2 bits
}

int main() {
    // Current switch value will be stored here
    volatile uint8_t* switchValue = (volatile uint8_t*)XPAR_XBRAM_0_BASEADDR;
    uint8_t prevValue = 0xFF;  // Initialize to a value that won't match any real switch value

    /** Application Loop **/
    while(1) {
        // Read the current value of the switches
        uint8_t currentValue = read_switches();
        
        // Only update shared memory if the value has changed
        if (currentValue != prevValue) {
            *switchValue = currentValue;
            prevValue = currentValue;
            xil_printf("Switch state updated: 0b%02b\r\n", currentValue);  // Debug output in binary
        }

        // 100ms delay
        usleep(100000);
    }

    return 0;
}