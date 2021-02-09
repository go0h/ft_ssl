/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:17:00 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/08 23:53:48 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"
# include <stdio.h>

# define MEGABYTE 1048576

typedef void	(*init_func)(void);
typedef void	(*calc_func)(char *data, size_t cur_size, size_t overall);
typedef char	*(*get_func)(void);

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
	init_func	init;
	calc_func	func;
	get_func	get;
	int			hash_size;
}				t_hash_func;

typedef struct	s_ssl
{
	t_hash_func	hash_func;
	size_t		options;
	t_darr		*sources;
}				t_ssl;

enum { A, B, C, D, E, F, G, H };

size_t			ft_options(int ac, char **av);

t_ssl			*ft_parse_params(int ac, char **av);

void			ft_md5_init(void);
void			ft_md5(char *data, size_t cur_size, size_t overall);
char			*ft_get_md5_hash(void);

void			ft_sha256_init(void);
void			ft_sha256(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha256_hash(void);

long			ft_read_file(int fd, char **data);


/*
** UTILITY FUNCTIONS
*/

void			ft_error_handle(const char *msg, t_error err);

void			free_ssl(t_ssl **ssl);

void			print_ssl(t_ssl *ssl);

void			free_data(void *data);

u_int64_t		swap_8_bytes(u_int64_t n);

u_int32_t		swap_4_bytes(u_int32_t n);

uint32_t		rot_l(uint32_t num, int shift);

uint32_t		rot_r(uint32_t num, int shift);

#endif
