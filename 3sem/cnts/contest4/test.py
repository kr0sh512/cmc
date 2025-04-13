import struct

# Define the Node structure
class Node:
    def __init__(self, key, left_idx, right_idx):
        self.key = key
        self.left_idx = left_idx
        self.right_idx = right_idx

# Create a binary search tree
nodes = [
    Node(20, 1, 2),  # Root node
    Node(-10, 3, 4),  # Left child of root
    Node(30, 5, 6),  # Right child of root
    Node(-5, 0, 0),   # Left child of node with key 10
    Node(15, 0, 0),  # Right child of node with key 10
    Node(25, 0, 0),  # Left child of node with key 30
    Node(35, 0, 0)   # Right child of node with key 30
]

# Write the nodes to a binary file in Big-Endian format
with open('test_tree.bin', 'wb') as f:
    for node in nodes:
        # Pack the data in Big-Endian format
        f.write(struct.pack('>i', node.key))
        f.write(struct.pack('>i', node.left_idx))
        f.write(struct.pack('>i', node.right_idx))

# Verify the content of the file
with open('test_tree.bin', 'rb') as f:
    content = f.read()
    print("Binary content:", bytes(content).hex())