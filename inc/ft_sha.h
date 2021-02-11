/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:39:06 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:28:33 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA_H
# define FT_SHA_H

# include "ft_ssl_md5.h"

void		ft_sha256_round(uint32_t *x, uint32_t *c);

size_t		allign_sha256_data(char **data, size_t cur_size, size_t overall);

void		ft_sha512_round(uint64_t *x, uint64_t *c);

size_t		allign_sha512_data(char **data, size_t cur_size, size_t overall);

#endif
