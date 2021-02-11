/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:17:00 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/11 22:38:46 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"
# include <stdio.h>

# define BATCH_SIZE 1048576

typedef void	(*t_init_func)(void);
typedef void	(*t_calc_func)(char *data, size_t cur_size, size_t overall);
typedef char	*(*t_get_func)(void);

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
	t_init_func	init;
	t_calc_func	func;
	t_get_func	get;
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

/*
** MD5 - Hash functions
*/

void			ft_md5_init(void);
void			ft_md5(char *data, size_t cur_size, size_t overall);
char			*ft_get_md5_hash(void);

/*
** SHA256 - Hash functions
*/

void			ft_sha256_init(void);
void			ft_sha256(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha256_hash(void);

/*
** SHA224 - Hash functions
*/

void			ft_sha224_init(void);
void			ft_sha224(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha224_hash(void);

/*
** SHA512 - Hash functions
*/

void			ft_sha512_init(void);
void			ft_sha512(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha512_hash(void);

/*
** SHA384 - Hash functions
*/

void			ft_sha384_init(void);
void			ft_sha384(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha384_hash(void);

/*
** UTILITY FUNCTIONS
*/

void			ft_error_handle(const char *msg, t_error err);

void			free_ssl(t_ssl **ssl);

void			print_ssl(t_ssl *ssl);

void			free_data(void *data);

uint32_t		rot32_l(uint32_t num, int shift);

uint32_t		rot32_r(uint32_t num, int shift);

uint64_t		rot64_l(uint64_t num, int shift);

uint64_t		rot64_r(uint64_t num, int shift);

uint32_t		swap_4_bytes(uint32_t n);

uint64_t		swap_8_bytes(uint64_t n);

#endif
