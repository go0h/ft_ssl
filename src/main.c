/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:51 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/05 21:46:20 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int		main(int argc, char **argv)
{
	t_ssl	*ssl;

	ssl = ft_parse_params(argc, argv);
	print_ssl(ssl);
	return (EXIT_SUCCESS);
}
