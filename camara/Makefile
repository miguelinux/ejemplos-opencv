SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
TARGET=programa

CXXFLAGS+= `pkg-config --cflags opencv`
CXXFLAGS+= -Wall -Wextra

OCVLIBS=`pkg-config --libs opencv`

.PHONY: all
all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ $(OCVLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS) *~


