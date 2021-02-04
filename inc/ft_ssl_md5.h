/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:17:00 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/04 20:52:44 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"

typedef void	(*t_hash)(char *data, size_t opts);

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
	t_hash		func;
}				t_hash_func;

typedef struct	s_ssl
{
	t_hash_func	*hash;
	size_t		options;
}				t_ssl;

void			usage(t_error err, char *opt);

size_t			options(int ac, char **av);

t_hash_func		get_hash_func(int ac, char **av);

void			ft_md5(char *data, size_t opts);

void			ft_sha256(char *data, size_t opts);

#endif
