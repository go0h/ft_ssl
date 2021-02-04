/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:22:22 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/04 18:27:57 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void			usage(t_error err, char *opt)
{
	if (err == USAGE)
	{
		ft_printf("Usage: ./ft_ssl_md5 hash_func [pqrs]\n\n");
		ft_printf("\t-h - for pritn this help\n");
		ft_printf("\t-p - echo STDIN to STDOUT and append the checksum to STDOUT\n");
		ft_printf("\t-q - quiet mode\n");
		ft_printf("\t-r - reverse the format of the output\n");
		ft_printf("\t-s - print the sum of the given string\n");
		ft_printf("Allowed hash functions:\n");
		ft_printf("\tmd5    - Message Digest 5\n");
		ft_printf("\tsha256 - Secure Hash Algorithm\n");
	}
	else if (err == INVALID_OPTION)
	{
		ft_printf("./ft_ssl_md5: invalid option -- '%s'\n", opt);
		ft_printf("Try './ft_ssl_md5 -h' for more information.\n");
	}
	exit(err);
}

static int		check_flags(char *flags, size_t options)
{
	while (*flags && options)
	{
		if (*flags > 96 && *flags < 123)
		{
			if ((options >> (*flags - 71)) & 1)
				options ^= (1L << (*flags - 71));
		}
		else if (*flags > 64 && *flags < 91)
		{
			if ((options >> (*flags - 65)) & 1)
				options ^= (1L << (*flags - 65));
		}
		else if (*flags > 47 && *flags < 58)
		{
			if ((options >> (*flags + 4)) & 1)
				options ^= (1L << (*flags + 4));
		}
		flags++;
	}
	return (options ? 0 : 1);
}

static int		check_option(char *str, size_t *options)
{
	int			i;

	if (str[0] == '-')
	{
		i = 1;
		if (str[i] == 'h')
			return (1);
		while (str[i])
		{
			if (str[i] > 96 && str[i] < 123)
				*options |= (1L << (str[i] - 71));
			else if (str[i] > 64 && str[i] < 91)
				*options |= (1L << (str[i] - 65));
			else if (str[i] > 47 && str[i] < 58)
				*options |= (1L << (str[i] + 4));
			else
				return (-1);
			++i;
		}
		return (0);
	}
	return (2);
}

size_t			options(int ac, char **av)
{
	int			i;
	int			ret;
	size_t		options;

	i = 2;
	options = 0;
	while (i < ac)
	{
		if ((ret = check_option(av[i], &options)) == 1)
			usage(USAGE, NULL);
		else if (ret == -1)
			usage(INVALID_OPTION, av[i]);
		else if (ret == 2)
			return (options);
		++i;
	}
	if (!check_flags("pqrs", options))
		usage(USAGE, NULL);
	return (options);
}

