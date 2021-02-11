/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:23:01 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:41:44 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha.h"

static uint64_t	g_ti[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

/*
**	Σ0 := (a rotr 28) xor (a rotr 34) xor (a rotr 39)
**	Ma := (a and b) xor (a and c) xor (b and c)
**	t2 := Σ0 + Ma
**	Σ1 := (e rotr 14) xor (e rotr 18) xor (e rotr 41)
**	Ch := (e and f) xor ((not e) and g)
**	t1 := h + Σ1 + Ch + k[i] + w[i]
*/

static void		ft_sha512_main_cycle(uint64_t *w, uint64_t *c)
{
	int			i;
	uint64_t	t1;
	uint64_t	t2;

	i = 0;
	while (i < 80)
	{
		t2 = (rot64_r(c[A], 28) ^ rot64_r(c[A], 34) ^ rot64_r(c[A], 39)) +
			((c[A] & c[B]) ^ (c[A] & c[C]) ^ (c[B] & c[C]));
		t1 = (rot64_r(c[E], 14) ^ rot64_r(c[E], 18) ^ rot64_r(c[E], 41)) +
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
** s0 := (w[i-15] rotr 1) xor (w[i-15] rotr 8) xor (w[i-15] shr 7)
** s1 := (w[i-2] rotr 19) xor (w[i-2] rotr 61) xor (w[i-2] shr 10)
** w[i] := w[i-16] + s0 + w[i-7] + s1
*/

void			ft_sha512_round(uint64_t *x, uint64_t *c)
{
	int			i;
	uint64_t	s0;
	uint64_t	s1;
	uint64_t	w[80];

	i = 0;
	while (i < 16)
	{
		w[i] = swap_8_bytes(x[i]);
		++i;
	}
	ft_bzero((uint64_t*)&w[16], sizeof(uint64_t) * 64);
	i = 16;
	while (i < 80)
	{
		s0 = rot64_r(w[i - 15], 1) ^ rot64_r(w[i - 15], 8) ^ (w[i - 15] >> 7);
		s1 = rot64_r(w[i - 2], 19) ^ rot64_r(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
	ft_sha512_main_cycle((uint64_t*)&w, c);
}

size_t			allign_sha512_data(char **data, size_t cur_size, size_t overall)
{
	char		*new_data;
	size_t		zeros;
	uint64_t	msg_length;

	zeros = (overall + 1) % 128;
	zeros = zeros > 120 ? (128 - zeros) + 120 : 120 - zeros;
	if (!(new_data = (char*)ft_memalloc(cur_size + 1 + zeros + 8)))
		return (0);
	ft_memcpy(new_data, *data, cur_size);
	new_data[cur_size] = 0x80;
	msg_length = swap_8_bytes(overall * __CHAR_BIT__);
	ft_memcpy(&new_data[cur_size + 1 + zeros], &msg_length, 8);
	*data = new_data;
	return (cur_size + 1 + zeros + 8);
}
