/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:22:41 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/10 20:01:48 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(void)
{
	static uint32_t g[80] = {
		2, 3, 5, 7, 11, 13, 17, 19,
		23, 29, 31, 37, 41, 43, 47, 53,
		59, 61, 67, 71, 73, 79, 83, 89,
		97, 101, 103, 107, 109, 113, 127, 131,
		137, 139, 149, 151, 157, 163, 167, 173,
		179, 181, 191, 193, 197, 199, 211, 223,
		227, 229, 233, 239, 241, 251, 257, 263,
		269, 271, 277, 281, 283, 293, 307, 311,
		313, 317, 331, 337, 347, 349, 353, 359,
		367, 373, 379, 383, 389, 397, 401, 409
	};
	int i;
	uint32_t bits;

	i = 0;
	while (i < 80)
	{
		long double d = sqrtl(g[i]) - (int)sqrtl(g[i]);
		uint64_t pow = ~0;
		uint64_t res = (d * pow);

		printf("%016lX ", res);
		if (i && (i + 1) % 2 == 0)
			printf("\n");
		++i;
	}
	return (0);
}