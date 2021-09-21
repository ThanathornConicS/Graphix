CXX			:= g++
CXX_FLAGS	:= -std=c++17 -ggdb

BIN 		:= bin
SRC			:= src
INCLUDE 	:= include

LIBRARIES	:= lib
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE):	$(SRC)/*.cpp $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ -L$(LIBRARIES) -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

clean:
	-rm $(BIN)/*