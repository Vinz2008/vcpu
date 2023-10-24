CC = gcc

EMULATORDIR = emulator

EMULATORSRCS := $(wildcard $(EMULATORDIR)/*.c)
EMULATOROBJS = $(patsubst %.c,%.o,$(EMULATORSRCS))

CFLAGS = -Wall -O2 -c -g

all: vcpu-emulator

vcpu-emulator: $(EMULATOROBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EMULATORDIR)/%.o:$(EMULATORDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(EMULATORDIR)/*.o

run:
	./vcpu-emulator test.bin