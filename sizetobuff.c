/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizetobuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 20:26:02 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 21:57:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

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

	if (nb == 0)
	{
		ft_strcpy(buffer, "0");
		return (1);
	}
	n = m - 1;
	buffer[n--] = '\0';
	while (nb)
	{
		buffer[n--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (m - 1);
}
