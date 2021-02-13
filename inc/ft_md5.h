/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:10:49 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/13 22:05:05 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include "ft_ssl.h"

typedef struct		s_md5_round
{
	int k;
	int s;
}					t_md5_round;

typedef uint32_t	(*t_round_f)(uint32_t x, uint32_t y, uint32_t z);

uint32_t			fun_f(uint32_t x, uint32_t y, uint32_t z);

uint32_t			fun_g(uint32_t x, uint32_t y, uint32_t z);

uint32_t			fun_h(uint32_t x, uint32_t y, uint32_t z);

uint32_t			fun_i(uint32_t x, uint32_t y, uint32_t z);

#endif
