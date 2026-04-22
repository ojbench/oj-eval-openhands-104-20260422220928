CXX ?= g++
CXXFLAGS ?= -std=gnu++11 -O2 -pipe -s
LDFLAGS ?=
SRC = main.cpp
BIN = code

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	 rm -f $(BIN) *.o
