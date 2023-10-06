#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"

// expander.c
char	*expander(t_data *data, char *input);
char	*expander_time(t_data *data, char *input, int i);
char	*expand_input(char *input, int index, char *value, int var_len);

// expander_utils.c
int		get_var_len(char *input, int i);
char	*get_value(t_data *data, char *input, int start, int len);
int		is_quoted_dollarsign(t_data *data, char *input, int i);
bool	toggle_bool(bool ian);

// expander_env_var.c
int		is_token(char c);
int		check_for_tokens(char *val);
char	*add_quotes_to_tokens(char *val, int count);

#endif