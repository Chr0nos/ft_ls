/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 14:51:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 15:01:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int		msort(t_list *a, t_list *b)
{
	const long	ma = ((t_file*)(a->content))->stats.st_mtime;
	const long	mb = ((t_file*)(b->content))->stats.st_mtime;

	return ((int)(ma - mb));
}

int		rmsort(t_list *a, t_list *b)
{
	return (msort(a, b) * -1);
}
