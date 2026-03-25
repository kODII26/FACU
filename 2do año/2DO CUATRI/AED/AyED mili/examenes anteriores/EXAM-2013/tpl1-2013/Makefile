program.bin: program.cpp
	g++ -o $@ $<

PROG := testme
# PROG := programsol
$(PROG).bin: $(PROG).cpp
	g++ -g3 -O0 -o $@ $<

# PWD := JK5SY8L1SU3
PWD := TE6J3SE5MA
zip:
	ad -rf tpl1-2013
	mkdir tpl1-2013
	cp Evaluar.hpp Makefile program.cpp tpl1-2013
	cp /home/mstorti/AED/aed/exam/tpl1-2013.pdf tpl1-2013
#	zip -r -P $(PWD) tpl1-2013.zip tpl1-2013
	zip -r tpl1-2013.zip tpl1-2013

unzip:
	ad -rf qq
	mkdir qq 
	cd qq ; unzip -P $(PWD) ../tpl1-2013.zip
