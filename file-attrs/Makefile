CC = gcc
CFLAGS = -W -Wall -Wextra -Werror -std=c18
SRC = src/attrib.c src/ln.c src/main.c src/utils.c
TARGET = lx
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
test: $(TARGET)
	bash tests/test.sh
clean:
	rm -rf *.o lx