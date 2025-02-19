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
	@printf "\033[2;3mBuilding Deq...\033[0m\n"
	$(MAKE) -C deq
	@printf "\033[92;1mDeq Built\033[0m\n"

.SUFFIXES:

%.o: %.c  ; gcc -o $@ -c $< $(ccflags)
%.i: %.c  ; gcc -o $@ -E $< $(defines)
%.s: %.c  ; gcc -o $@ -S $< $(defines)
%.o: %.cc ; g++ -o $@ -c $< $(ccflags)
%.i: %.cc ; g++ -o $@ -E $< $(defines)
%.s: %.cc ; g++ -o $@ -S $< $(defines)

$(prog): $(objs) libdeq.so
	@printf "\033[2;3mBuilding %s...\033[0m\n" $@
	$(ld) -o $@ $(objs) $(ldflags) -Wl,-rpath=.
	@printf "\033[92;1m%s Built\033[0m\n" $@

libdeq.so: deq/libdeq.so
	cp $^ ./

try: $(objs) libdeq.so
	gcc -o $@ $(objs) $(ldflags) -Wl,-rpath=.

trytest: try
	Test/run

test: $(prog)
	Test/run

clean:
	rm -f $(prog) libdeq.so try trytest test *.o *.d *.i
	$(MAKE) -C deq clean

valgrind: $(prog) ; vg
