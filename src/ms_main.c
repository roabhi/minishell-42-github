/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/28 23:07:51 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

// void debug_cmd_list_builtins(t_cmd *first)
// {
// 	t_cmd *tmp;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	tmp = first;
// 	while(tmp)
// 	{
// 		//debugar token
// 		printf("Token %d:\n", i);
// 		printf("argc == %d\n", tmp->argc);
// 		while(tmp->argv[j])
// 		{
// 			printf("El argc[%d] es |%s| y es built-in es = %d\n", j, tmp->argv[j], msh_str_is_built_in(tmp->argv[j]));
// 			j++;
// 		}
// 		printf("\n");		
// 		j = 0;
// 		i++;
// 		tmp = tmp->next;
// 	}
// }

//Global variable
int	g_return_status;

void	msh_sigint_handler(int sig)
{
	if (sig != 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_return_status = 1;
	}
}

void	msh_ignore_signals(t_vars *vars, int ac, char **av)
{
	(void)ac;
	(void)av;
	/*if (ac > 1 || av[1] != NULL)
	{
		printf("ERROR: the program does not take any arguments!");
		exit(1);
	}*/
	vars->sigbool = 1;
	signal(SIGINT, msh_sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

//if sigexec == -1 is unset
//if sigexec == 0 is set to error
//if sigexec == 1 is set to success
void	msh_set_vars(t_vars *vars, char *input)
{
	vars->prompt = ft_calloc(ft_strlen(input) + 1, 1);
	vars->inpli = NULL;
	ft_strlcpy(vars->prompt, input, ft_strlen(input));

}

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;
	//int		looping; // ? This now is a var in struc controlloing the main looping execution

	vars.looping = 1;
	g_return_status = 0;
	msh_ignore_signals(&vars, ac, av);    //Comentar cuando testing
	msh_set_vars(&vars, "msh %  ");
	//free(vars.tokens);


	// for (char **env = envp; *env != 0; env++)
  // {
  //   char *thisEnv = *env;
  //   printf("%s\n", thisEnv);    
  // }

	// ? Capute env vars to hold into own **envar_vars inside struct s_vars
	if (!msh_store_env_own_vars(&vars, envp))
		return (-1);	
	// ? End of caputuring env vars





	// ! Testing mode
	// Test 1: Got to /minishel_tester  and do bash test.sh
	// Test 2: Desde raiz: python3 -m minishell_test
	// https://github.com/thallard/minishell_tester
	// https://github.com/cacharle/minishell_test
	// if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	// {
	// 	vars.inpli = av[2];
	// 	vars.inplen = ft_strlen(vars.inpli);
	// 	vars.input = msh_sanitize_input(vars.inpli);
	// 	if (vars.input == NULL)
	// 		exit(g_return_status);

	// 	vars.cmd = msh_tokenize(&vars);		
	// 	if (vars.cmd != NULL){
	// 		msh_expander(&vars);
	// 		msh_execute_start(&vars);
	// 	}


	// 	msh_free_cmd_list(vars.cmd); // ? free args
	// 	msh_free_raw_array(vars.tokens); // ? free tokens
	// 	free(vars.input); // ? free trimed input);
	// 	msh_free_envars(&vars);
	//   free(vars.prompt);
	// 	exit(g_return_status);
	// }
	// ! End tesyting mode
	
	while (vars.looping)
	{
		vars.looping = 1;
		vars.inpli = readline(vars.prompt);
		if (vars.inpli != NULL)
		{
			if (vars.inpli[0] == '\0')
			{
				free(vars.inpli);
				continue ;
			}
			add_history(vars.inpli);
			vars.input = msh_sanitize_input(vars.inpli);
			if (vars.input == NULL)
				continue ;

			vars.cmd = msh_tokenize(&vars);		
			//msh_debug_cmd_list(vars.cmd); // debug tokens
			//Execution integrando builtins a pipes
			if (vars.cmd != NULL)
			{
				msh_expander(&vars);
				msh_execute_start(&vars);
			}

			//msh_debug_cmd_list(vars.cmd);


			// if(ft_strcmp(vars.cmd->argv[0], "exit") == 0)
				// looping = 0; // ? This is now controlled by its own built in
			//msh_split_cmd_argvs(input);

			//vars.inplen = ft_strlen(vars.inpli);			
			msh_free_cmd_list(vars.cmd); // ? free args
			msh_free_raw_array(vars.tokens); // ? free tokens
			free(vars.input); // ? free trimed input
		}
		else
			vars.looping = 0; // this is ctrl-D exits shell

		//looping = msh_getting_commands(&vars, envp);
		//msh_free_commands(&vars);
}
	msh_free_envars(&vars);
	free(vars.prompt);
	printf("Salgo pro aqui");
	system("leaks minishell"); //para comprobar leaks usar leaks minishell dentro  y quitar esta linea antes de entregar
	return (g_return_status);
}



