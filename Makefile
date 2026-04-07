FILES = src/main.c src/calc.c src/gui.c src/parser.c
CC = gcc
CFLAGS = -Wall -Wextra -I include
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    TARGET = calculator_with_parser
    LIBS = -lm
else
    TARGET = calculator_with_parser.exe
    LIBS =
endif

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIBS) -o $(TARGET)

clean:
	rm -f calculator_with_parser.exe