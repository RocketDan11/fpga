#include "xparameters.h"
#include "sleep.h"

// Define the LED GPIO registers
#define LED_TRI_OFFSET     0x4
#define LED_MASK           0x03    // Assuming LEDs are on the two lowest bits

// Function to initialize the LEDs
void init_leds() {
    volatile uint32_t *led_tri = (volatile uint32_t *)(XPAR_LEDS_BASEADDR + LED_TRI_OFFSET);
    // Set the two lowest bits as outputs (0 for output, 1 for input)
    *led_tri &= ~LED_MASK;
}

// Function to write to the LEDs (2-bit value)
void write_leds(uint8_t value) {
    volatile uint32_t *led_data = (volatile uint32_t *)(XPAR_LEDS_BASEADDR);  // Added offset
    
    // Read current state
    uint32_t current_state = *led_data;
    
    // Clear the LED bits
    current_state &= ~LED_MASK;
    
    // Set new LED values
    current_state |= (value & LED_MASK);
    
    // Write back
    *led_data = current_state;
}

int main() {
    // Initialize LEDs
    init_leds();

    // Current switch value will be read from here
    volatile uint8_t* switchValue = (volatile uint8_t*)XPAR_XBRAM_0_BASEADDR;
    uint8_t prevValue = 0xFF;  // Initialize to a value that won't match any real switch value

    /** Application Loop **/
    while(1) {
        uint8_t currentValue = *switchValue & LED_MASK;
        
        // Only update LEDs if the value has changed
        if (currentValue != prevValue) {
            write_leds(currentValue);
            prevValue = currentValue;
            xil_printf("Updated LEDs: 0b%02b\r\n", currentValue);  // Debug output in binary
        }

        // 100ms delay
        usleep(100000);
    }

    return 0;
}