program.bin: program.cpp
	g++ -o $@ $<

PROG := programsol
$(PROG).bin: $(PROG).cpp
	g++ -g3 -O0 -o $@ $<

# PWD := JK5SY8L1SU3
# PWD := TE6J3SE5MA
PWD := 6DG1ZG7IH6
TOOLS := tree.h util.h util_tree.h
zip:
	ad -rf tpl2-2013
	mkdir tpl2-2013
	cp Evaluar.hpp Makefile $(TOOLS) program.cpp tpl2-2013
	cp /home/mstorti/AED/aed/exam/tpl2-2013.pdf tpl2-2013
	ad -f tpl2-2013.zip
#	zip -r -P $(PWD) tpl2-2013.zip tpl2-2013
	zip -r tpl2-2013.zip tpl2-2013

unzip:
	ad -rf unpacked
	mkdir unpacked 
	cd unpacked ; unzip -P $(PWD) ../tpl2-2013.zip
	ad -rf tpl2-2013-unpacked
	mv ./unpacked/tpl2-2013 tpl2-2013-unpacked
	ad -rf unpacked
