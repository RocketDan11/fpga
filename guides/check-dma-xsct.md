Assuming the following Memory Map:

DDR "Source" Address: 0x0011\_0000

DDR "Destination" Address: 0x0012\_0000

MM2S Source

0x4040\_0000 : MM2S DMA Control Register

0x4040\_0018 : MM2S Source Address (31:0) Register

0x4040\_0028 : MM2S Source Length Register

S2MM Destination

0x4040\_0030 : S2MM DMA Control Register

0x4040\_0048 : S2MM Destination Address (31:0) Register

0x4040\_0058 : S2MM Destination Length Register

You can use the XSCT Console (in SDK) to write to the Source Addresses (data to send to PL) and to read the Destination Addresses (to verify data from PL).  For example, use the following commands from XSCT to write specific data to the Source Address and verify the data was written as expected:

mwr -size w 0x00110000 {0x01234567 0x12345678 0x23456789 0x34567890 0x45678901 0x56789012 0x67890123 0x78901234 0x89012345 0x90123456 0x21436587 0xffeeddcc} 0x100

  _Write 256 words starting at address 0x0011_0000 & fill with list with remaining filled by last value_

mrd 0x00110000 0x100

  _Read 256 (0x100) words starting at address 0x0011_0000_

For DMA Transfer from **PS-DDR to PL** and then from **PL to PS-DDR**:

DMA Transfers begin with the writing of the Length Register

Step 1: mwr 0x40400000 0x00000001

 _Start Source DMA Engine_

Step 2: mwr 0x40400030 0x00000001

 _Start Destination DMA Engine_

Step 3: mwr 0x40400018 0x00110000

 _Define Source Address_

Step 4: mwr 0x40400048 0x00120000

 _Define Destination Address_

 

PS-DDR to PL DMA Transfer begin with the writing of the Length Register

Step 5: mwr 0x40400028 0x00000400

 _Write Source Length Register & Launch DMA_

PL to PS-DDR DMA Transfer begin with the writing of the Length Register

Step 6: mwr 0x40400058 0x00000400

 _Write Destination Length Register & Launch DMA_

After the DMA Transfers, you can verify the Destination Address contents using the XSCT:

mrd 0x00120000 0x100

  _Read 256 words starting at address 0x0012_0000_
