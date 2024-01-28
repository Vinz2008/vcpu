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

0xFX : misc
-> 0xFF : noop
-> 0xFE : halt


(TODO : add an instruction for syscalls)


## Registers

r0, r1, r2, r3, r4, 

pc (16 bits) : address