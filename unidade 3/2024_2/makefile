CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++20 -Iinclude -g
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = bin/main

TEST_LIB = $(wildcard lib/catch2/*.cpp)
TEST_SOURCES = $(filter-out src/main.cpp, $(SOURCES)) $(wildcard test/*.cpp) 
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o) $(TEST_LIB:.cpp=.o)
TEST_EXECUTABLE = bin/test-all

TEST_SOURCES_INSERIR = $(filter-out src/main.cpp, $(SOURCES)) $(wildcard test/TesteInserir.cpp)
TEST_OBJECTS_INSERIR = $(TEST_SOURCES_INSERIR:.cpp=.o) $(TEST_LIB:.cpp=.o)
TEST_EXECUTABLE_INSERIR = bin/test-inserir

TEST_SOURCES_BUSCAR = $(filter-out src/main.cpp, $(SOURCES)) $(wildcard test/TesteBuscar.cpp)
TEST_OBJECTS_BUSCAR = $(TEST_SOURCES_BUSCAR:.cpp=.o) $(TEST_LIB:.cpp=.o)
TEST_EXECUTABLE_BUSCAR = bin/test-buscar

TEST_SOURCES_REMOVER = $(filter-out src/main.cpp, $(SOURCES)) $(wildcard test/TesteRemover.cpp)
TEST_OBJECTS_REMOVER = $(TEST_SOURCES_REMOVER:.cpp=.o) $(TEST_LIB:.cpp=.o)
TEST_EXECUTABLE_REMOVER = bin/test-remover

TEST_SOURCES_REDIMENSIONAR = $(filter-out src/main.cpp, $(SOURCES)) $(wildcard test/TesteRedimensionar.cpp)
TEST_OBJECTS_REDIMENSIONAR = $(TEST_SOURCES_REDIMENSIONAR:.cpp=.o) $(TEST_LIB:.cpp=.o)
TEST_EXECUTABLE_REDIMENSIONAR = bin/test-redimensionar

all: $(EXECUTABLE) $(TEST_EXECUTABLE) $(TEST_EXECUTABLE_INSERIR) $(TEST_EXECUTABLE_BUSCAR) $(TEST_EXECUTABLE_REMOVER) $(TEST_EXECUTABLE_REDIMENSIONAR)

test: $(TEST_EXECUTABLE) $(TEST_EXECUTABLE_INSERIR) $(TEST_EXECUTABLE_BUSCAR) $(TEST_EXECUTABLE_REMOVER) $(TEST_EXECUTABLE_REDIMENSIONAR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE_INSERIR): $(TEST_OBJECTS_INSERIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE_BUSCAR): $(TEST_OBJECTS_BUSCAR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE_REMOVER): $(TEST_OBJECTS_REMOVER)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE_REDIMENSIONAR): $(TEST_OBJECTS_REDIMENSIONAR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run-test-inserir
run-test-inserir: $(TEST_EXECUTABLE_INSERIR)
	./$(TEST_EXECUTABLE_INSERIR)

.PHONY: run-test-buscar
run-test-buscar: $(TEST_EXECUTABLE_BUSCAR)
	./$(TEST_EXECUTABLE_BUSCAR)

.PHONY: run-test-remover
run-test-remover: $(TEST_EXECUTABLE_REMOVER)
	./$(TEST_EXECUTABLE_REMOVER)

.PHONY: run-test-redimensionar
run-test-redimensionar: $(TEST_EXECUTABLE_REDIMENSIONAR)
	./$(TEST_EXECUTABLE_REDIMENSIONAR)

.PHONY: run-test
run-test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) 

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TEST_OBJECTS_INSERIR) $(TEST_EXECUTABLE_INSERIR) $(TEST_OBJECTS_BUSCAR) $(TEST_EXECUTABLE_BUSCAR) $(TEST_OBJECTS_REMOVER) $(TEST_EXECUTABLE_REMOVER) $(TEST_OBJECTS_REDIMENSIONAR) $(TEST_EXECUTABLE_REDIMENSIONAR) $(TEST_EXECUTABLE)

.PHONY: clean-doc
clean-doc:
	rm -rf ./doc/*

.PHONY: doc
doc:
	doxygen Doxyfile
