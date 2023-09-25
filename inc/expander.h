#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"

// expander.c
void	expander(t_data *data, char *input);
char	*expander_time(t_data *data, char *input, int i);
char	*expand_input(char *input, int index, char *value, int var_len);

// expander_utils.c
bool	toggle_bool(bool ian);
int		is_quoted_dollarsign(t_data *data, char *input, int i);
char	*get_value(t_data *data, char *input, int start, int len);
int		get_var_len(char *input, int i);

#endif