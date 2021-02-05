/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:46:28 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/05 21:46:39 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	print_sources(void *data)
{
	ft_printf("%s\n", *(size_t*)data);
}

void	print_ssl(t_ssl *ssl)
{
	size_t i;

	ft_printf("Hash funcion: %s\nOptions: %lu\nSources: %d\n",
	ssl->hash_func.name, ssl->options, ssl->sources->size);
	i = 0;
	while (i < ssl->sources->size)
	{
		ft_printf("%d: %s\n", i + 1,
		*(size_t*)ft_da_get_pointer(ssl->sources, i));
		++i;
	}
}

void	free_data(void *data)
{
	free((char*)*(size_t*)data);
}

void	free_ssl(t_ssl **ssl)
{
	if (ssl != NULL && *ssl != NULL)
	{
		ft_da_iter((*ssl)->sources, &free_data);
		ft_da_delete(&(*ssl)->sources);
		ft_bzero(*ssl, sizeof(t_ssl));
		free(*ssl);
	}
}