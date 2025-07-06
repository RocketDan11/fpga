
#to trace a model it should be defined using nn.Module, use standard layers, and have a static forward pass (no branching or data-dependent control flow).


import torch
import torch.fx as fx

model = MyModel()  # your PyTorch nn.Module
traced = fx.symbolic_trace(model)
print(traced.graph)

