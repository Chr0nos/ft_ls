/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltsort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:32:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:07:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int	ltsort(t_list *a, t_list *b)
{
	long	ta;
	long	tb;

	ta = ((t_file*)(a->content))->stats.st_mtime;
	tb = ((t_file*)(b->content))->stats.st_mtime;
	if (ta == tb)
	{
		ta = ((t_file*)(a->content))->stats.st_mtimespec.tv_nsec;
		tb = ((t_file*)(b->content))->stats.st_mtimespec.tv_nsec;
		if (ta == tb)
			return (sorter(b, a));
	}
	return ((int)(ta - tb));
}

int	ltsortr(t_list *a, t_list *b)
{
	return (ltsort(a, b) * -1);
}
