/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:51:57 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/08 23:13:40 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static t_hash_func	get_hash_func(char *param)
{
	size_t				i;
	static t_hash_func	funcs[] = {
	{ "md5", &ft_md5_init, &ft_md5, &ft_get_md5_hash, 16 },
	{ "sha256", &ft_sha256_init, &ft_sha256, &ft_get_sha256_hash, 32 } };

	i = 0;
	while (i < sizeof(funcs) / sizeof(t_hash_func))
	{
		if (!ft_strcmp(param, funcs[i].name))
			break ;
		else if (!ft_strcmp(param, "-h"))
			ft_error_handle(NULL, USAGE);
		++i;
	}
	if (i == sizeof(funcs) / sizeof(t_hash_func))
		ft_error_handle(param, INVALID_OPTION);
	return (funcs[i]);
}

static t_darr		*parse_sources(int ac, char **av)
{
	int		i;
	char	*filename;
	t_darr	*srcs;

	i = 0;
	if (!(srcs = ft_da_new(0, sizeof(char*))))
		ft_error_handle(__FUNCTION__, MALLOC);
	while (i < ac)
	{
		if (*av[i] != '-')
		{
			if (!(filename = ft_strdup(av[i])) ||
				!(srcs = ft_da_add(srcs, &filename)))
			{
				ft_strdel(&filename);
				ft_da_iter(srcs, &free_data);
				ft_da_delete(&srcs);
				ft_error_handle(__FUNCTION__, MALLOC);
			}
		}
		++i;
	}
	return (ft_da_shrink(srcs));
}

t_ssl				*ft_parse_params(int ac, char **av)
{
	t_ssl	ssl;
	t_ssl	*p_ssl;

	if (ac < 2)
		ft_error_handle(NULL, USAGE);
	ssl.hash_func = get_hash_func(av[1]);
	if (ac > 2)
		ssl.options = ft_options(ac - 1, &av[1]);
	ssl.sources = parse_sources(ac - 2, &av[2]);
	if (!ssl.sources || !(p_ssl = (t_ssl*)ft_memalloc(sizeof(t_ssl))))
	{
		ft_da_iter(ssl.sources, &free_data);
		ft_da_delete(&ssl.sources);
		ft_error_handle(__FUNCTION__, MALLOC);
	}
	ft_memcpy(p_ssl, &ssl, sizeof(t_ssl));
	return (p_ssl);
}
