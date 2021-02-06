/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:19:39 by astripeb          #+#    #+#             */
/*   Updated: 2021/02/06 15:45:18 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

uint32_t	shift_left(uint32_t num, int shift)
{
	return (num << shift | ((~0 << (32 - shift)) & num) >> (32 - shift));
}


int main(void)
{
	int n = 0x00FF00FF;
	int n1 = 0x01010101;

	printf("%08X << %d = %08X\n", n, 8, shift_left(n, 8));
	printf("%08X << %d = %08X\n", n1, 4, shift_left(n1, 4));
	printf("%08X << %d = %08X\n", n1, 32, shift_left(n1, 32));

	return (0);
}
