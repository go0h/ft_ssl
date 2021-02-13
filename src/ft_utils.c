/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:46:28 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:06:24 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rot32_l(uint32_t num, int shift)
{
	return (num << shift | (num >> (32 - shift)));
}

uint32_t	rot32_r(uint32_t num, int shift)
{
	return (num >> shift | (num << (32 - shift)));
}

uint64_t	rot64_r(uint64_t num, int shift)
{
	return (num >> shift | (num << (64 - shift)));
}

u_int64_t	swap_8_bytes(u_int64_t n)
{
	return ((n & 0xffULL) << 56 |
			(n & 0xff00ULL) << 40 |
			(n & 0xff0000ULL) << 24 |
			(n & 0xff000000ULL) << 8 |
			(n & 0xff00000000ULL) >> 8 |
			(n & 0xff0000000000ULL) >> 24 |
			(n & 0xff000000000000ULL) >> 40 |
			(n & 0xff00000000000000ULL) >> 56);
}

u_int32_t	swap_4_bytes(u_int32_t n)
{
	return ((n & 0xffULL) << 24 |
			(n & 0xff00ULL) << 8 |
			(n & 0xff0000ULL) >> 8 |
			(n & 0xff000000ULL) >> 24);
}
