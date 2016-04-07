EXE=test.out

all: $(EXE)

CFLG=-O3 -Wall
CLEAN=rm -f $(EXE) *.o *.a

interpolate.o: interpolate.cpp

gradient.o: gradient.cpp

testGradient.o: testGradient.cpp

testGradient.o: testGradient.cpp
# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

test.out:testGradient.o interpolate.o gradient.o
	g++ -O3 -o $@ $^  $(LIBS) 

#  Clean
clean:
	$(CLEAN)
