CC = gcc
CFLAGS = -W -Wall -Wextra -Werror -std=c18 
SRC = src/append.c src/copy.c src/main.c src/reverse.c src/utils.c
TARGET = filetool

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)
