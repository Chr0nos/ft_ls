/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:26:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 15:33:31 by snicolet         ###   ########.fr       */
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
	const long	ta = ((t_file*)(a->content))->stats.st_ctime;
	const long	tb = ((t_file*)(b->content))->stats.st_ctime;

	return ((int)(ta - tb));
}

int		rcsort(t_list *a, t_list *b)
{
	return (csort(a, b) * -1);
}
