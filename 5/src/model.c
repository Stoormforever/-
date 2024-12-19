#include "model.h"

#define ALL_QUERIES 1000

#define MAX_ARR_LEN 100

#define EPS 1e-8

#define T1_IN_B 1
#define T1_IN_E 5
 
#define T2_IN_B 0
#define T2_IN_E 3

#define T1_OUT_B 0
#define T1_OUT_E 4

#define T2_OUT_B 0
#define T2_OUT_E 1


double min(double time1, double time2)
{
    if (fabs(time1) < EPS)
        return time2;
    if (fabs(time2) < EPS)
        return time1;
    if (time1 < time2)
        return time1;
    else
        return time2;
}


int arr_model(void)
{
    printf("Реализация очередью-массивом\n");
    arr_queue_t queue1 = arr_queue_create();
    arr_queue_t queue2 = arr_queue_create();
    int rc = 0;

    int queries_in = 0;
    int queries_out = 0;
    int q1_in = 0, q2_in = 0;
    int q1_out = 0, q2_out = 0;
    int sum_len_1 = 0, sum_len_2 = 0;
    int q1_len = 0, q2_len = 0;
    double time = 0.0;
    double stop_time = 0.0;
    double q_time1 = 0.0;
    double q_time2 = 0.0;
    double oa_time = 0.0;
    short int qtype = 0;

    while (q1_out < ALL_QUERIES)
    {
        if (fabs(q_time1) < EPS || q_time1 < 0)
        {
            q_time1 = rand_time(T1_IN_B, T1_IN_E);
            if ((rc = arr_queue_push(queue1, 1)))
                return rc;
            sum_len_1 += q1_len;
            queries_in++;
            q1_len++;
            q1_in++;
        }
        if (fabs(q_time2) < EPS || q_time2 < 0)
        {
            q_time2 = rand_time(T2_IN_B, T2_IN_E);
            if ((rc = arr_queue_push(queue2, 2)))
                return rc;
            sum_len_2 += q2_len; 
            queries_in++;
            q2_len++;
            q2_in++;
        }
        if (fabs(oa_time) < EPS || oa_time < 0)
        {
            if (qtype == 1 && q1_out % 100 == 0 && q1_out != 0)
            {
                int avg_qlen_1 = sum_len_1 / q1_in;
                int avg_qlen_2 = sum_len_2 / q2_in;

                double avg_q1_time = avg_qlen_1 * (T1_IN_B + T1_IN_E) / 2;
                double avg_q2_time = avg_qlen_2 * (T2_IN_B + T2_IN_E) / 2;

                printf("Очередь1 :\n");
                printf("  Текущая длина очереди: %d\n", q1_len);
                printf("  Средняя длина очереди: %d\n", avg_qlen_1);
                printf("  Кол-во вошедших заявок: %d\n", q1_in);
                printf("  Кол-во вышедших заявок: %d\n", q1_out);
                printf("  Среднее время пребывания в очереди: %lf\n", avg_q1_time);
                printf("Очередь2 :\n");
                printf("  Текущая длина очереди: %d\n", q2_len);
                printf("  Средняя длина очереди: %d\n", avg_qlen_2);
                printf("  Кол-во вошедших заявок: %d\n", q2_in);
                printf("  Кол-во вышедших заявок: %d\n", q2_out);
                printf("  Среднее время пребывания в очереди: %lf\n", avg_q2_time);
            }
            if (q2_len > 0 && q1_len == 0)
            {
                if ((rc = arr_queue_pop(queue2)))
                    return rc;
                sum_len_2 += q2_len; 
                q2_len--;
                queries_out++;
                q2_out++;
                qtype = 2;

                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
            }
            else if (q1_len > 0)
            {
                if ((rc = arr_queue_pop(queue1)))
                    return rc;
                sum_len_1 += q1_len;
                q1_len--;
                queries_out++;
                q1_out++;
                qtype = 1;

                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
            }
            else
                stop_time += min(q_time1, q_time2);
        }
        double min_time = min(min(q_time1, q_time2), min(q_time2, oa_time));

        time += min_time;

        q_time1 -= min_time;
        q_time2 -= min_time;
        oa_time -= min_time;    
    }
    
    double avg_q1_in = (T1_IN_B + T1_IN_E) / 2 * ALL_QUERIES;
    double avg_q1_out = (T1_OUT_B + T1_OUT_E) / 2 * ALL_QUERIES;

    double estimate_model_time;

    if (avg_q1_in > avg_q1_out)
        estimate_model_time = avg_q1_in;
    else
        estimate_model_time = avg_q1_out;

    double percent = fabs((time - estimate_model_time) * 100 / estimate_model_time);

    printf("\n------------------------------------\n");
    printf("Общее кол-во вошедших заявок 1-го типа : %d\n", q1_in);
    printf("Общее кол-во вышедших заявок 1-го типа : %d\n", q1_out);
    printf("Общее кол-во вошедших заявок 2-го типа : %d\n", q2_in);
    printf("Общее кол-во вышедших заявок 2-го типа : %d\n", q2_out);
    printf("Общее время моделирования              : %lf\n", time);
    printf("Погрешность моделирования              : %lf\n", percent);
    printf("Общее время простоя                    : %lf\n", stop_time);

    arr_queue_destroy(queue1);
    arr_queue_destroy(queue2);

    return ERR_OK;
}

int list_model(void)
{
    printf("Реализация очередью-массивом\n");
    list_queue_t queue1 = list_queue_create();
    list_queue_t queue2 = list_queue_create();
    int rc = 0;

    int queries_in = 0;
    int queries_out = 0;
    int q1_in = 0, q2_in = 0;
    int q1_out = 0, q2_out = 0;
    int sum_len_1 = 0, sum_len_2 = 0;
    int q1_len = 0, q2_len = 0;
    double time = 0.0;
    double stop_time = 0.0;
    double q_time1 = 0.0;
    double q_time2 = 0.0;
    double oa_time = 0.0;
    short int qtype = 0;
    void *arr[MAX_ARR_LEN];
    size_t arr_len = 0;

    while (q1_out < ALL_QUERIES)
    {
        if (fabs(q_time1) < EPS || q_time1 < 0)
        {
            q_time1 = rand_time(T1_IN_B, T1_IN_E);
            if ((rc = list_queue_push(queue1, 1)))
                return rc;
            sum_len_1 += q1_len;
            queries_in++;
            q1_len++;
            q1_in++;
        }
        if (fabs(q_time2) < EPS || q_time2 < 0)
        {
            q_time2 = rand_time(T2_IN_B, T2_IN_E);
            if ((rc = list_queue_push(queue2, 2)))
                return rc;
            sum_len_2 += q2_len; 
            queries_in++;
            q2_len++;
            q2_in++;
        }
        if (fabs(oa_time) < EPS || oa_time < 0)
        {
            if (arr_len == 100)
            {
                int choice;
                printf("Вывести ли массив адресов(0 - нет, 1- да):");
                if (scanf("%d", &choice) != 1 || choice > 1 || choice < 0)
                    printf("не верный ввод");
                if (choice == 1)
                {
                    for (size_t i = 0; i < arr_len; i++)
                        printf("%p\n", arr[i]);
                }
            
                arr_len = 0;
            }
            if (qtype == 1 && q1_out % 100 == 0 && q1_out != 0)
            {
                int avg_qlen_1 = sum_len_1 / q1_in;
                int avg_qlen_2 = sum_len_2 / q2_in;

                double avg_q1_time = avg_qlen_1 * (T1_IN_B + T1_IN_E) / 2;
                double avg_q2_time = avg_qlen_2 * (T2_IN_B + T2_IN_E) / 2;

                printf("Очередь1 :\n");
                printf("  Текущая длина очереди: %d\n", q1_len);
                printf("  Средняя длина очереди: %d\n", avg_qlen_1);
                printf("  Кол-во вошедших заявок: %d\n", q1_in);
                printf("  Кол-во вышедших заявок: %d\n", q1_out);
                printf("  Среднее время пребывания в очереди: %lf\n", avg_q1_time);
                printf("Очередь2 :\n");
                printf("  Текущая длина очереди: %d\n", q2_len);
                printf("  Средняя длина очереди: %d\n", avg_qlen_2);
                printf("  Кол-во вошедших заявок: %d\n", q2_in);
                printf("  Кол-во вышедших заявок: %d\n", q2_out);
                printf("  Среднее время пребывания в очереди: %lf\n", avg_q2_time);
            }
            if (q2_len > 0 && q1_len == 0)
            {
                if ((rc = list_queue_pop(queue2, &arr[arr_len])))
                    return rc;
                arr_len++;
                sum_len_2 += q2_len; 
                q2_len--;
                queries_out++;
                q2_out++;
                qtype = 2;

                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
            }
            else if (q1_len > 0)
            {
                if ((rc = list_queue_pop(queue1, &arr[arr_len])))
                    return rc;
                arr_len++;
                sum_len_1 += q1_len;
                q1_len--;
                queries_out++;
                q1_out++;
                qtype = 1;

                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
            }
            else
                stop_time += min(q_time1, q_time2);
        }
        double min_time = min(min(q_time1, q_time2), min(q_time2, oa_time));

        time += min_time;

        q_time1 -= min_time;
        q_time2 -= min_time;
        oa_time -= min_time;    
    }
    
    double avg_q1_in = (T1_IN_B + T1_IN_E) / 2 * ALL_QUERIES;
    double avg_q1_out = (T1_OUT_B + T1_OUT_E) / 2 * ALL_QUERIES;

    double estimate_model_time;

    if (avg_q1_in > avg_q1_out)
        estimate_model_time = avg_q1_in;
    else
        estimate_model_time = avg_q1_out;

    double percent = fabs((time - estimate_model_time) * 100 / estimate_model_time);

    printf("\n------------------------------------\n");
    printf("Общее кол-во вошедших заявок 1-го типа : %d\n", q1_in);
    printf("Общее кол-во вышедших заявок 1-го типа : %d\n", q1_out);
    printf("Общее кол-во вошедших заявок 2-го типа : %d\n", q2_in);
    printf("Общее кол-во вышедших заявок 2-го типа : %d\n", q2_out);
    printf("Общее время моделирования     : %lf\n", time);
    printf("Погрешность моделирования     : %lf\n", percent);
    printf("Общее время простоя           : %lf\n", stop_time);

    list_queue_destroy(queue1);
    list_queue_destroy(queue2);

    return ERR_OK;
}