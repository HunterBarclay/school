prog=deq

include ./Parent-GNUmakefile

try: main.o libdeq.so
	gcc -o $@ $< -L. -ldeq -Wl,-rpath=.
