issue: auto assign memory addresses with hls generated dma have overlapping, i need to assign distinct address spaces for each BRAM to clearly differentiate source and destination.

slave device | base address | high address| range
axi\_bram\_ctrl\_0 | 0x4000\_0000 | 0x4000\_1FFF | 8kb
axi\_bram\_ctrl\_0 | 0x4200\_0000 | 0x4200\_1FFF | 8kb
dma\_0 s\_axi\_ctrl | 0x43C0\_0000 | 0x4C0\_FFFF | 64kb

