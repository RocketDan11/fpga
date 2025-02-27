attempt at creating dma w hls...

- first create a simple hardware platform in vivado that has two discrete ports pointing to two different memory locations (can be in the same block of memory)
- export bitsream

- In Vitis create new HLS component, name top module 'simple\_dma' and select the platform from above.

- create simple\_dma.cpp under Sources.. 
- create testbench.cpp and simple\_dma.h.

in hls config select the correct top\_module

-> run simulation
-> run C synthesis
-> run C/RTL cosimulation
-> run package
-> run implementation


Licensing -- if you have an issue with license.. click the link provided in vitis to go to amd.com .. create new license selecting vitis HLS. create new host.. to find hostname in terminal type 'hostname'.. select Ethernet/MAC and to find MAC @ type 'ip link show' or 'ifconfig'.. find the 6 hex representing MAC.. should look like 'ff:ff:ff:ff:ff:ff'
