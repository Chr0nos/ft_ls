/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 21:02:44 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 14:39:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

int		sizesort(t_list *a, t_list *b)
{
	const off_t	sa = ((t_file *)(a->content))->stats.st_size;
	const off_t	sb = ((t_file *)(b->content))->stats.st_size;

	if (sa == sb)
		return (sorter(a, b));
	return ((int)(sa - sb));
}

int		rsizesort(t_list *a, t_list *b)
{
	return (sizesort(a, b) * -1);
}
