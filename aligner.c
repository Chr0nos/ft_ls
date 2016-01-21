/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aligner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:48:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 16:04:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	aligner(char *buffer, unsigned int len)
{
	char				*tmp;
	size_t				slen;
	size_t				diff;

	slen = ft_strlen(buffer);
	if (slen >= len)
		return ;
	diff = len - slen;
	ft_memmove(buffer + diff, buffer, slen);
	while (diff--)
		buffer[diff] = ' ';
}
