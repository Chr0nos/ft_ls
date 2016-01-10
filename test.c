/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 02:20:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 03:19:28 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flush_int(int nb, char *buffer)
{
	char	*x;
	int		xl;

	x = ft_itoa(nb);
	xl = (int)ft_strlen(x);
	if (xl > 2)
		xl = 2;
	ft_memcpy(buffer, x, (unsigned int)xl);
	ft_strdel(&x);
	return (xl);
}

static void	ft_wsize(unsigned long long size, char *buffer)
{
	int			k;
	int			p;
	int			rest;

	rest = 0;
	k = 0;
	while ((size > 1024) && (k < 6))
	{
		rest = size % 1024;
		size /= 1024;
		k++;
	}
	if ((!(p = 0)) && (size == 0))
		buffer[p++] = '0';
	p += flush_int((int)size, &buffer[p]);
	if (rest)
	{
		buffer[p++] = '.';
		p += flush_int((int)rest, &buffer[p]);
	}
	buffer[p++] = "bKMGTE"[k];
	buffer[p] = '\0';
}

int	main(void)
{
	char	buffer[20];

	ft_wsize(42 * 1024, (char*)buffer);
	ft_putendl(buffer);
	return (0);
}
