/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha384.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:31:20 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:36:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha.h"
#include <assert.h>

static uint64_t	g_buf[8];

void			ft_sha384_init(void)
{
	g_buf[A] = 0xcbbb9d5dc1059ed8;
	g_buf[B] = 0x629a292a367cd507;
	g_buf[C] = 0x9159015a3070dd17;
	g_buf[D] = 0x152fecd8f70e5939;
	g_buf[E] = 0x67332667ffc00b31;
	g_buf[F] = 0x8eb44a8768581511;
	g_buf[G] = 0xdb0c2e0d64f98fa7;
	g_buf[H] = 0x47b5481dbefa4fa4;
}

char			*ft_get_sha384_hash(void)
{
	int			i;
	uint64_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint64_t) * 8)))
		return (NULL);
	i = 0;
	while (i < 6)
	{
		hash[i] = swap_8_bytes(g_buf[i]);
		++i;
	}
	return ((char*)hash);
}

void			ft_sha384(char *data, size_t cur_size, size_t overall)
{
	size_t		i;
	uint64_t	c[8];

	if (cur_size != BATCH_SIZE)
	{
		if (!(cur_size = allign_sha512_data(&data, cur_size, overall)))
			return ;
	}
	// temporary
	assert(cur_size % 128 == 0);
	i = 0;
	while (i < cur_size)
	{
		ft_memcpy(&c, &g_buf, sizeof(uint64_t) * 8);
		ft_sha512_round((uint64_t*)&data[i], (uint64_t*)&c);
		g_buf[A] += c[A];
		g_buf[B] += c[B];
		g_buf[C] += c[C];
		g_buf[D] += c[D];
		g_buf[E] += c[E];
		g_buf[F] += c[F];
		g_buf[G] += c[G];
		g_buf[H] += c[H];
		i += 128;
	}
	if (cur_size != BATCH_SIZE)
		free(data);
}
