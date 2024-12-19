#include <stdio.h>
#include "funcs.h"

int main(void)
{
    char str1[STR_MAX_LEN + 2];
    char str2[STR_MAX_LEN + 2];
    int rc;
    if ((rc = read_str(str1, MAX_FRACTION_1)))
        return rc;
    if ((rc = read_str(str2, MAX_FRACTION_2)))
        return rc;
    
    struct real_t real1;
    struct real_t real2;
    if ((rc = real_parse(&real1, str1, MAX_FRACTION_1)))
        return rc;
    if ((rc = real_parse(&real2, str2, MAX_FRACTION_2)))
        return rc;
    if ((rc = check_exponent(&real1)))
        return rc;
    if ((rc = check_exponent(&real2)))
        return rc;
    if (real1.point_ind >= 0)
        normalize(&real1);
    if (real2.point_ind >= 0)
        normalize(&real2);

    struct real_t real = multiply_real(&real1, &real2);
    if ((rc = check_exponent(&real)))
        return rc;
    if (real.len_f > MAX_FRACTION_2)
        round_fraction(&real);
    delete_extra_zeroes(&real);

    print_real(&real);

    return 0;
}
