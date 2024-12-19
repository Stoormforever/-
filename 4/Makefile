## Компилятор
CC := gcc

## Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -ggdb -Iinc

## Объектные файлы программы
OBJS_MAIN := out/arr_stack.o out/list_stack.o out/dynamic_array.o out/address_io.o out/main.o

## Обыектные файлы замеров
OBJS_EXP := out/arr_stack.o out/list_stack.o out/timer.o out/time_exp.o

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