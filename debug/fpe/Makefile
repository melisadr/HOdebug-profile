.PHONY: default help object executable all clean segfault dynamic static nobugs
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))
EXECUTABLES = $(patsubst %.c, %.e, $(SOURCE_C))

OBJECTS_TRAP = $(patsubst %.c, %_trapfpe.o, $(SOURCE_C))
EXECUTABLES_TRAP = $(patsubst %.c, %_trapfpe.e, $(SOURCE_C))

default: all

help:
	@echo "\
Options:\n\n\
  make all:           make every executable (default)\n\
  make fpe1:          compila normalmente el caso fpe1 \n\
  make fpe1_t:	      compila con flag -DTRAPFPE el paso fpe1 \n\
  make fpe2:          compila normalmente el caso fpe2 \n\
  make fpe2_t:	      compila con flag -DTRAPFPE el paso fpe2 \n\
  make fpe3:          compila normalmente el caso fpe3 \n\
  make fpe3_t:	      compila con flag -DTRAPFPE el paso fpe3 \n\
  make clean:	      limpia todo

objects: $(OBJECTS_C)

executable: $(EXECUTABLES)

all: objects executable

fpe1: test_fpe1.e 

fpe1_t: test_fpe1_trapfpe.e 

fpe2: test_fpe2.e 

fpe2_t: test_fpe2_trapfpe.e 

fpe3: test_fpe3.e 

fpe3_t: test_fpe3_trapfpe.e 
 

%_c.o: %.c
	$(CC) -g -O0  -c $^ -o  $@

%.e: %_c.o
	$(LD) $^ -lm -o $@

%_trapfpe.o: %.c
	$(CC) -DTRAPFPE -g -c $^ -o  $@

%_trapfpe.e: %_trapfpe.o 
	$(LD) $^ ./fpe_x87_sse/fpe_x87_sse.o -lm -o $@

clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLES) $(OBJECTS_TRAP) $(EXECUTABLES_TRAP) 

