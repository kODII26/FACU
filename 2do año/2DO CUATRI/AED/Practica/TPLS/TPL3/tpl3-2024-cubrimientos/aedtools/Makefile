default: buildd

#w make the doc
README.pdf: README.adoc
	asciidoc -s README.adoc

#w Make the tags
tags: 
	etags *.hpp *.cpp

#w Compile and install
buildd:
	if [ ! -d build ] ; then mkdir build ; fi ; \
		cd build ; cmake .. ; make -j ; make install

## Describe targets
what:
	@makewhat.pl -s Makefile
