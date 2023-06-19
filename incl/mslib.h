/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:06:39 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/19 20:36:03 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSLIB_H
# define MSLIB_H

# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<fcntl.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<sys/ioctl.h>
# include<signal.h>
# include<dirent.h>
# include<termios.h>
# include<curses.h>
# include<term.h>

# include"../libft/libft.h"

// ? Global var
int	g_return_status;

typedef struct s_quotes {
	int	quote;
	int	miniquote;
}	t_quotes;

typedef struct s_separator {
	int		index;
	char	*separator;
	char	*prev_token;
	char	*next_token;
}	t_separator;

typedef struct s_cmd {
	int				index;
	int				argc;
	char			**argv;
	int				is_separator;
	struct s_cmd	*next;	
}	t_cmd;

typedef struct s_counters {
	int				c1;
	int				c2;
}	t_counters;

typedef struct s_vars
{
	char			*input;
	int				looping;
	t_quotes		*quotes;
	t_counters		*c;
	char			**envar;
	char			*prompt;
	char			*inpli;
	char			**inpcomm;
	char			**tokens;
	int				inplen;
	int				sigbool;
	char			**paths;
	char			**cmd_buffer;
	t_cmd			*cmd;
}	t_vars;

// Utils

char	*msh_strjoinchr(char *str, char ch);
void	msh_update_quotes_status(t_quotes *quotes, char c);
void	msh_init_quotes_struct(t_quotes *quote_struct);
int		msh_no_quotes(t_quotes *quotes);
char	*msh_free_return_null(char *ptr);
int		msh_cmd_is_built_in(t_cmd *cmd);

// Helpers

void	msh_print_element(char *input, int start, int end);
void	msh_debug_cmd_list(t_cmd *first);
void	msh_print_env_vars(t_vars *vars, char *str);


//env parser

int		msh_store_env_own_vars(t_vars *vars, char **envp);
int		msh_store_env_own_lines(t_vars *vars, char **envp, int index);


//Parser

char	*msh_sanitize_input(char *str);
char	*msh_clean_irrelveant_spaces_in_input(char *input);
int		msh_malformed_quotes(char *input);


// Validators

int		msh_chr_can_be_separator(char c);
int		msh_is_startarg(char *input, int c, t_quotes *quotes);
int		msh_is_endarg(char *input, int c, t_quotes *quotes);

// Tokenizer-ish

char	**msh_split_cmd_argvs(char *input, int argc);
int		msh_count_tokens(char *input);
char	**msh_prepare_splitted_input_in_cmds(t_vars *vars);
t_cmd	*msh_tokenize(t_vars *vars);
int		msh_how_many_argv_have_the_cmd(char *input);


// Destroyers

void	msh_free_cmd_list(t_cmd *first);
void	msh_free_raw_array(char **arr);
void	msh_free_envar(t_vars *vars);
void	msh_free_ptr(void *ptr);

//  * Built ins
void	msh_exec_builtin(t_cmd *cmd, t_vars *vars);

// ? exit built in
void	msh_exec_exit(t_cmd *cmd, t_vars *vars);

// ? echo built in
void	msh_exec_echo(t_cmd *cmd, t_vars *vars);
int		msh_echo_has_n_flag(char *arg);
void	msh_echo_print(char **args, int n_flags, int index);

// ? env builtin
void	msh_exec_env(t_cmd *cmd, t_vars *vars);
int		is_valid_env_var_key(char *var_name); // ? more like utils for env

// ? pwd builtin
void	msh_exec_pwd(t_cmd *cmd, t_vars *vars);
int		msh_get_env_index(t_vars *vars, char *env_name); // ? more like utils for env
void	msh_print_env_value(t_vars *vars, int env_index); // ? more like utils for env
char	*msh_get_env_value(t_vars *vars, int env_index); // ? more like utils for env

// ? cd builtin
void	msh_exec_cd(t_cmd *cmd, t_vars *vars);
void	msh_cd_go_home(t_vars *vars);
int		msh_cd_change_dir(t_vars *vars, char *path);

// ? unset builtin
void	msh_exec_unset(t_cmd *cmd, t_vars *vars);

// ? export builtin
void	msh_exec_export(t_cmd *cmd, t_vars *vars);

// Executions
int		msh_execute_start(t_vars *vars);
int		msh_cmd_execute(t_vars *vars);
char	*msh_getpath_cmd(t_vars *vars, char *cmd);
char	*msh_getpath_line(char **envp);
void	msh_getpath(t_vars *vars, char **envp);

#endif