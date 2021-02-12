/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:22:22 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/12 21:32:56 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static void		usage(const char *msg, t_error err)
{
	if (err == USAGE)
	{
		ft_printf("Usage: ./ft_ssl_md5 hash_func [pqrs]\n\n");
		ft_printf("\t-h - for pritn this help\n");
		ft_printf("\t-p - echo STDIN to STDOUT and append %s\n",
		"the checksum to STDOUT");
		ft_printf("\t-q - quiet mode\n");
		ft_printf("\t-r - reverse the format of the output\n");
		ft_printf("\t-s - print the sum of the given string\n");
		ft_printf("Allowed hash functions:\n");
		ft_printf("\tmd5    - Message Digest 5\n");
		ft_printf("\tsha256 (224) - Secure Hash Algorithm\n");
		ft_printf("\tsha512 (384) - Secure Hash Algorithm\n");
		ft_printf("\tsha512_256 (224) - Secure Hash Algorithm\n");
	}
	else if (err == INVALID_OPTION)
	{
		ft_printf("./ft_ssl_md5: invalid option -- '%s'\n", msg);
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

/*
**	A - 0	E - 4	I - 8	M - 12	Q - 16	U - 20	Y - 24
**	B - 1	F - 5	J - 9	N - 13	R - 17	V - 21	Z - 25
**	C - 2	G - 6	K - 10	O - 14	S - 18	W - 22
**	D - 3	H - 7	L - 11	P - 15	T - 19	X - 23
**
**	a - 26	e - 30	i - 34	m - 38	q - 42	u - 46	y - 50
**	b - 27	f - 31	j - 35	n - 39	r - 43	v - 47	z - 51
**	c - 28	g - 32	k - 36	o - 40	s - 44	w - 48
**	d - 29	h - 33	l - 37	p - 41	t - 45	x - 49
**
**	0 - 52	2 - 54	4 - 56	6 - 58	8 - 60
**	1 - 53	3 - 55	5 - 57	7 - 59	9 - 61
*/

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

size_t			ft_options(int ac, char **av)
{
	int			i;
	int			ret;
	size_t		options;

	i = 1;
	options = 0;
	while (i < ac)
	{
		if ((ret = check_option(av[i], &options)) == 1)
			usage(NULL, USAGE);
		else if (ret == -1)
			usage(av[i], INVALID_OPTION);
		++i;
	}
	if (!check_flags("pqrs", options))
		usage(NULL, USAGE);
	return (options);
}

void			ft_error_handle(const char *msg, t_error err)
{
	if (err == USAGE || err == INVALID_OPTION)
		usage(msg, err);
	else
	{
		ft_fprintf(STDERR_FILENO, "%s: ", msg);
		perror(NULL);
		if (err == MALLOC)
			exit(EXIT_FAILURE);
	}
}
