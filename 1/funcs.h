#ifndef FUNCS_H
#define FUNCS_H
#define STR_MAX_LEN 50
#define MAX_FRACTION_1 35
#define MAX_FRACTION_2 40

struct real_t
{
    char sign_f;
    int fraction[MAX_FRACTION_1 + MAX_FRACTION_2];
    size_t len_f;
    int exp;
    int point_ind;
};

int read_str(char *str, const size_t max_f);
int real_parse(struct real_t *real, char *buff, const size_t max_f);
int check_exponent (const struct real_t *real);
void normalize(struct real_t *real);
void delete_extra_zeroes(struct real_t *real);
struct real_t multiply_real(struct real_t *real1, struct real_t *real2);
void round_fraction(struct real_t *real);
void print_real(const struct real_t *real);
#endif
