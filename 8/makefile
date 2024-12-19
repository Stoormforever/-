# Компилятор
CC := gcc

## Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -ggdb -Iinc -lm
## Объектные файлы программы
OBJS_MAIN := out/queue_impl.o out/graph.o out/menu.o out/main.o

ifeq ($(DEBUG),FALSE)
	MODE = -g0
else
	MODE = -g3
endif

app.exe : out/ | $(OBJS_MAIN)
	$(CC) -o $@ $(OBJS_MAIN)

out/%.o : src/%.c
	$(CC) $(CFLAGS) $(MODE) -c $< -o $@

out/:
	mkdir $@

.PHONY : clean
clean :
	rm *.exe out/*
