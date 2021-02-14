/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:51 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/14 14:46:50 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	get_param(char *param, t_hash_func *hf)
{
	char		*trimmed;
	t_hash_func	*f_ptr;

	f_ptr = NULL;
	if (!(trimmed = ft_strtrim(param)))
		ft_error_handle(__FUNCTION__, MALLOC);
	if (!ft_strcmp(trimmed, "help"))
		ft_print_md_commands();
	else if (!ft_strcmp(trimmed, "exit"))
	{
		ft_strdel(&trimmed);
		exit(EXIT_SUCCESS);
	}
	else if (!(f_ptr = get_hash_func(trimmed)))
		ft_printf("Invalid option '%s'\nTry 'help' or 'exit'\n", trimmed);
	else
		*hf = *f_ptr;
	ft_strdel(&trimmed);
	return (f_ptr != NULL);
}

static void	process_interactive(void)
{
	int			n;
	char		command[256];
	t_ssl		ssl;

	ft_bzero(&ssl, sizeof(t_ssl));
	ft_printf("ft_ssl> ");
	while ((n = read(STDIN_FILENO, &command, 256)) > 0)
	{
		command[n] = '\0';
		if (get_param(command, &ssl.hash_func))
			process_stdin(&ssl);
		ft_printf("ft_ssl> ");
	}
}

static void	process_args(int ac, char **av)
{
	int		i;
	t_ssl	ssl;

	i = 2;
	ssl = ft_parse_params(ac, av);
	if (!ssl.files && !(ssl.options & (ECHO | STRING)))
		process_stdin(&ssl);
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p") && (ssl.options & ECHO))
			process_stdin(&ssl);
		else if (!ft_strcmp(av[i], "-s") && (ssl.options & STRING))
		{
			if (i + 1 == ac)
				ft_error_handle(av[i], INVALID_OPTION);
			process_string(&ssl, av[++i]);
		}
		else if (ft_strcmp(av[i], "-q") && ft_strcmp(av[i], "-r"))
			process_file(&ssl, av[i]);
		++i;
	}
}

int			main(int argc, char **argv)
{
	if (argc < 2)
		process_interactive();
	else
		process_args(argc, argv);
	return (EXIT_SUCCESS);
}
