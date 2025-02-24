prog=shell
objs+=$(addsuffix .o,$(basename $(wildcard *.c *.cc)))

defines+=-D_GNU_SOURCE
ccflags+=-g -Wall -MMD $(defines) -fPIC
ldflags:=-lreadline -lncurses -L. -ldeq
ld?=gcc

.PHONY: clean valgrind deq all

# Requires deq be addressed first, before evaluating the rest of the dependencies
all: deq $(prog) ;

# Runs the deq makefile
deq:
	@printf "\033[2;3mBuilding deq...\033[0m\n"
	$(MAKE) -C deq
	@printf "\033[92;1mdeq Built\033[0m\n"

.SUFFIXES:

%.o: %.c  ; gcc -o $@ -c $< $(ccflags)
%.i: %.c  ; gcc -o $@ -E $< $(defines)
%.s: %.c  ; gcc -o $@ -S $< $(defines)
%.o: %.cc ; g++ -o $@ -c $< $(ccflags)
%.i: %.cc ; g++ -o $@ -E $< $(defines)
%.s: %.cc ; g++ -o $@ -S $< $(defines)

$(prog): deq $(objs) libdeq.so
	@printf "\033[2;3mBuilding %s...\033[0m\n" $@
	$(ld) -o $@ $(objs) $(ldflags) -Wl,-rpath=.
	@printf "\033[92;1m%s Built\033[0m\n" $@

libdeq.so: deq/libdeq.so
	cp $^ ./

test: $(prog)
	run-tests

clean:
	rm -f $(prog) libdeq.so test *.o *.d *.i
	rm -f tests/test-*/out*
	rm -f tests/test-*/diff*
	rm -f tests/test-*/errs*
	$(MAKE) -C deq clean

valgrind: $(prog) ; vg
