/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:15:06 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:04:47 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

uint32_t	fun_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | ((~x) & z));
}

uint32_t	fun_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | ((~z) & y));
}

uint32_t	fun_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	fun_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ ((~z) | x));
}
