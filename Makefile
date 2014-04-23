SRC=$(wildcard src/*.c)

mis: $(SRC)
	clear
	test -d bin || mkdir bin
	colorgcc --std=c99 -g -Iinclude/ -o bin/$@ $? $(CFLAGS) -lm

run: mis
	bin/mis res/two-leaders.txt

debug: mis
	gdb -tui bin/mis

.PHONY: clean
clean:
	rm -rf bin/ obj/
