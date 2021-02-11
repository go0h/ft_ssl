/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 22:22:24 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:28:07 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha.h"
#include <assert.h>

static uint32_t	g_buf[8];

void			ft_sha224_init(void)
{
	g_buf[A] = 0xC1059ED8;
	g_buf[B] = 0x367CD507;
	g_buf[C] = 0x3070DD17;
	g_buf[D] = 0xF70E5939;
	g_buf[E] = 0xFFC00B31;
	g_buf[F] = 0x68581511;
	g_buf[G] = 0x64F98FA7;
	g_buf[H] = 0xBEFA4FA4;
}

char			*ft_get_sha224_hash(void)
{
	int			i;
	uint32_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint32_t) * 7)))
		return (NULL);
	i = 0;
	while (i < 7)
	{
		hash[i] = swap_4_bytes(g_buf[i]);
		++i;
	}
	return ((char*)hash);
}

void			ft_sha224(char *data, size_t cur_size, size_t overall)
{
	size_t		i;
	uint32_t	c[8];

	if (cur_size != BATCH_SIZE)
	{
		if (!(cur_size = allign_sha256_data(&data, cur_size, overall)))
			return ;
	}
	// temporary
	assert(cur_size % 64 == 0);
	i = 0;
	while (i < cur_size)
	{
		ft_memcpy(&c, &g_buf, sizeof(uint32_t) * 8);
		ft_sha256_round((uint32_t*)&data[i], (uint32_t*)&c);
		g_buf[A] += c[A];
		g_buf[B] += c[B];
		g_buf[C] += c[C];
		g_buf[D] += c[D];
		g_buf[E] += c[E];
		g_buf[F] += c[F];
		g_buf[G] += c[G];
		g_buf[H] += c[H];
		i += 64;
	}
	if (cur_size != BATCH_SIZE)
		free(data);
}
