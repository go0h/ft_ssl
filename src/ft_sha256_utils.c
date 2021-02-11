/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:36:37 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:27:41 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static uint32_t	g_ti[] = {
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

/*
**	Σ0 := (a rotr 2) xor (a rotr 13) xor (a rotr 22)
**	Ma := (a and b) xor (a and c) xor (b and c)
**	t2 := Σ0 + Ma
**	Σ1 := (e rotr 6) xor (e rotr 11) xor (e rotr 25)
**	Ch := (e and f) xor ((not e) and g)
**	t1 := h + Σ1 + Ch + k[i] + w[i]
*/

static void		ft_sha256_main_cycle(uint32_t *w, uint32_t *c)
{
	int			i;
	uint32_t	t1;
	uint32_t	t2;

	i = 0;
	while (i < 64)
	{
		t2 = (rot32_r(c[A], 2) ^ rot32_r(c[A], 13) ^ rot32_r(c[A], 22)) +
			((c[A] & c[B]) ^ (c[A] & c[C]) ^ (c[B] & c[C]));
		t1 = (rot32_r(c[E], 6) ^ rot32_r(c[E], 11) ^ rot32_r(c[E], 25)) +
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

void			ft_sha256_round(uint32_t *x, uint32_t *c)
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	w[64];

	i = 0;
	while (i < 16)
	{
		w[i] = swap_4_bytes(x[i]);
		++i;
	}
	ft_bzero((uint32_t*)&w[16], sizeof(uint32_t) * 48);
	i = 16;
	while (i < 64)
	{
		s0 = rot32_r(w[i - 15], 7) ^ rot32_r(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rot32_r(w[i - 2], 17) ^ rot32_r(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
	ft_sha256_main_cycle((uint32_t*)&w, c);
}

size_t			allign_sha256_data(char **data, size_t cur_size, size_t overall)
{
	char		*new_data;
	size_t		zeros;
	uint64_t	msg_length;

	zeros = (overall + 1) % 64;
	zeros = zeros > 56 ? (64 - zeros) + 56 : 56 - zeros;
	if (!(new_data = (char*)ft_memalloc(cur_size + 1 + zeros + 8)))
		return (0);
	ft_memcpy(new_data, *data, cur_size);
	new_data[cur_size] = 0x80;
	msg_length = swap_8_bytes(overall * __CHAR_BIT__);
	ft_memcpy(&new_data[cur_size + 1 + zeros], &msg_length, 8);
	*data = new_data;
	return (cur_size + 1 + zeros + 8);
}
