/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:10:49 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/07 12:12:23 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

#include "ft_ssl_md5.h"

typedef struct	s_md5_round
{
	int k;
	int s;
}				t_md5_round;

typedef u_int32_t	(*round_f)(u_int32_t x, u_int32_t y, u_int32_t z);

u_int32_t	fun_f(u_int32_t x, u_int32_t y, u_int32_t z);

u_int32_t	fun_g(u_int32_t x, u_int32_t y, u_int32_t z);

u_int32_t	fun_h(u_int32_t x, u_int32_t y, u_int32_t z);

u_int32_t	fun_i(u_int32_t x, u_int32_t y, u_int32_t z);

#endif
