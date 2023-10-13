CC = g++
CFLAGS = -std=c++17
SOURCES = main.cpp unit.cpp block.cpp
HEADERS = block.h unit.h size.h frame.h point.h
RECURSIVE_PACKAGING_EXECUTABLE = ../build/unit_packaging_recursive
PACKAGING_EXECUTABLE = ../build/unit_packaging

all: unit_packaging_recursive unit_packaging

unit_packaging_recursive : $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -DRECURSIVE_BLOCK $(SOURCES) -o $(RECURSIVE_PACKAGING_EXECUTABLE)

unit_packaging : $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PACKAGING_EXECUTABLE)

clean:
	rm -rf $(RECURSIVE_PACKAGING_EXECUTABLE) $(PACKAGING_EXECUTABLE)
