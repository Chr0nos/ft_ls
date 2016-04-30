/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpresent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 21:05:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 22:54:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		strpresent(const char *str, const char c)
{
	unsigned int	p;

	p = 0;
	while (str[p] != '\0')
		if (str[p++] == c)
			return ((int)p - 1);
	return (-1);
}
