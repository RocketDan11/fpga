#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"

// Define base address for BRAM
#define XPAR_XBRAM_0_BASEADDR 0x40000000
#define GPIO_TRI_OFFSET 0x4
#define GPIO_BIT_MASK 0x1  // Since it's 1-bit wide

int main() {
    // Initialize platform
    init_platform();
    
    // Create pointers for the first 3 registers
    volatile uint32_t* reg0 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR);
    volatile uint32_t* reg1 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 4);
    volatile uint32_t* reg2 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 8);
    volatile uint32_t* result = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 12);
    
    // Write values to registers
    *reg0 = 0x00000001;  // Example value for register 0
    *reg1 = 0x00000010;  // Example value for register 1
    *reg2 = 0x00000100;  // Example value for register 2
    
    // Print the values written to verify
    xil_printf("Register 0 value: 0x%08x\r\n", *reg0);
    xil_printf("Register 1 value: 0x%08x\r\n", *reg1);
    xil_printf("Register 2 value: 0x%08x\r\n", *reg2);
    
    // Write 1 to MB_RESET data register
    volatile uint32_t *gpio_data = (volatile uint32_t *)(XPAR_XGPIO_0_BASEADDR);
    *gpio_data &= GPIO_BIT_MASK;  // set bit
    // Print debug info
    xil_printf("GPIO1 value: 0x%08x\r\n", *gpio_data);

    usleep(100000); //delay 100ms

// Read the value from the register
uint32_t value = *result;

// Print the value (in both hex and decimal format for clarity)
xil_printf("Register value: 0x%08x (decimal: %d)\r\n", value, value);

    // Infinite loop to maintain program operation
    while(1) {
        // Add any additional monitoring or operations here
        usleep(100000);  // 100ms delay
    }
    
    cleanup_platform();
    return 0;
}
