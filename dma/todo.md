Memory transfer options
---
AXI DMA supports memory mapped to stream interface.. what we need is memory map to memory map transfer.

AXI Central DMA -> supports MM2MM out of the box

AXI DMA -> robust dma, though the only interface is MM2S and S2MM.. maybe we can route the MM2S output to the S2MM input to force it to act as MM2MM

AXI Datamover -> used inside of AXI DMA, supports MM2S and S2MM. maybe we can package two of them such as (MM2S - S2MM) with a fifo in between to create our own "simple" DMA

HLS generated DMA -> write the loop (start, stop, stride) in C and let HLS generate the HDL we need for moving Data.

