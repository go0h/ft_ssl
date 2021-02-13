/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:51:57 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:32:42 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash_func	g_funcs[] = {
	{"MD5", &ft_md5_init, &ft_md5, &ft_get_md5_hash, 16},
	{"SHA256", &ft_sha256_init, &ft_sha256, &ft_get_sha256_hash, 32},
	{"SHA224", &ft_sha224_init, &ft_sha224, &ft_get_sha224_hash, 28},
	{"SHA512", &ft_sha512_init, &ft_sha512, &ft_get_sha512_hash, 64},
	{"SHA384", &ft_sha384_init, &ft_sha384, &ft_get_sha384_hash, 48},
	{"SHA512-256", &ft_sha512_256_i, &ft_sha512_256, &ft_get_sha512_256_h, 32},
	{"SHA512-224", &ft_sha512_224_i, &ft_sha512_224, &ft_get_sha512_224_h, 28}
};

static t_hash_func	get_hash_func(char *param)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_funcs) / sizeof(t_hash_func))
	{
		if (!ft_strcmp_ignore_case(param, g_funcs[i].name))
			break ;
		else if (!ft_strcmp(param, "-h"))
			ft_error_handle(NULL, USAGE);
		++i;
	}
	if (i == sizeof(g_funcs) / sizeof(t_hash_func))
		ft_error_handle(param, INVALID_OPTION);
	return (g_funcs[i]);
}

static size_t		count_files(int ac, char **av)
{
	int		i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (i < ac)
	{
		if (*av[i] != '-')
			++cnt;
		++i;
	}
	return (cnt);
}

/*
**	./ft_ssl md5 -s string
**	./ft_ssl md5 -p STDIN
**	./ft_ssl md5 -q
**	./ft_ssl md5 -r
*/

t_ssl				ft_parse_params(int ac, char **av)
{
	t_ssl	ssl;

	ft_bzero(&ssl, sizeof(t_ssl));
	if (ac < 2)
		ft_error_handle(NULL, USAGE);
	ssl.hash_func = get_hash_func(av[1]);
	if (ac > 2)
	{
		ssl.options = ft_options(ac - 1, &av[1]);
		ssl.files = count_files(ac - 2, &av[2]);
	}
	return (ssl);
}
