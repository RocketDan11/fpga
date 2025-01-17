Creating a shared memory system with a truly dual ported RAM on PYNQ-Z2 board.

create a new directory called shared_mem, inside create a new vivado project called shared_mem_hw. create a block diagram named u15_top. Add the following components.

[+] ps7

run block automation

[+] microblaze_riscv

run block automation, selecting no cache and increasing local memory to 64KB

microblaze - local memory uses 2 buses, one for data and the other for instructions (Harvard architecture) notice the local memory is double buffered

![[mb_ps.png]]
[+] AXI SmartConnect rename(ps_connect)
[+] AXI_SmartConnect rename(mb_connect)
[+] AXI BRAM controller rename(ps_mem_ctrl)
[+] AXI BRAM controller rename(mb_mem_ctrl)
[+] Block Memory Generator rename(shared_mem)

double click shared_mem and change mode to 'True Dual Port RAM'. check common clock
![[bram_options.png]]

double click each mem_ctrl and under BRAM options change # of BRAM interfaces to 1.

now connect each master to its corresponding slave port. connect the mem_ctrl master ports to the shared_mem.

![[dualportRAM.png]]

now double click each interconnect and shave the # of slave ports to 1. connect each slave to the master of its corresponding processor.
![[shared_mem.png]]

now manually connect all aclk signals to the processing systems FCLK_CLK0 port. manually connect each interconnect reset to the Processing System Reset blocks interconnect_aresetn port and each mem_ctrl reset to the peripheral_areset port.
![[shared_mem0.png]]

This is our truly dualported platform. to test it lets add switches to the microblaze network and LEDs to the processing systems network.
double click each interconnect and add a master interface.
[+] AXI GPIO rename(SWITCHES)
[+] AXI_GPIO rename(LEDs)

connect each S_AXI ports to its processors interconnect.
mb -> SWITCHES
ps -> LEDs

in the boards menu double click 2 RGB and assign it to GPIO 0, double click 2 Switches and add it to GPIO 1. make sure to add the peripherals to the correct GPIO block..
![[gpio_block.png]]

now lets add a serial configuration to the microblaze. double click its interconnect and add one more master port.

[+] AXI UARTLite 

double click UARTLite block and change baud rate to 115200.

connect the UARTs slave to the 3rd master on mb_connect.. connect the clocks for the 3 blocks we've added to FCLK_CLK0 on processing system.. connect the remaining resets to peripheral_aresetn port on Processing System Reset. after validating design and assigning unassigned memory addresses the final design should look like this. NOTE: running block automation here will add the pin for the uart_rtl

![[final_design.png]]


in the sources tab, under Design sources right click u15_top and select 'create HDL wrapper'

![[wrapper.png]]

now save and in Flow Navigator, Run Implementation. this will take a couple minutes. in the top right corner of your screen you will see the progress
![[loding.png]]when its done we can open the Implemented design and navigate to the I/O ports tab.. here we can assign the pmod ports to their respective tx and rx pins as well as set the voltage.
![[uart_rtl.png]]save this and choose the name uart_rtl. this will create a constraint file with the following constraints..
![[constraints.png]]now we can finish by generating the bit stream, this will take a couple minutes, then file > export hardware and include bitstream.

now create a new directory along side shared_mem_hw called shared_mem_sw. enter this directory and run vitis 'vitis -w .' to set the current directory as the active workspace.

now create a new platform component. choose to browse for existing hardware and select u15_top_wrapper.xsa that we just exported from vivado. choose standalone operating system and ps7_cortex_0 for the processor.
![[vitis.png]]now from examples. create a new hello world example named hello_world_ps selecting all the presets. make another hello world from example and create a new domain called microblaze
![[microblaze.png]]our vitis explorer should look like this..
![[vitis_explorer.png]]now create a new system project. select the platform we created.

in system project setting choose Add Existing Component and add both hello_world examples to the project.
![[system_project.png]]

now edit the source code for each hello_world..

for hello_world_mb
```#include <stdio.h>

#include "platform.h"

#include "xil_printf.h"

#include "xparameters.h"

#include "sleep.h"

  

// Function to read the switches (2-bit value)

uint8_t read_switches() {

volatile uint32_t *switch_data = (volatile uint32_t *)(XPAR_SWITCHES_BASEADDR);

return *switch_data & 0x03; // Read and mask to get only the lowest 2 bits

}

  

int main() {

// Current switch value will be stored here

volatile uint8_t* switchValue = (volatile uint8_t*)XPAR_XBRAM_0_BASEADDR;

uint8_t prevValue = 0xFF; // Initialize to a value that won't match any real switch value

  

/** Application Loop **/

while(1) {

// Read the current value of the switches

uint8_t currentValue = read_switches();

// Only update shared memory if the value has changed

if (currentValue != prevValue) {

*switchValue = currentValue;

prevValue = currentValue;

xil_printf("Switch state updated: 0b%02b\r\n", currentValue); // Debug output in binary

}

  

// 100ms delay

usleep(100000);

}

  

return 0;

}
```

and for hello_world_ps
```
#include <stdio.h>

#include "platform.h"

#include "xil_printf.h"

#include "xparameters.h"

#include "sleep.h"

  

// Define the LED GPIO registers

#define LED_TRI_OFFSET 0x4

#define LED_MASK 0x03 // Assuming LEDs are on the two lowest bits

#define XPAR_XBRAM_0_BASEADDR 0x40000000

// Function to initialize the LEDs

void init_leds() {

volatile uint32_t *led_tri = (volatile uint32_t *)(XPAR_LEDS_BASEADDR + LED_TRI_OFFSET);

// Set the two lowest bits as outputs (0 for output, 1 for input)

*led_tri &= ~LED_MASK;

}

  

// Function to write to the LEDs (2-bit value)

void write_leds(uint8_t value) {

volatile uint32_t *led_data = (volatile uint32_t *)(XPAR_LEDS_BASEADDR); // Added offset

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

uint8_t prevValue = 0xFF; // Initialize to a value that won't match any real switch value

  

/** Application Loop **/

while(1) {

uint8_t currentValue = *switchValue & LED_MASK;

// Only update LEDs if the value has changed

if (currentValue != prevValue) {

write_leds(currentValue);

prevValue = currentValue;

xil_printf("Updated LEDs: 0b%02b\r\n", currentValue); // Debug output in binary

}

  

// 100ms delay

usleep(100000);

}

  

return 0;

}
```

Now we can create a run configuration. the defaults are find. this will load an .elf onto each processor. when we flip the switches we can observe the LEDs change color.
