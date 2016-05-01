/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortrdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 17:19:10 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/01 18:54:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ls_sortrdir(t_list *a, t_list *b)
{
	if (((t_dir*)a->content)->flags & REVERSESORT)
		return (-ft_strcmp(((t_dir*)a->content)->path,
			((t_dir*)b->content)->path));
	return (ft_strcmp(((t_dir*)a->content)->path, ((t_dir*)b->content)->path));
}
