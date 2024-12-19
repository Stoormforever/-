# Компилятор
CC := gcc

## Флаги компиляции
CFLAGS := -std=gnu99 -Wall -Werror -pedantic -Wextra -ggdb -Iinc -lm
## Объектные файлы программы
OBJS_MAIN := out/tree_impl.o out/avl_tree.o out/table_impl.o out/menu.o out/main.o

## Обыектные файлы замеров
OBJS_EXP := out/tree_impl.o out/avl_tree.o out/table_impl.o out/table_impl2.o out/timer.o out/time_exp.o

ifeq ($(DEBUG),FALSE)
	MODE = -g0
else
	MODE = -g3
endif

app.exe : out/ | $(OBJS_MAIN)
	$(CC) -o $@ $(OBJS_MAIN)

time_exp.exe : out/ | $(OBJS_EXP)
	$(CC) -o $@ $(OBJS_EXP)

out/%.o : src/%.c
	$(CC) $(CFLAGS) $(MODE) -c $< -o $@

out/:
	mkdir $@

.PHONY : clean
clean :
	rm *.exe out/*
