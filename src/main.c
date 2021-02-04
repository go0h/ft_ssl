/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:51 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/04 20:54:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int			main(int argc, char **argv)
{
	t_hash_func hf;

	if (argc < 2)
		usage(USAGE, NULL);

	hf = get_hash_func(argc, argv);
	ft_printf("hash function = %s\n", hf.name);
	return (EXIT_SUCCESS);
}
