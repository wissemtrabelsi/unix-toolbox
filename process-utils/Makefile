CC = gcc
CFLAGS = -W -Wall -Wextra -Werror -std=c18
SRC = src/main.c src/ptree.c src/pwatch.c src/sig.c src/utils.c
TARGET = putil

all:$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

test: $(TARGET)
	bash tests/test.sh

clean:
	rm -f $(TARGET)

.PHONY: all test clean