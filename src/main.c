/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:51 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/09 16:39:07 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

// static void	process_fd(t_ssl *ssl, int fd, char *source_name)
// {
// 	long	n;
// 	char	*data;
// 	char	*hash;
// 	long	size_in_bytes;
// 	char	buf[MEGABYTE];

// 	ssl->hash_func.init();
// 	size_in_bytes = 0;
// 	while ((n = read(fd, buf, MEGABYTE)) > 0)
// 	{
// 		size_in_bytes += n;
// 	}
// 	ssl->hash_func.func(data, size_in_bytes);
// 	hash = ssl->hash_func.get();
// 	n = 0;
// 	while (n < ssl->hash_func.hash_size)
// 		ft_printf("%hhx", hash[n++]);
// 	ft_printf("\n");
// 	free(hash);
// }


static void	process_fd(t_ssl *ssl, int fd, char *source_name)
{
	int		i;
	char	*data;
	char	*hash;
	long	size_in_bytes;

	size_in_bytes = 0;
	if ((size_in_bytes = ft_read_file(fd, &data)) == -1)
		ft_error_handle(source_name, MALLOC);
	// ft_printf("process %s - %lu\n", source_name, size_in_bytes);
	ssl->hash_func.init();
	ssl->hash_func.func(data, 0, size_in_bytes);
	hash = ssl->hash_func.get();
	i = 0;
	while (i < ssl->hash_func.hash_size)
		ft_printf("%hhx", hash[i++]);
	ft_printf("\n");
	free(hash);
}

static void	process_sources(t_ssl *ssl)
{
	int		fd;
	size_t	i;
	char	*source_name;

	if (ssl->sources->size != 0)
	{
		i = 0;
		while (i < ssl->sources->size)
		{
			source_name = *(char**)ft_da_get_pointer(ssl->sources, i);
			if ((fd = open(source_name, O_RDONLY)) < 0)
				ft_error_handle(source_name, SYS);
			else
				process_fd(ssl, fd, source_name);
			++i;
		}
	}
	else
		process_fd(ssl, STDIN_FILENO, "stdin");
}

int			main(int argc, char **argv)
{
	t_ssl	*ssl;

	ssl = ft_parse_params(argc, argv);
	// print_ssl(ssl);
	process_sources(ssl);
	free_ssl(&ssl);
	return (EXIT_SUCCESS);
}
