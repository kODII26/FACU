# -*- mode: makefile -*-
## GITVERSION: parc1-2015-125-g4896600
CPP := util_btree.cpp util.cpp util_tree.cpp
HPP := eval.hpp util.hpp util_tree.hpp tree.hpp util_btree.hpp 
SRCS := $(CPP) $(HPP)
program.bin: program.cpp $(SRCS)
	g++ -g3 -O0 -o $@ $< $(CPP)

check:
	$(MAKE) program.bin
	./program.bin
