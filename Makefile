CC = gcc

CFLAGS = -Wall -Wextra -std=c99

TARGET = mario_kart_gp

SRCS = main.c pilotos.c karts.c itens.c corridas.c historico.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)