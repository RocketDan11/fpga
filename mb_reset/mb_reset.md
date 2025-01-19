create a new project following the naming convention in previous projects. (parent directory named mb_reset, inside we will have two directories, reset_hw and reset_sw)

inside reset_hw create a new Vivado project selecting pynq-z2 board preset.

create a new block diagram called 'u15_top' and add...

[+] processing system 7
- run block automation choosing defaults
[+] microblaze risc-v
- run block automation, selecting 'none' for cache and 64KB for local memory. the rest can be left default.
[+] 2x AXI SmartConnect
- name one MB_CONNECT and the other PS_CONNECT
[+] Uartlite
- set baud rate to 115200
[+] AXI GPIO 
- set to single channel, all output, 1 bit wide.

-- connect each processor to its respective SmartConnect, then MB_CONNECT M0 to Uartlite and PS_CONNECT M0 to AXI GPIO block, then disconnect the microblaze reset pin and replace it with the output of GPIO.. your design should look like this.. (2 memory controllers and block memory generator are not needed.)

![[mb_reset.png]]

Now create the uart_rtl constraint file and generate the bitstream..

---
in VITIS, create a new platform using the hardware we just exported, then create a system project using a hello_world template for each processor. build the system project with the following code for each processor..

for microblaze:
```#include <stdio.h>

#include "platform.h"

#include "xil_printf.h"

  
  

int main()

{

init_platform();

  

print("Hello World\n\r");

print("RESET\n\r");

while(1){}

cleanup_platform();

return 0;

}
```
This will print Hello World and RESET then go into an infinite loop. it will be stuck here unless it gets reset.. hence the PS code below...

```#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

int main() {
    volatile unsigned int *gpio = (volatile unsigned int *)XPAR_AXI_GPIO_0_BASEADDR;
    
    while(1) {
        // Write 1 (button press)
        *gpio = 0x1;
        
        // Small delay for button press
        for(volatile int i = 0; i < 1000000; i++);
        
        // Write 0 (button release)
        *gpio = 0x0;
        
        // 5 second delay (adjust loop count based on your system clock)
        for(volatile int i = 0; i < 50000000; i++);
    }
    
    return 0;
}
```
This will for a reset singal to the microblazes reset port every couple of seconds.. by monitoring the uartlite from the microblaze, we can see the microblaze getting reset and running its code again.