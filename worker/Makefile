TARGET = tileshard

CXX = g++

LDFLAGS = -lsqlite3

SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)