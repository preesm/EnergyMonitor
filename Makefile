
PREFIX=/usr/local/

TARGET=EnergyRecorder
INCS=$(wildcard *.h)
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

INCDIRS=
LIBS=

CXX=g++
CXXFLAGS=-O2 -Wall -Wextra
# -Werror

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LIBS)

%.o: %.cpp $(INCS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rfv $(OBJS)

proper: clean
	rm -fv $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	rm -fv $(PREFIX)/bin/$(TARGET)

test: all
	./$(TARGET) testdir
