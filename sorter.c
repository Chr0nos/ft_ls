/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:26:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/19 09:31:02 by snicolet         ###   ########.fr       */
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
	return (ft_strcasecmp(as, bs));
}

int		rsort(t_list *a, t_list *b)
{
	return (sorter(a, b) * -1);
}

int		csort(t_list *a, t_list *b)
{
	const long	ta = ((t_file*)(a->content))->stats.st_ctime;
	const long	tb = ((t_file*)(b->content))->stats.st_ctime;

	return ((int)(ta - tb));
}

int		rcsort(t_list *a, t_list *b)
{
	return (csort(a, b) * -1);
}

int		sort(t_list *a, t_list *b)
{
	const int	f = ((t_dir*)(a->content))->flags;

	if (f & NOSORT)
		return (0);
	else if (f & SIZESORT)
		return ((f & REVERSESORT) ? sizesort(a, b) : rsizesort(a, b));
	else if (f & MTIMESORT)
		return ((f & REVERSESORT) ? msort(a, b) : rmsort(a, b));
	else if (f & CTIMESORT)
		return ((f & REVERSESORT) ? rcsort(a, b) : csort(a, b));
	else
		return ((f & REVERSESORT) ? rsort(a, b) : sorter(a , b));
}
