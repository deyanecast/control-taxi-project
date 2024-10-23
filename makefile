CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11

SRC = src/main.cpp src/cliente.cpp src/reserva.cpp src/utilidades.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = bin/project_algorithms
CFLAGS = -g

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
