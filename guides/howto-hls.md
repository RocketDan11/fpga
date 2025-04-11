terms
--
RTL - register-transfer level
HLS - high level synthesis
HDL - hardware description language
PS7 - processing system 7
Intro
--
This is a guide on how to create custom RTL components by describing your needs functionally with a high level language (C, C++) and using HLS to generate the HDL to implement the solution in logic.

Hardware platform
--
In the Vitis tools, you can select the chip you want to target (this matters bc different architectures have different hardware implementations), though generally I create a base platform in Vivado by selecting my chip there, dropping in a PS7 and exporting a bitstream.

Vitis HLS
--
to create an HLS component...

