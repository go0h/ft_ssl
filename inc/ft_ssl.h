/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:17:00 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/14 14:34:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# define BATCH_SIZE	1048576

# define ECHO		0x20000000000UL
# define QUIET		0x40000000000UL
# define REVERSE	0x80000000000UL
# define STRING		0x100000000000UL

typedef void	(*t_init_func)(void);
typedef void	(*t_calc_func)(char *data, size_t cur_size, size_t overall);
typedef char	*(*t_get_func)(void);

typedef enum	e_error
{
	NONE, USAGE, INVALID_OPTION, SYS, MALLOC
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
	size_t		files;
}				t_ssl;

enum { A, B, C, D, E, F, G, H };

void			process_string(t_ssl *ssl, char *data);
void			process_stdin(t_ssl *ssl);
void			process_file(t_ssl *ssl, char *filename);
t_hash_func		*get_hash_func(char *param);

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
** SHA512/256 - Hash functions
*/

void			ft_sha512_256_i(void);
void			ft_sha512_256(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha512_256_h(void);

/*
** SHA512/224 - Hash functions
*/

void			ft_sha512_224_i(void);
void			ft_sha512_224(char *data, size_t cur_size, size_t overall);
char			*ft_get_sha512_224_h(void);

/*
** UTILITY FUNCTIONS
*/
void			ft_print_md_commands(void);

size_t			ft_options(int ac, char **av);

t_ssl			ft_parse_params(int ac, char **av);

void			ft_print_hash_from_fd(t_ssl ssl, char *source, char *hash);

void			ft_print_hash_from_str(t_ssl ssl, char *source, char *hash);

void			ft_error_handle(const char *msg, t_error err);

uint32_t		rot32_l(uint32_t num, int shift);

uint32_t		rot32_r(uint32_t num, int shift);

uint64_t		rot64_l(uint64_t num, int shift);

uint64_t		rot64_r(uint64_t num, int shift);

uint32_t		swap_4_bytes(uint32_t n);

uint64_t		swap_8_bytes(uint64_t n);

#endif
