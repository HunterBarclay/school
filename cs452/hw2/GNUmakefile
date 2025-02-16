prog=buddy

include ./ParentMakefile

try: hw1/deq.o hw1/main.o balloc.o bbm.o bm.o freelist.o utils.o wrapper.o
	gcc -o $@ $^ $(ldflags)

.PHONY: test-wrapper

test-wrapper: try
	./$<
