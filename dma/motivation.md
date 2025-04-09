Motivation

Emerging architectures offer many cores paired with an abundance of high-bandwidth memory, creating significant opportunities for performance gains. However, to fully capitalize on this evolving hardware landscape, efficient latency hiding is crucial. 

Objective

Our primary objective is to determine the optimal DMA placement strategy and Implementation.
Placement - Push vs Pull
In the push configuration, DMA engines are located on the processor side, requiring four DMA engines per processor, whereas in the pull configuration, DMA resides on the memory side with each memory channel connected to a DMA.
Implementation - AXI vs HLS
AXI is AMD’s generalized, closed-sourced solution designed to provide standardized connectivity across various IP components. In contrast, HLS-generated cores offer a custom, application-specific approach, enabling tailored designs that can achieve enhanced performance and efficiency.

