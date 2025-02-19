lib_shared=libdeq.so
lib_static=libdeq.a
objs+=$(addsuffix .o,$(basename $(wildcard *.c *.cc)))

defines+=-D_GNU_SOURCE
ccflags+=-g -Wall -MMD $(defines) -fPIC
ldflags+=-g -shared

.PHONY: clean all

all: $(lib_shared) $(lib_static)

.SUFFIXES:

%.o: %.c  ; gcc -o $@ -c $< $(ccflags)
%.i: %.c  ; gcc -o $@ -E $< $(defines)
%.s: %.c  ; gcc -o $@ -S $< $(defines)
%.o: %.cc ; g++ -o $@ -c $< $(ccflags)
%.i: %.cc ; g++ -o $@ -E $< $(defines)
%.s: %.cc ; g++ -o $@ -S $< $(defines)

ld?=gcc

$(lib_shared): $(objs) ; $(ld) -o $@ $^ $(ldflags)
$(lib_static): $(objs)
	ar rcs $@ $^

clean:: ; rm -f $(lib_shared) $(lib_static) *.o *.d *.i

# run:      $(prog) ; ./$< $(args)
# valgrind: $(prog) ; $@ --leak-check=full --show-leak-kinds=all ./$< $(args)

sinclude *.d
