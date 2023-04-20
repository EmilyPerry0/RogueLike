TARGET = rogueLike
SRC_FILES = main.cpp Game.hpp Item.hpp

# DO NOT EDIT BELOW HERE
CXX = g++
CFLAGS = -Wall -g -std=c++17
OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

# DEPENDENCIES
Item.o: Item.hpp
Game.o: Game.hpp Item.hpp
main.o: main.cpp Game.hpp