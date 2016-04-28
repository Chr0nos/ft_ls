/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:26:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:04:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int		sorter(t_list *a, t_list *b)
{
	char	*as;
	char	*bs;

	as = ((t_file*)(a->content))->name;
	bs = ((t_file*)(b->content))->name;
	return (ft_strcmp(as, bs));
}

int		rsort(t_list *a, t_list *b)
{
	return (sorter(a, b) * -1);
}

int		csort(t_list *a, t_list *b)
{
	long	ta;
	long	tb;

	ta = ((t_file*)(a->content))->stats.st_ctime;
	tb = ((t_file*)(b->content))->stats.st_ctime;
	if (ta == tb)
	{
		ta = ((t_file*)(a->content))->stats.st_ctimespec.tv_nsec;
		tb = ((t_file*)(b->content))->stats.st_ctimespec.tv_nsec;
		if (ta == tb)
			return (sorter(b, a));
	}
	return ((int)(ta - tb));
}

int		rcsort(t_list *a, t_list *b)
{
	return (csort(a, b) * -1);
}

void	*getsorter(int f)
{
	if (f & NOSORT)
		return (NULL);
	else if (f & SIZESORT)
		return ((void*)((f & REVERSESORT) ? &sizesort : &rsizesort));
	else if (f & CTIMESORT)
		return ((void*)((f & REVERSESORT) ? &rcsort : &csort));
	else if (f & TTIMESORT)
		return ((void*)((f & REVERSESORT) ? &ltsort : &ltsortr));
	else
		return ((void*)((f & REVERSESORT) ? &rsort : &sorter));
}
