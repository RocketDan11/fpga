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
to create an HLS component, open Vitis and select a workspace,
- choose "Create HLS Component" and select component name
- select empty file
- choose top function name, this should be the same as the c code you plan to convert to HLS, such as "dma"
- choose "Hardware Design" and select the bit-stream that we exported from Vivado
- choose a clock speed (100Mhz is a fine default)
- for flow\_target select "Vivado IP Flow Target"
- for package.output.format select "Generate Vivado IP and .zip archive"

now that we've created an empty HLS project. In Vitis Explorer view click the drop down to reveal the options. right click "Sources" and select "New Source File"... create a c++ file with the name same as we chose for our top level function (ex: dma.cpp)
