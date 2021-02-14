/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:11:16 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/14 13:45:49 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_string(t_ssl *ssl, char *data)
{
	size_t	size;

	size = ft_strlen(data);
	ssl->hash_func.init();
	ssl->hash_func.func(data, size, size);
	ft_print_hash_from_str(*ssl, data, ssl->hash_func.get());
	ssl->options = ssl->options ^ STRING;
}

void	process_stdin(t_ssl *ssl)
{
	long	n;
	long	size;
	char	buf[BATCH_SIZE];
	char	*data;
	char	*temp;

	size = 0;
	data = NULL;
	ssl->hash_func.init();
	while ((n = read(STDIN_FILENO, &buf, BATCH_SIZE)) > 0)
	{
		temp = data;
		if (!(data = ft_realloc(temp, size, size + n + 1)))
		{
			free(temp);
			ft_error_handle(__FUNCTION__, MALLOC);
		}
		ft_memcpy(&data[size], (void*)&buf, n);
		size += n;
	}
	ssl->hash_func.func(data, size, size);
	ssl->options & ECHO ? ft_printf("%s", data) : 0;
	ft_print_hash_from_fd(*ssl, "stdin", ssl->hash_func.get());
	ft_memdel((void**)&data);
	ssl->options = ssl->options ^ ECHO;
}

void	process_file(t_ssl *ssl, char *filename)
{
	int		fd;
	long	n;
	long	size_in_bytes;
	char	buf[BATCH_SIZE];

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_error_handle(filename, SYS);
		return ;
	}
	size_in_bytes = 0;
	ssl->hash_func.init();
	while ((n = read(fd, (char*)&buf, BATCH_SIZE)) > 0)
	{
		size_in_bytes += n;
		ssl->hash_func.func((char*)&buf, n, size_in_bytes);
	}
	ft_print_hash_from_fd(*ssl, filename, ssl->hash_func.get());
	close(fd);
}
