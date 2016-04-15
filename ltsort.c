/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltsort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 13:32:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/03 13:35:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ltsort(t_list *a, t_list *b)
{
	const long	ta = ((t_file*)(a->content))->stats.st_atime;
	const long	tb = ((t_file*)(b->content))->stats.st_atime;

	return ((int)(ta - tb));
}

int	ltsortr(t_list *a, t_list *b)
{
	return (ltsort(a, b) * -1);
}
