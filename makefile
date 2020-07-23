CC = g++ -std=c++11
exe_file = 3dcollaborativegame

# Handle debug case
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS := -g -Wall
else 
	CFLAGS := -DNDEBG -03
endif

#Enable the compiler to know where the standard libraries are
STDFLAGS := -isystem "MinGW/lib/gcc/mingw32/9.2.0/include/c++" -isystem "MinGW/include" -static-libgcc -static-libstdc++

#Compile it as a Position Independent Executable (PIE)
CFLAGS := -no-pie

#Special flags to get FreeGLUT and OpenGL to work 
OGLFLAGS := GLUT-MinGW-3.7.6-6/lib/libglut32.a -lopengl32

#Special flag to get the math library to work
MATHFLAG := -lm

#Get all .cpp files in the source directory
SRC_DIR := source
OBJ_DIR := objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

#Compile all .cpp files in the source directory and glad in the glad directory
$(exe_file): $(OBJ_FILES) $(OBJ_DIR)/glad.o
	$(CC) -o $@ $^ $(STDFLAGS) $(CFLAGS) $(MATHFLAG) $(OGLFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/glad.o: glad/glad.c
	$(CC) -c glad/glad.c -o $(OBJ_DIR)/glad.o $(CFLAGS)

clean:
	rm -rf $(exe_file) *.o

.PHONY: clean

#$(exe_file): main.o graphics.o geometry.o glad.o Vector3D.o
#	$(CC) main.o graphics.o geometry.o glad.o Vector3D.o -o $(exe_file) $(STDFLAGS) $(CFLAGS) $(MATHFLAG) $(OGLFLAGS)
#main.o: main.cpp
#	$(CC) -c main.cpp $(CFLAGS)
#graphics.o: graphics.cpp
#	$(CC) -c graphics.cpp $(CFLAGS)
#geometry.o: geometry.cpp
#	$(CC) -c geometry.cpp $(CFLAGS)
#Vector3D.o: Vector3D.cpp
#	$(CC) -c Vector3D.cpp $(CFLAGS)
#glad.o: glad/glad.c
#	$(CC) -c glad/glad.c $(CFLAGS)

#clean:
#	rm -f *.o $(exe_file).exe

#.PHONY: clean

