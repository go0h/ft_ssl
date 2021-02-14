/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:51:57 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/14 14:49:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash_func		g_funcs[] = {
	{"MD5", &ft_md5_init, &ft_md5, &ft_get_md5_hash, 16},
	{"SHA256", &ft_sha256_init, &ft_sha256, &ft_get_sha256_hash, 32},
	{"SHA224", &ft_sha224_init, &ft_sha224, &ft_get_sha224_hash, 28},
	{"SHA512", &ft_sha512_init, &ft_sha512, &ft_get_sha512_hash, 64},
	{"SHA384", &ft_sha384_init, &ft_sha384, &ft_get_sha384_hash, 48},
	{"SHA512-256", &ft_sha512_256_i, &ft_sha512_256, &ft_get_sha512_256_h, 32},
	{"SHA512-224", &ft_sha512_224_i, &ft_sha512_224, &ft_get_sha512_224_h, 28}
};

void			ft_print_md_commands(void)
{
	size_t	i;

	i = 0;
	ft_printf("Message Digest commands:\n");
	while (i < sizeof(g_funcs) / sizeof(t_hash_func))
	{
		ft_printf("%-15s", g_funcs[i].name);
		if (i != 0 && (i + 1) % 4 == 0)
			ft_printf("\n");
		++i;
	}
	ft_printf("\n");
}

t_hash_func		*get_hash_func(char *param)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_funcs) / sizeof(t_hash_func))
	{
		if (!ft_strcmp_ignore_case(param, g_funcs[i].name))
			break ;
		++i;
	}
	if (i == sizeof(g_funcs) / sizeof(t_hash_func))
		return (NULL);
	return (&g_funcs[i]);
}

static size_t	count_files(int ac, char **av)
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

t_ssl			ft_parse_params(int ac, char **av)
{
	t_ssl		ssl;
	t_hash_func	*f_ptr;

	ft_bzero(&ssl, sizeof(t_ssl));
	if (!ft_strcmp(av[1], "-h"))
		ft_error_handle(NULL, USAGE);
	if (!(f_ptr = get_hash_func(av[1])))
		ft_error_handle(av[1], INVALID_OPTION);
	ft_memcpy(&ssl.hash_func, f_ptr, sizeof(t_hash_func));
	if (ac > 2)
	{
		ssl.options = ft_options(ac - 1, &av[1]);
		ssl.files = count_files(ac - 2, &av[2]);
	}
	return (ssl);
}
