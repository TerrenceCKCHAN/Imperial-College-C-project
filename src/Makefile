all:
	+$(MAKE) -C assembler
	+$(MAKE) -C emulator
	mv assembler/assemble .
	mv emulator/emulate .

clean:
	rm -f emulate
	rm -f assemble
