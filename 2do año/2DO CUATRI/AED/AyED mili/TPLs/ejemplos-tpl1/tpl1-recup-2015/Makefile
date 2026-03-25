# -*- mode: makefile -*-
## GITVERSION: tpl1-recup-2015-33-ge65b368
CPP := util_btree.cpp util.cpp util_tree.cpp
HPP := eval.hpp util.hpp util_tree.hpp tree.hpp util_btree.hpp 
SRCS := $(CPP) $(HPP)
program.bin: program.cpp $(SRCS)
	g++ -g3 -O0 -o $@ $< $(CPP)
