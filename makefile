IDIR = include
SDIR = src
CC = gcc
CFLAGS = -I$(IDIR) `pkg-config --cflags --libs gtk4`
LDADD = `pkg-config --libs gtk4`

ODIR = src/obj
LDIR = libs

_DEPS = functions.h main.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o activate.o globals.o first_screen.o button_callbacks.o player_one.o player_two.o drawing.o check_win.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bingo: $(OBJ)
	$(CC) -o $@ $^ $(LDADD)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
