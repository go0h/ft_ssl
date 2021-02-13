/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_224.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:55 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:05:33 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha2.h"

static uint64_t	g_buf[8];

void			ft_sha512_224_i(void)
{
	g_buf[A] = 0x8C3D37C819544DA2;
	g_buf[B] = 0x73E1996689DCD4D6;
	g_buf[C] = 0x1DFAB7AE32FF9C82;
	g_buf[D] = 0x679DD514582F9FCF;
	g_buf[E] = 0x0F6D2B697BD44DA8;
	g_buf[F] = 0x77E36F7304C48942;
	g_buf[G] = 0x3F9D85A86A1D36C8;
	g_buf[H] = 0x1112E6AD91D692A1;
}

char			*ft_get_sha512_224_h(void)
{
	int			i;
	uint64_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint64_t) * 4)))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		hash[i] = swap_8_bytes(g_buf[i]);
		++i;
	}
	return ((char*)hash);
}

void			ft_sha512_224(char *data, size_t cur_size, size_t overall)
{
	size_t		i;
	uint64_t	c[8];

	if (cur_size != BATCH_SIZE)
	{
		if (!(cur_size = allign_sha512_data(&data, cur_size, overall)))
			return ;
	}
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
