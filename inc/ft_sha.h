/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:39:06 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/09 22:13:38 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA_H
# define FT_SHA_H

# include "ft_ssl_md5.h"

size_t		allign_sha256_data(char **data, size_t cur_size, size_t overall);

#endif
