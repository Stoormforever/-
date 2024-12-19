#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"
#define EXP_BUFF_LEN 5
#define INPUT_ERROR 1
#define RANGE_ERROR 2
#define TYPE_ERROR 3
#define FRACTION_OVERFLOW 4
#define EXP_OVERFLOW 5

int read_str(char *str, const size_t max_f)
{

    printf("Введите вещественное число в формате [+-]m.n E [+-]K, \n\
где длина m + n <= %zu и длина k<=5, \n\
пробелы только до и после заглавной E по 1:\n\
----|----|----|----|----|----|----|----|\n", max_f);
    if (!fgets(str, STR_MAX_LEN + 2, stdin))
    {
        printf("Ошибка ввода");
        return INPUT_ERROR;
    }
    size_t str_len;
    str_len = strlen(str);
    if (str[str_len - 1] == '\n')
        str[str_len - 1] = 0;
    else
    {
        printf("Не верная длинна строки");
        return RANGE_ERROR;
    }
    if (strlen(str) == 0)
    {
        printf("Ошибка ввода");
        return INPUT_ERROR;
    }

    return 0;
}

int real_parse(struct real_t *real, char *str, const size_t max_f)
{
    int exp = 0;
    char sign_e;
    char exp_buff[EXP_BUFF_LEN + 1];
    size_t exp_len = 0;
    size_t len_f = 0;
    real->sign_f = '+';
    real->point_ind = -1;

    char *ptr = str;
    if (*ptr == '-' || *ptr == '+')
    {
        real->sign_f = *ptr;
        ptr++;
    }
    int significant = 0;
    int point_count = 0;
    while (*ptr && *ptr != ' ')
    {
        if (!isdigit(*ptr) && *ptr != '.')
        {
            printf("Не корректный ввод числа");
            return TYPE_ERROR;
        }
        if (*ptr == '.')
        {
            real->point_ind = len_f;
            significant = 1;
            point_count++;
        }
        else if (significant || *ptr != '0')
        {
            real->fraction[len_f] = *ptr - '0';
            len_f++;
            significant = 1;
        }
        if (len_f > max_f)
        {
            printf("Переполнение мантиссы");
            return FRACTION_OVERFLOW;
        }
        if (point_count > 1)
        {
            printf("Не корректный ввод числа");
            return TYPE_ERROR;
        }
        ptr++;
    }

    if (*ptr && !strncmp(ptr, " E ", 3))
    {
        ptr += 3;
        if (!*ptr)
        {
            printf("Не корректный ввод числа");
            return TYPE_ERROR;
        }
        if (*ptr == '-' || *ptr == '+')
        {
            sign_e = *ptr;
            ptr++;
        }
        while (isdigit(*ptr))
        {
            exp_buff[exp_len] = *ptr;
            if (exp_len > 5)
            {
                printf("Переполнение порядка");
                return EXP_OVERFLOW;
            }
            exp_len++;
            ptr++;
        }
    
        if (exp_len == 0 || *ptr)
        {
            printf("Не корректный ввод числа");
            return TYPE_ERROR;
        }
        int k = 1;
        for (int i = exp_len - 1; i >= 0; i--)
        {
            exp += k * (exp_buff[i] - '0');
            k *= 10;
        }
    }
    if (sign_e == '-')
        exp *= -1;

    if (len_f == 0)
        real->fraction[0] = 0;

    real->exp = exp;
    real->len_f = len_f;

    return 0;
}

void round_fraction(struct real_t *real)
{
    size_t i = real->len_f - 1;
    for (; i >= MAX_FRACTION_2; i--)
    {
        if (real->fraction[i] >= 5)
            real->fraction[i - 1] += 1;
        real->len_f--;
    }

    for (; real->fraction[i] >= 10 && i != 0; i--)
    {
        real->fraction[i] = 0;
        real->fraction[i - 1] += 1;
    }
    if (real->fraction[i] >= 10)
    {
        real->fraction[i] = 1;
       real->exp +=1;
    }
}

int check_exponent (const struct real_t *real)
{
    if (real->exp > 99999 || real->exp < -99999)
    {
        printf("Переполнение порядка");
        return EXP_OVERFLOW;
    }

    return 0;
}

void normalize(struct real_t *real)
{
    delete_extra_zeroes(real);
    real->exp -= real->len_f - real->point_ind;
    if (real->point_ind == 0)
    {
        size_t i = 0;
        for (; real->fraction[i] == 0 && i < real->len_f; i++);
        if (i != 0)
        {
            size_t k = 0;
            for (; i < real->len_f; i++)
            {
                real->fraction[k] = real->fraction[i];
                k++;
            }
            real->len_f = k;
        }
    }
}

void delete_extra_zeroes(struct real_t *real)
{
    for (size_t i = real->len_f - 1; real->fraction[i] == 0 && i > 0; i--)
        real->len_f--;
}

void reverse_array(int *arr, size_t arr_len)
{
    int temp;
    for(size_t i = 0; i < arr_len / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[arr_len - i - 1];
        arr[arr_len - i - 1] = temp;
    }
}

struct real_t multiply_real(struct real_t *real1, struct real_t *real2)
{
    struct real_t res = {0};
    if (real2->len_f == 0 || real1->len_f == 0)
    {
        res.len_f = 1;
        res.exp = 0;
        res.sign_f = '+';
        return res;
    }

    size_t arr_len = real2->len_f + real1->len_f - 1;

    reverse_array(real1->fraction, real1->len_f);
    reverse_array(real2->fraction, real2->len_f);

    for (size_t i = 0; i < real1->len_f; i++)
        for (size_t j = 0; j < real2->len_f; j++)
            res.fraction[i + j] += real1->fraction[i] * real2->fraction[j];
    for (size_t i = 0; i < arr_len; i++)
        if (res.fraction[i] % 10 != res.fraction[i])
        {
            int digit = res.fraction[i] % 10;
            res.fraction[i + 1] += (res.fraction[i] - digit) / 10;
            res.fraction[i] = digit;
        }
    if (res.fraction[arr_len] != 0)
        arr_len++;
    res.len_f = arr_len;
    res.exp = real1->exp + real2->exp + arr_len;
    if (real1->sign_f == real2->sign_f)
        res.sign_f = '+';
    else
        res.sign_f = '-';
    reverse_array(res.fraction, res.len_f);
    return res;
}

void print_real(const struct real_t *real)
{
    printf("Вычисленное произведение числел:\n----|----|----|----|----|----|----|\n");
    printf("%c0.", real->sign_f);
    for (size_t i = 0; i < real->len_f; i++)
        printf("%d", real->fraction[i]);
    if (real->exp != 0)
    	printf(" E %d", real->exp);
}