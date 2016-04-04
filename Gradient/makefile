EXE=main.out

all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=rm *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-g -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL -lgsl

#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
main.o: main.cpp 

shader.o: shader.c

interpolate.o: interpolate.cpp

gradient.o: gradient.cpp

test.o: test.cpp
# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
main.out:main.o gradient.o shader.o interpolate.o
	g++ -O3 -o $@ $^   $(LIBS)

test.out:test.o interpolate.o gradient.o
	g++ -O3 -o $@ $^  $(LIBS) 
#  Clean
clean:
	$(CLEAN)
