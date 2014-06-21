# Makefile for ECPG

# Name of executable file
TRG	= formatDNA

# Name of source file (.pgc)
FILES	= $(TRG).pgc

CC	= cc
PCC	= ecpg
INC_DIR	= /usr/include/postgresql
LIBS	= -lecpg -lm
C_FILES	= $(FILES:.pgc=.c)
OBJS	= $(C_FILES:.c=.o)

$(TRG):		$(OBJS)
		$(CC) -o $@ $(OBJS) $(LIBS)

clean:
		rm $(OBJS) $(C_FILES)

%.c:		%.pgc
		$(PCC) $<

.c.o:
		$(CC) -c -g -I$(INC_DIR) $<
