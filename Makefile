MIS_SRC=$(wildcard src/mis/*.c)
VC_SRC=$(wildcard src/vc/*.c)

vc: $(VC_SRC)
	clear
	test -d bin || mkdir bin
	colorgcc --std=c99 -g -Iinclude/vc/ -o bin/$@ $? $(CFLAGS) -lm

mis: $(MIS_SRC)
	clear
	test -d bin || mkdir bin
	colorgcc --std=c99 -g -Iinclude/mis/ -o bin/$@ $? $(CFLAGS) -lm

run-vc: vc
	bin/vc res/two-leaders.txt 10

run-mis: mis
	bin/mis res/two-leaders.txt

.PHONY: clean
clean:
	rm -rf bin/ obj/
