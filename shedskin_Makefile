SHEDSKIN_LIBDIR=../shedskin_src/shedskin/lib
CC=emcc
CCFLAGS=  -I. -I${SHEDSKIN_LIBDIR}
LFLAGS=

CPPFILES=hello.cpp \
	${SHEDSKIN_LIBDIR}/re.cpp \
	${SHEDSKIN_LIBDIR}/builtin.cpp

HPPFILES=hello.hpp \
	${SHEDSKIN_LIBDIR}/re.hpp \
	${SHEDSKIN_LIBDIR}/builtin.hpp

all:	hello

hello:	$(CPPFILES) $(HPPFILES)
	$(CC)  $(CCFLAGS) $(CPPFILES) -o hello.js

clean:
	rm hello.js



