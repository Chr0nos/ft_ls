/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizetobuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 20:26:02 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/20 21:14:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int		sizetobuff_len(off_t nb)
{
	unsigned int		len;

	len = 1;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

unsigned int			sizetobuff(off_t nb, char *buffer)
{
	const unsigned int	m = sizetobuff_len(nb);
	unsigned int		n;

	n = m - 1;
	buffer[n--] = '\0';
	if (!nb)
		buffer[n] = '0';
	while (nb)
	{
		buffer[n--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (m);
}
