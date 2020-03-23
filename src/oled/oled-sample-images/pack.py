import os
import sys

fn = sys.argv[1]

with open(fn, 'rb') as f:
    f.readline() # Magic number
    f.readline() # Creator comment
    f.readline() # Dimensions
    f.readline() # Max value, 255
    data = bytearray(f.read())

print(len(data))

p = []
for i in range(0, len(data), 8):
    byte = 0
    for n, bit in enumerate(data[i:i+8]):
        byte += 2**(7-n) if bit == 255 else 0

    p.append(byte)

b = bytearray(p)

print(len(b))
print(b[-1])


basename, _ = os.path.splitext(fn)
with open('%s.bin' % basename, 'wb') as f:
    f.write(b)