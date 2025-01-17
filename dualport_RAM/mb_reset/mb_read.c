#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
  
int main() {
    init_platform();

    // Create pointers for the registers
    volatile uint32_t* reg0 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR);
    volatile uint32_t* reg1 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 4);
    volatile uint32_t* reg2 = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 8);
    volatile uint32_t* result = (volatile uint32_t*)(XPAR_XBRAM_0_BASEADDR + 12);
    
    /** Application Loop **/
    while(1) {
        // Read values from first 3 registers
        uint32_t value0 = *reg0;
        uint32_t value1 = *reg1;
        uint32_t value2 = *reg2;
        
        // Calculate sum
        uint32_t sum = value0 + value1 + value2;
        
        // Store result in fourth register
        *result = sum;
        
        // Print values for debugging
        xil_printf("Reg0: 0x%08x, Reg1: 0x%08x, Reg2: 0x%08x, Sum: 0x%08x\r\n", 
                   value0, value1, value2, sum);
        
        // Delay before next read
        usleep(100000);  // 100ms delay
    }
    
    cleanup_platform();
    return 0;
}
