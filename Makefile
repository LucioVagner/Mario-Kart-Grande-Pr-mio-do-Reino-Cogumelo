CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -Iinclude

TARGET = mario_kart_gp

SRCS = src/main.c src/pilotos.c src/karts.c src/itens.c src/corridas.c src/historico.c src/oficina.c src/camp.c src/portabilidade.c

OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET)