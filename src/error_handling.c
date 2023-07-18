#include "error_handling.h"

int ft_error(char *msg, t_data *data)
{
    ft_putstr_fd(msg, 2);
    if (data)
        ft_exit(data);
    return(FAIL);
}

void ft_exit(t_data *data)
{
    if (data->input)
        free_null(data->input);
}

void    free_null(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}
