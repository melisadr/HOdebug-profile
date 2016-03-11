.PHONY: default help object executable all clean segfault dynamic static nobugs
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))
EXECUTABLES = $(patsubst %.c, %.e, $(SOURCE_C))

OBJECTS_FLAG = $(patsubst %.c, %_flag.o, $(SOURCE_C))
EXECUTABLES_FLAG = $(patsubst %.c, %_flag.e, $(SOURCE_C))

default: all

help:
	@echo "\
Options:\n\n\
  make all:           make every executable (default)\n\
  make oob2:          compila normalmente el caso fpe1 \n\
  make oob2_f:	      compila con flag -DTRAPFPE el paso fpe1 \n\
  make clean:	      	limpia todo
	make clean_f:				limpia con flag

objects: $(OBJECTS_C)

executable: $(EXECUTABLES)

all: objects executable

oob2: test_oob2.e 

oob2_f: test_oob2_f.e 
 

%_c.o: %.c
		$(CC) -g -O0  -c $^ -o  $@

%.e: %_c.o
		$(LD) $^ -o $@

%_flag.o: %.c
		$(CC) -DDEBUG -g -c $^ -o  $@

%_f.e: %_flag.o 
		$(LD) $^ -o $@

clean:
		rm -rfv $(OBJECTS_C) $(EXECUTABLES) 

clean_f:
		rm -rfv $(OBJECTS_FLAG) $(EXECUTABLES_FLAG) 

