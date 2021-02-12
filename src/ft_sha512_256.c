/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:01:47 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/12 20:12:29 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha.h"
#include <assert.h>

static uint64_t	g_buf[8];

void			ft_sha512_256_init(void)
{
	g_buf[A] = 0x22312194FC2BF72C;
	g_buf[B] = 0x9F555FA3C84C64C2;
	g_buf[C] = 0x2393B86B6F53B151;
	g_buf[D] = 0x963877195940EABD;
	g_buf[E] = 0x96283EE2A88EFFE3;
	g_buf[F] = 0xBE5E1E2553863992;
	g_buf[G] = 0x2B0199FC2C85B8AA;
	g_buf[H] = 0x0EB72DDC81C52CA2;
}

char			*ft_get_sha512_256_hash(void)
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

void			ft_sha512_256(char *data, size_t cur_size, size_t overall)
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
