#!/bin/python3
from pwn import *
from ctypes import CDLL

password = b'eachintheshell'

p = remote('localhost', 1331)

libc = CDLL("libc.so.6")
seed = libc.time(0)
log.info(f'seed: {seed}')
libc.srand(seed)

payload = b''

for c in password:
    payload += p8(c ^ (libc.rand() & 0xff))

log.info(f'({len(payload)}){payload}')
p.send(payload)
p.stream()
