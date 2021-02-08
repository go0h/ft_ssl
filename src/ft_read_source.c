/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:12:08 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/08 22:10:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static void	swap(char **p1, char **p2)
{
	char *temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

long		ft_read_file(int fd, char **data)
{
	long	n;
	long	res;
	char	buf[BUFF_SIZE];
	char	*temp;

	res = 0;
	if (!(*data = ft_memalloc(1)))
		return (-1);
	while ((n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(temp = ft_memalloc(res + n)))
		{
			ft_bzero(*data, res);
			ft_memdel((void**)data);
			return (-1);
		}
		ft_memcpy(temp, *data, res);
		ft_memcpy(&temp[res], &buf, n);
		swap(data, &temp);
		free(temp);
		res += n;
	}
	return (res);
}
