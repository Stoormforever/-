#define DA_INIT_SIZE 1
#define DA_STEP 2

#include "dynamic_array.h"

struct dyn_array_t
{
    void *(*data);
    size_t len;
    size_t allocated;
};

address_arr_t init_da_array(void)
{
	address_arr_t parr;

	parr = malloc(sizeof(struct dyn_array_t));
	if (parr)
	{
		parr->data = NULL;
		parr->len = 0;
		parr->allocated = 0;
	}

	return parr;
}

int da_append(address_arr_t parr, int *elem)
{
	if (!parr->data)
	{
		parr->data = malloc(DA_INIT_SIZE * sizeof(parr->data[0]));
		if (!parr->data)
			return ALLOCATION_ERROR;
		parr->allocated = DA_INIT_SIZE;
	}
	else
	{
		if (parr->len >= parr->allocated)
		{
			void *tmp = realloc(parr->data, parr->allocated * DA_STEP * sizeof(parr->data[0]));
			if (!tmp)
				return ALLOCATION_ERROR;
			parr->data = tmp;
			parr->allocated *= DA_STEP;
		}
	}
    parr->data[parr->len] = elem;
    parr->len++;
    return ERR_OK;
}

void da_make_empty(address_arr_t parr)
{
	free(parr->data);

	parr->data = NULL;
	parr->allocated = 0;
	parr->len = 0;
}

void da_destroy(address_arr_t parr)
{
	da_make_empty(parr);
	
	free(parr);
}

void da_print(const address_arr_t parr)
{
    printf("Освобожденные адресса: \n");
	for (size_t i = 0; i < parr->len; i++)
        printf("%p ", parr->data[i]);
    printf("\n");
}