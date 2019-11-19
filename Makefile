CC = sdcc
LIBS = -lstm8 -mstm8
IDIR = -I./
CFLAGS = $(LIBS) $(IDIR)
OUTDIR = ./bin/
RELDIR = $(OUTDIR)rel/
RELFLS = $(RELDIR)*.rel
IHXFLE = $(OUTDIR)main.ihx

SRCS += ./onewire_drvr.c

all: $(IHXFLE)

$(IHXFLE): $(RELFLS)
	$(CC) main.c $^ $(CFLAGS) -o$(OUTDIR)

# Cycle is needed since SDCC compiles only 1 file at once.
$(RELFLS): $(SRCS)
	mkdir -p $(RELDIR)
	for SOURCE in $^; do $(CC) $(CFLAGS) -c $$SOURCE -o$(RELDIR); done; 

clean:
	@rm -rf $(OUTDIR)

flash:
	sudo stm8flash -c stlinkv2 -p stm8l152c6 -w $(IHXFLE)

.PHONY: clean flash
