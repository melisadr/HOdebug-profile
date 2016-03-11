.PHONY: default help object executable all clean segfault dynamic static nobugs
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_1 = $(patsubst %.c, %_1.o, $(SOURCE_C))
EXECUTABLES_1 = $(patsubst %.c, %_1.e, $(SOURCE_C))

OBJECTS_FLAG = $(patsubst %.c, %_flag.o, $(SOURCE_C))
EXECUTABLES_FLAG = $(patsubst %.c, %_flag.e, $(SOURCE_C))

default: all

help:
	@echo "\
Options:\n\n\
  make all:           make every executable (default)\n\
  make pr1_0:         compila con -O0 \n\
  make pr1_1:		      compila con -O1 \n\
	make pr1_3: 				compila con -O3	\n\
	make pr2_0:         compila con -O0 \n\
  make pr2_1:		      compila con -O1 \n\
	make pr2_3: 				compila con -O3	\n\
  make clean:	      	limpia todo			\n\

objects: $(OBJECTS_C)

executable: $(EXECUTABLES)

all: objects executable

pr1_0: test_profile_me_1_0.e 

pr1_1: test_profile_me_1_1.e

pr1_3: test_profile_me_1_3.e

pr2_0: test_profile_me_2_0.e 

pr2_1: test_profile_me_2_1.e

pr2_3: test_profile_me_2_3.e
 

%_0.o: %.c
		$(CC) -O0  -c $^ -o  $@

%_0.e: %_0.o
		$(LD) $^ -o $@

%_1.o: %.c
		$(CC) -O0  -c $^ -o  $@

%_1.e: %_0.o
		$(LD) $^ -o $@

%_3.o: %.c
		$(CC) -O0  -c $^ -o  $@

%_3.e: %_0.o
		$(LD) $^ -o $@


clean:
		rm -rfv $(OBJECTS_C) $(EXECUTABLES) 

clean_f:
		rm -rfv $(OBJECTS_FLAG) $(EXECUTABLES_FLAG) 

