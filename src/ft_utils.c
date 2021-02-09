/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:46:28 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/09 21:58:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void		print_ssl(t_ssl *ssl)
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

uint32_t	rot_l(uint32_t num, int shift)
{
	return (num << shift | (num >> (32 - shift)));
}

uint32_t	rot_r(uint32_t num, int shift)
{
	return (num >> shift | (num << (32 - shift)));
}

u_int64_t	swap_8_bytes(u_int64_t n)
{
	return ((n & 0xffULL) << 56 |
			(n & 0xff00ULL) << 40 |
			(n & 0xff0000ULL) << 24 |
			(n & 0xff000000ULL) << 8 |
			(n & 0xff00000000ULL) >> 8 |
			(n & 0xff0000000000ULL) >> 24 |
			(n & 0xff000000000000ULL) >> 40 |
			(n & 0xff00000000000000ULL) >> 56);
}

u_int32_t	swap_4_bytes(u_int32_t n)
{
	return ((n & 0xffULL) << 24 |
			(n & 0xff00ULL) << 8 |
			(n & 0xff0000ULL) >> 8 |
			(n & 0xff000000ULL) >> 24);
}
