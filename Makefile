CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c common.c create.c dispaly.c search.c save.c update.c

OBJ = $(SRC:.c=.o)

TARGET = a.out

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)