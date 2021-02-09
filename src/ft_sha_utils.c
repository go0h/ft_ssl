/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 21:36:37 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/09 22:03:04 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

size_t		allign_sha256_data(char **data, size_t cur_size, size_t overall)
{
	char		*new_data;
	size_t		zeros;
	u_int64_t	msg_length;

	zeros = (overall + 1) % 64;
	zeros = zeros > 56 ? (64 - zeros) + 56 : 56 - zeros;
	if (!(new_data = (char*)ft_memalloc(cur_size + 1 + zeros + 8)))
		return (0);
	ft_memcpy(new_data, *data, cur_size);
	new_data[cur_size] = 0x80;
	msg_length = swap_8_bytes(overall * __CHAR_BIT__);
	ft_memcpy(&new_data[cur_size + 1 + zeros], &msg_length, 8);
	*data = new_data;
	return (cur_size + 1 + zeros + 8);
}
