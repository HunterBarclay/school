prog=buddy

include ../GNUmakefile

try: test.o libbuddy.so
	gcc -o $@ $< -L. -lbuddy -Wl,-rpath=.
