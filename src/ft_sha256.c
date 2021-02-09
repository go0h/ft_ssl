/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:22:02 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/08 23:54:14 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <assert.h>

static u_int32_t	g_buf[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static u_int32_t	g_ti[] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
 };

void	ft_sha256_init(void)
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

char		*ft_get_sha256_hash(void)
{
	int			i;
	uint32_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint32_t) * 8)))
		return (NULL);
	i = 0;
	while(i < 8)
	{
		hash[i] = swap_4_bytes(g_buf[i]);
		++i;
	}

	return ((char*)hash);
}

void		print_sha256_hash(u_int32_t *h)
{
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n",
	h[A], h[B], h[C], h[D], h[E], h[F], h[G], h[H]);
}

/*
**	Σ0 := (a rotr 2) xor (a rotr 13) xor (a rotr 22)
**	Ma := (a and b) xor (a and c) xor (b and c)
**	t2 := Σ0 + Ma
**	Σ1 := (e rotr 6) xor (e rotr 11) xor (e rotr 25)
**	Ch := (e and f) xor ((not e) and g)
**	t1 := h + Σ1 + Ch + k[i] + w[i]
*/

void		ft_sha256_main_cycle(u_int32_t *w, uint32_t *c)
{
	int			i;
	u_int32_t	t1;
	u_int32_t	t2;

	i = 0;
	while (i < 64)
	{
		t2 = (rot_r(c[A], 2) ^ rot_r(c[A], 13) ^ rot_r(c[A], 22)) +
			((c[A] & c[B]) ^ (c[A] & c[C]) ^ (c[B] & c[C]));
		t1 = (rot_r(c[E], 6) ^ rot_r(c[E], 11) ^ rot_r(c[E], 25)) +
			((c[E] & c[F]) ^ (~c[E] & c[G]));
		t1 = c[H] + t1 + g_ti[i] + w[i];
		c[H] = c[G];
		c[G] = c[F];
		c[F] = c[E];
		c[E] = c[D] + t1;
		c[D] = c[C];
		c[C] = c[B];
		c[B] = c[A];
		c[A] = t1 + t2;
		++i;
	}
}

/*
** s0 := (w[i-15] rotr 7) xor (w[i-15] rotr 18) xor (w[i-15] shr 3)
** s1 := (w[i-2] rotr 17) xor (w[i-2] rotr 19) xor (w[i-2] shr 10)
** w[i] := w[i-16] + s0 + w[i-7] + s1
*/

void		ft_sha256_round(u_int32_t *x, uint32_t *c)
{
	int				i;
	u_int32_t		s0;
	u_int32_t		s1;
	u_int32_t		w[64];

	i = 0;
	while (i < 16)
	{
		w[i] = swap_4_bytes(x[i]);
		++i;
	}
	ft_bzero((u_int32_t*)&w[16], sizeof(u_int32_t) * 48);
	i = 16;
	while (i < 64)
	{
		s0 = rot_r(w[i - 15], 7) ^ rot_r(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rot_r(w[i - 2], 17) ^ rot_r(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
	ft_sha256_main_cycle((u_int32_t*)&w, c);
}

static size_t		allign_data(char **data, size_t size)
{
	char	*new_data;
	size_t	zeros;
	size_t	msg_length;

	zeros = (size + 1) % 64;
	zeros = zeros > 56 ? (64 - zeros) + 56 : 56 - zeros;
	if (!(new_data = (char*)ft_memalloc(size + 1 + zeros + 8)))
		return (0);
	ft_memcpy(new_data, *data, size);
	new_data[size] = 1 << 7;
	msg_length = swap_8_bytes(size * __CHAR_BIT__);
	ft_memcpy(&new_data[size + 1 + zeros], &msg_length, 8);
	free(*data);
	*data = new_data;
	return (size + 1 + zeros + 8);
}

void ft_sha256(char *data, size_t cur_size, size_t overall)
{
	size_t			i;
	static uint32_t	c[] = {0, 0, 0, 0, 0, 0, 0, 0};

	cur_size *= 0;
	if (!(overall = allign_data(&data, overall)))
		return ;
	// temporary
	assert(overall % 64 == 0);
	i = 0;
	while (i < overall)
	{
		ft_memcpy(&c, &g_buf, sizeof(u_int32_t) * 8);
		ft_sha256_round((u_int32_t*)&data[i], (u_int32_t*)&c);
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
	free(data);
}
