/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:03:47 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/07 15:11:59 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"
#include <assert.h>

static u_int32_t	g_buf[] = { 0, 0, 0, 0 };

static u_int32_t	g_ti[] = {
	0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE,
	0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
	0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
	0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
	0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA,
	0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
	0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
	0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
	0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
	0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
	0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05,
	0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
	0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039,
	0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
	0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
	0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391 };

/*
**	[abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
**	[ABCD  0 7  1][DABC  1 12  2][CDAB  2 17  3][BCDA  3 22  4]
**	[ABCD  4 7  5][DABC  5 12  6][CDAB  6 17  7][BCDA  7 22  8]
**	[ABCD  8 7  9][DABC  9 12 10][CDAB 10 17 11][BCDA 11 22 12]
**	[ABCD 12 7 13][DABC 13 12 14][CDAB 14 17 15][BCDA 15 22 16]
**
**	[ABCD  1 5 17][DABC  6 9 18][CDAB 11 14 19][BCDA  0 20 20]
**	[ABCD  5 5 21][DABC 10 9 22][CDAB 15 14 23][BCDA  4 20 24]
**	[ABCD  9 5 25][DABC 14 9 26][CDAB  3 14 27][BCDA  8 20 28]
**	[ABCD 13 5 29][DABC  2 9 30][CDAB  7 14 31][BCDA 12 20 32]
**
**	[ABCD  5 4 33][DABC  8 11 34][CDAB 11 16 35][BCDA 14 23 36]
**	[ABCD  1 4 37][DABC  4 11 38][CDAB  7 16 39][BCDA 10 23 40]
**	[ABCD 13 4 41][DABC  0 11 42][CDAB  3 16 43][BCDA  6 23 44]
**	[ABCD  9 4 45][DABC 12 11 46][CDAB 15 16 47][BCDA  2 23 48]
**
**	[ABCD  0 6 49][DABC  7 10 50][CDAB 14 15 51][BCDA  5 21 52]
**	[ABCD 12 6 53][DABC  3 10 54][CDAB 10 15 55][BCDA  1 21 56]
**	[ABCD  8 6 57][DABC 15 10 58][CDAB  6 15 59][BCDA 13 21 60]
**	[ABCD  4 6 61][DABC 11 10 62][CDAB  2 15 63][BCDA  9 21 64]
*/

t_md5_round	g_r[] = {
	{0, 7}, {1, 12}, {2, 17}, {3, 22},
	{4, 7}, {5, 12}, {6, 17}, {7, 22},
	{8, 7}, {9, 12}, {10, 17}, {11, 22},
	{12, 7}, {13, 12}, {14, 17}, {15, 22},
	{1, 5}, {6, 9}, {11, 14}, {0, 20},
	{5, 5}, {10, 9}, {15, 14}, {4, 20},
	{9, 5}, {14, 9}, {3, 14}, {8, 20},
	{13, 5}, {2, 9}, {7, 14}, {12, 20},
	{5, 4}, {8, 11}, {11, 16}, {14, 23},
	{1, 4}, {4, 11}, {7, 16}, {10, 23},
	{13, 4}, {0, 11}, {3, 16}, {6, 23},
	{9, 4}, {12, 11}, {15, 16}, {2, 23},
	{0, 6}, {7, 10}, {14, 15}, {5, 21},
	{12, 6}, {3, 10}, {10, 15}, {1, 21},
	{8, 6}, {15, 10}, {6, 15}, {13, 21},
	{4, 6}, {11, 10}, {2, 15}, {9, 21}
};

static void		init_buf(uint32_t *h)
{
	h[A] = 0x67452301;
	h[B] = 0xEFCDAB89;
	h[C] = 0x98BADCFE;
	h[D] = 0x10325476;
}

void		print_md5_hash(uint32_t *h)
{
	ft_printf("%08x%08x%08x%08x\n",
	swap_4_bytes(h[A]),
	swap_4_bytes(h[B]),
	swap_4_bytes(h[C]),
	swap_4_bytes(h[D]));
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
	msg_length = size * __CHAR_BIT__;
	ft_memcpy(&new_data[size + 1 + zeros], &msg_length, 8);
	free(*data);
	*data = new_data;
	return (size + 1 + zeros + 8);
}

/*
** [abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
*/

void		ft_md5_round(u_int32_t *x, uint32_t *c)
{
	int				i;
	u_int32_t		f;
	static round_f	func[] = {&fun_f, &fun_g, &fun_h, &fun_i};

	i = 0;
	while (i < 64)
	{
		f = c[A] + func[i / 16](c[B], c[C], c[D]) + x[g_r[i].k] + g_ti[i];
		c[A] = c[D];
		c[D] = c[C];
		c[C] = c[B];
		c[B] += rot_l(f, g_r[i].s);
		i++;
	}
}

void		ft_md5(char *data, size_t size)
{
	size_t			i;
	static uint32_t	c[4] = {0, 0, 0, 0};

	if (!(size = allign_data(&data, size)))
		return ;
	init_buf(g_buf);
	// temporary
	assert(size % 64 == 0);
	i = 0;
	while (i < size)
	{
		ft_memcpy(&c, &g_buf, sizeof(uint32_t) * 4);
		ft_md5_round((u_int32_t*)&data[i], (u_int32_t*)&c);
		g_buf[A] += c[A];
		g_buf[B] += c[B];
		g_buf[C] += c[C];
		g_buf[D] += c[D];
		i += 64;
	}
	print_md5_hash(g_buf);
}
