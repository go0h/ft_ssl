/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:22:02 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:05:25 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha2.h"

static uint32_t	g_buf[8];

void			ft_sha256_init(void)
{
	g_buf[A] = 0x6A09E667;
	g_buf[B] = 0xBB67AE85;
	g_buf[C] = 0x3C6EF372;
	g_buf[D] = 0xA54FF53A;
	g_buf[E] = 0x510E527F;
	g_buf[F] = 0x9B05688C;
	g_buf[G] = 0x1F83D9AB;
	g_buf[H] = 0x5BE0CD19;
}

char			*ft_get_sha256_hash(void)
{
	int			i;
	uint32_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint32_t) * 8)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		hash[i] = swap_4_bytes(g_buf[i]);
		++i;
	}
	return ((char*)hash);
}

void			ft_sha256(char *data, size_t cur_size, size_t overall)
{
	size_t		i;
	uint32_t	c[8];

	if (cur_size != BATCH_SIZE)
	{
		if (!(cur_size = allign_sha256_data(&data, cur_size, overall)))
			return ;
	}
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
