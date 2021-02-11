/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:03:47 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 21:39:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"
#include <assert.h>

static uint32_t		g_buf[4];

static uint32_t		g_ti[] = {
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
**	{k, s}
*/

static t_md5_round	g_r[] = {
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

void				ft_md5_init(void)
{
	g_buf[A] = 0x67452301;
	g_buf[B] = 0xEFCDAB89;
	g_buf[C] = 0x98BADCFE;
	g_buf[D] = 0x10325476;
}

char				*ft_get_md5_hash(void)
{
	uint32_t	*hash;

	if (!(hash = ft_memalloc(sizeof(uint32_t) * 4)))
		return (NULL);
	ft_memcpy(hash, g_buf, sizeof(uint32_t) * 4);
	return ((char*)hash);
}

/*
** [abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
*/

static void			ft_md5_round(uint32_t *x, uint32_t *c)
{
	int					i;
	uint32_t			f;
	static t_round_f	func[] = {&fun_f, &fun_g, &fun_h, &fun_i};

	i = 0;
	while (i < 64)
	{
		f = c[A] + func[i / 16](c[B], c[C], c[D]) + x[g_r[i].k] + g_ti[i];
		c[A] = c[D];
		c[D] = c[C];
		c[C] = c[B];
		c[B] += rot32_l(f, g_r[i].s);
		i++;
	}
}

static size_t		allign_data(char **data, size_t cur_size, size_t overall)
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
	msg_length = overall * __CHAR_BIT__;
	ft_memcpy(&new_data[cur_size + 1 + zeros], &msg_length, 8);
	*data = new_data;
	return (cur_size + 1 + zeros + 8);
}

void				ft_md5(char *data, size_t cur_size, size_t overall)
{
	size_t		i;
	uint32_t	c[4];

	if (cur_size != BATCH_SIZE)
	{
		if (!(cur_size = allign_data(&data, cur_size, overall)))
			return ;
	}
	// temporary
	assert(cur_size % 64 == 0);
	i = 0;
	while (i < cur_size)
	{
		ft_memcpy(&c, &g_buf, sizeof(uint32_t) * 4);
		ft_md5_round((uint32_t*)&data[i], (uint32_t*)&c);
		g_buf[A] += c[A];
		g_buf[B] += c[B];
		g_buf[C] += c[C];
		g_buf[D] += c[D];
		i += 64;
	}
	if (cur_size != BATCH_SIZE)
		free(data);
}
