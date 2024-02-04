# Specs

# Description

Inspired by [this video](https://www.youtube.com/watch?v=wjHlvQfo5uI)

16 bit arch

instructions : 32 bits wide (first byte opcode, second register, third and fourth are data)

## Opcodes

0x0X : LOAD
-> 0x00 : load from number to reg (LOAD reg, number)
-> 0x01 : load from reg to reg (LOAD reg, reg)
-> 0x02 : load from mem to reg (LOAD reg, mem)
0x1X : STORE
-> 0x10 : store from reg to memory (16 bits)
-> 0x11 : store from reg to memory (high 8 bits)
-> 0x12 : store from reg to memory (low 8 bits)
0x2X : CMP
-> 0x20 : compare reg with reg
-> 0x21 : compare reg with number
0x3X : Jump
-> 0x30 : branch if equal
-> 0x31 : branch if >
-> 0x32 : branch if <
-> 0x33 : branch always
0x4X : Math
-> 0x40 : add value to register (ADD r0, 2 -> r0 = r0 + 2)
-> 0x41 : subtract value from register (SUB r1, 2 -> r1 - 2)
-> 0x42 : add register to register (ADD r0, r1 -> r0 = r0 + r1)
-> 0x43 : substract register from register (SUB r1, r0 -> r1 - r0)
-> 0x44 : multiply value and register (MUL r0, 2 -> r0 = r0 * 2)
-> 0x45 : divide value and register (DIV r0, 2 -> r0 = r0 / 2)
-> 0x46 : multiply register and register (MUL r0, r1 -> r0 = r0 * r1)
-> 0x47 : divide register and register (DIV r0, r1 -> r0 = r0 / r1)

0x5X : logical operators ops
-> 0x50 : AND
-> 0x51 : OR
-> 0x52 : NOT
-> 0x53 : XOR

0xEX : Stack
-> 0xE0 : push a value to the stack
-> 0xE1 : push a value from a register to the stack
-> 0xE2 : pop the last value from the stack to a register

0xFX : misc
-> 0xF0 : syscall
-> 0xFE : halt
-> 0xFF : noop

(TODO : implement logical operators)
(TODO : add permissions for syscalls to access the filesystem, the network)
(TODO : add a way to call c functions : use syscall to also use the permission system to select which c functions can be called or use a dedicated instruction)
(TODO : add instruction for stack : push)
(TODO : have multiple segments in executables : one for strings, one for coded, one for global vars, etc)

## Registers

r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10 (r10 is for the stack pointer)

pc (16 bits) : address

## Calling convention

Using r0 for return address,
r1, r2, r3, and r4 are for args. If you have more args, you will need to push them on the stack

## The stack

The stack starts at 0xffff (the end of the memory) and grow downward