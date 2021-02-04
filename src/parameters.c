/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:51:57 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/04 20:54:44 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"


t_hash_func	get_hash_func(int ac, char **av)
{
	size_t				i;
	static t_hash_func	funcs[] = {
	{ "md5", &ft_md5 },
	{ "sha256", &ft_sha256 } };

	ac *= 0;
	i = 0;
	while (i < sizeof(funcs) / sizeof(t_hash_func))
	{
		if (!ft_strcmp(av[1], funcs[i].name))
			break;
		++i;
	}
	if (i == sizeof(funcs) / sizeof(t_hash_func))
		usage(INVALID_OPTION, av[1]);
	return (funcs[i]);
}
