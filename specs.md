# Specs

# Description

Inspired by [this video](https://www.youtube.com/watch?v=wjHlvQfo5uI)

16 bit arch

instructions : 32 bits wide (first byte opcode, second register, third and fourth are data)

## Opcodes

0x0X : LOAD
-> 0x00 : load from number to reg (LOAD reg, number)
-> 0x01 : load from reg to reg
-> 0x02 : load from mem to reg
0x1X : STORE
-> 0x10 : store from reg to memory (16 bits)
-> 0x11 : store from reg to memory (high 8 bits)
-> 0x12 : store from reg to memory (low 8 bits)
0x2X : CMP
-> 0x20 : compare reg with reg
-> 0x21 : compare reg with number
0x4X : Math
-> 0x40 : ADD
-> 0x41 : SUB
-> 0x42 : JMP

(add an instruction for syscalls)


## Registers

r0, r1, r2, r3, r4, 

pc (16 bits) : address