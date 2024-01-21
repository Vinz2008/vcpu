LOAD r1, 2560
LOAD r2, r1
ADD r2, 10
SUB r2, 1
CMP r2, 2570
JEQ 0x0
# loop
LOAD r3, 0
.start_loop
ADD r3, 1
CMP r3, 10
JLT start_loop
NOOP