CXX = clang++
CXXFLAGS = -std=gnu++14 -Wall -Wextra -pedantic -g
FONTES = main.cpp Biblioteca.cpp Loja.cpp
PROGRAMA = main

all: $(PROGRAMA)

$(PROGRAMA): $(FONTES) Biblioteca.h Loja.h
	$(CXX) $(CXXFLAGS) $(FONTES) -o $(PROGRAMA)

run: $(PROGRAMA)
	./$(PROGRAMA)

clean:
	rm -f $(PROGRAMA)
