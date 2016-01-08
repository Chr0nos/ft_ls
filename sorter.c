/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:26:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 14:28:36 by snicolet         ###   ########.fr       */
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
