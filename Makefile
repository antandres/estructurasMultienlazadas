TARGET = RUN
LIBS = -lm
CC = g++
CFLAGS = -g

.PHONY: default all clean

default: $(TARGET)
all: default
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -std=c++98 $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o core

cleanall: clean
	-rm -f $(TARGET)