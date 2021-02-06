/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:15:06 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/06 21:15:27 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

u_int32_t	fun_f(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return ((x & y) | ((~x) & z));
}

u_int32_t	fun_g(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return ((x & z) | ((~z) & y));
}

u_int32_t	fun_h(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return (x ^ y ^ z);
}

u_int32_t	fun_i(u_int32_t x, u_int32_t y, u_int32_t z)
{
	return (y ^ ((~z) | x));
}
