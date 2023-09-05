
COMPILER = clang++

SOURCE_LIBS = -Ilib/

OSX_OPT = -g -std=c++20 -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a

OSX_OUT = -o "bin/build_osx"

CFILES = src/*.cpp src/*/*.cpp src/*/*/*.cpp

build_osx:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT) 

