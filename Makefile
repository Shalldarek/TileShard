TARGET  = tileshard
CXX     = g++
CC      = gcc
CFLAGS   = -Wall -g -I. -I./modules -I./modules/include
CXXFLAGS = -Wall -g -I. -I./modules -I./modules/include
LDFLAGS  = -lsqlite3

CPP_SOURCES = $(wildcard worker/src/*.cpp)
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

C_SOURCES = $(wildcard modules/src/*.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS)

$(TARGET): $(OBJECTS)
	@echo "=== Linking: $(OBJECTS) ==="
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "=== Done! Run: ./$(TARGET) ==="

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned"

info:
	@echo "CPP_SOURCES: $(CPP_SOURCES)"
	@echo "C_SOURCES:   $(C_SOURCES)"
	@echo "OBJECTS:     $(OBJECTS)"
