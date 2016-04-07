EXE=test.out

all: $(EXE)

CLEAN=rm -f $(EXE) *.o *.a

CFLG=-O3 -Wall

testRead.o: testRead.cpp

readfile.o: readfile.cpp


.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<


test.out: testRead.o readfile.o
	g++ -O3 -o $@ $^


#  Clean
clean:
	$(CLEAN)