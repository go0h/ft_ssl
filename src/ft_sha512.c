/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:13:27 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:29:11 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha.h"
#include <assert.h>

static uint64_t	g_buf[8];

void			ft_sha512_init(void)
{
	g_buf[A] = 0x6a09e667f3bcc908;
	g_buf[B] = 0xbb67ae8584caa73b;
	g_buf[C] = 0x3c6ef372fe94f82b;
	g_buf[D] = 0xa54ff53a5f1d36f1;
	g_buf[E] = 0x510e527fade682d1;
	g_buf[F] = 0x9b05688c2b3e6c1f;
	g_buf[G] = 0x1f83d9abfb41bd6b;
	g_buf[H] = 0x5be0cd19137e2179;
}

char			*ft_get_sha512_hash(void)
{
	int			i;
	uint64_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint64_t) * 8)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		hash[i] = swap_8_bytes(g_buf[i]);
		++i;
	}
	return ((char*)hash);
}

void			ft_sha512(char *data, size_t cur_size, size_t overall)
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
