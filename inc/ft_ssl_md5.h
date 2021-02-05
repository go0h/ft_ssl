/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:17:00 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/05 21:45:04 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"
# include <stdio.h>

typedef void	(*t_func)(char *data, size_t opts);

typedef enum	e_error
{
	NONE,
	USAGE,
	INVALID_OPTION,
	SYS,
	MALLOC
}				t_error;

typedef struct	s_hash_func
{
	char		name[10];
	t_func		func;
}				t_hash_func;

typedef struct	s_ssl
{
	t_hash_func	hash_func;
	size_t		options;
	t_darr		*sources;
}				t_ssl;

size_t			ft_options(int ac, char **av);

t_ssl			*ft_parse_params(int ac, char **av);

void			ft_md5(char *data, size_t opts);

void			ft_sha256(char *data, size_t opts);

/*
** UTILITY FUNCTIONS
*/

void			ft_error_handle(const char *msg, t_error err);

void			free_ssl(t_ssl **ssl);

void			print_ssl(t_ssl *ssl);

void			free_data(void *data);

#endif
