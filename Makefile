CC = gcc

EMULATORDIR = emulator

EMULATORSRCS := $(wildcard $(EMULATORDIR)/*.c)
EMULATOROBJS = $(patsubst %.c,%.o,$(EMULATORSRCS))

ASSEMBLERDIR = assembler

ASSEMBLERSRCS := $(wildcard $(ASSEMBLERDIR)/*.c)
ASSEMBLEROBJS = $(patsubst %.c,%.o,$(ASSEMBLERSRCS))

RUNNERDIR = runner

RUNNERSRCS := $(wildcard $(RUNNERDIR)/*.c)
RUNNEROBJS = $(patsubst %.c,%.o,$(RUNNERSRCS))

CFLAGS = -Wall -O2 -c -g

#CFLAGS += -fsanitize=address
#LDFLAGS = -fsanitize=address

all: emulator assembler runner

emulator: vcpu-emulator

vcpu-emulator: $(EMULATOROBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EMULATORDIR)/%.o:$(EMULATORDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

assembler: vcpu-assembler

vcpu-assembler: $(ASSEMBLEROBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(ASSEMBLERDIR)/%.o:$(ASSEMBLERDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

runner: vcpu-runner

vcpu-runner: $(RUNNEROBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(RUNNERDIR)/%.o:$(RUNNERDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(EMULATORDIR)/*.o $(ASSEMBLERDIR)/*.o $(RUNNERDIR)/*.o

run:
	./vcpu-emulator test.bin

run-asm:
	./vcpu-assembler test.asm -o out.bin