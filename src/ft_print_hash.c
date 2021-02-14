/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:12:08 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/14 10:25:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_hash(char *hash, int size, char *end)
{
	int			i;
	static char	hex[16] = "0123456789abcdef";

	i = 0;
	while (i < size)
	{
		ft_printf("%c%c",
			hex[(unsigned char)hash[i] / 16],
			hex[(unsigned char)hash[i] % 16]);
		i++;
	}
	ft_printf("%s", end);
}

void		ft_print_hash_from_fd(t_ssl ssl, char *source, char *hash)
{
	if (!hash)
		ft_error_handle(__FUNCTION__, MALLOC);
	if (ssl.options & QUIET)
		print_hash(hash, ssl.hash_func.hash_size, "\n");
	else if (ssl.options & REVERSE)
	{
		print_hash(hash, ssl.hash_func.hash_size, "");
		ft_printf(" *%s\n", source);
	}
	else
	{
		if (ft_strcmp(source, "stdin"))
			ft_printf("%s", ssl.hash_func.name);
		ft_printf("(%s)= ", source);
		print_hash(hash, ssl.hash_func.hash_size, "\n");
	}
	free(hash);
}

void		ft_print_hash_from_str(t_ssl ssl, char *source, char *hash)
{
	if (!hash)
		ft_error_handle(__FUNCTION__, MALLOC);
	if (ssl.options & QUIET)
		print_hash(hash, ssl.hash_func.hash_size, "\n");
	else if (ssl.options & REVERSE)
	{
		print_hash(hash, ssl.hash_func.hash_size, "");
		ft_printf(" \"%s\"\n", source);
	}
	else
	{
		ft_printf("%s(\"%s\")= ", ssl.hash_func.name, source);
		print_hash(hash, ssl.hash_func.hash_size, "\n");
	}
	free(hash);
}
