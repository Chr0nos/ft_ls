/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 16:22:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 16:32:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	usort(t_list *a, t_list *b)
{
	long	ta;
	long	tb;

	ta = ((t_file*)(a->content))->stats.st_atime;
	tb = ((t_file*)(b->content))->stats.st_atime;
	if (ta == tb)
	{
		ta = ((t_file*)(a->content))->stats.st_atimespec.tv_nsec;
		tb = ((t_file*)(b->content))->stats.st_atimespec.tv_nsec;
		if (ta == tb)
			return (sorter(b, a));
	}
	return ((int)(ta - tb));
}

int	usortr(t_list *a, t_list *b)
{
	return (usort(a, b) * -1);
}
