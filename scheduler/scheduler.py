class BRAMStack:
    def __init__(self, id):
        self.id = id          # Unique ID for the BRAM stack
        self.set_bit = False  # Indicates if the BRAM needs updating
        self.data = None      # Data stored in the BRAM

    def __repr__(self):
        return f"BRAMStack(id={self.id}, set_bit={self.set_bit}, data={self.data})"
    
def set_bram_bit(bram_stacks, bram_id):
    if bram_id in bram_stacks:
        bram_stacks[bram_id].set_bit = True
        print(f"Set bit for BRAMStack ID {bram_id}")
    else:
        print(f"BRAMStack ID {bram_id} does not exist.")

def update_bram_stacks(bram_stacks, data):
    for bram in bram_stacks.values():
        if bram.set_bit:
            # Fill the BRAM with data
            bram.data = data
            bram.set_bit = True
            print(f"BRAMStack ID {bram.id} updated with data: {data}")

def read_bram_stacks(bram_stacks):
    for bram in bram_stacks.values():
        if bram.set_bit:
            print(f"BRAMStack ID {bram.id} updated with data: {bram.data}")
            bram.set_bit = False





bram_stacks = {i: BRAMStack(i) for i in range(256)}  # Assuming 256 BRAM stacks
# Example: Set bits for BRAM stacks with IDs 5, 10, and 128
set_bram_bit(bram_stacks, 5)
set_bram_bit(bram_stacks, 10)
set_bram_bit(bram_stacks, 128)

# Update BRAM stacks with data when their set bits are active
data_to_fill = 42  # Example data
update_bram_stacks(bram_stacks, data_to_fill)

# Verify that the BRAM stacks have been updated
print(bram_stacks[5])
print(bram_stacks[10])
print(bram_stacks[128])

# Output BRAM stacks that were not updated (should have set_bit=False and data=None)
print(bram_stacks[0])
print(bram_stacks[1])


    
