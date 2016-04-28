/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:23:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:32:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

/*
** this function is the sorter of the arguments that ls will take care of
** behind the t_list * there is a simple char *
** about the desired order:
** 1 : errors
** 2 : files
** 3 : directories
** in case of same categories between "a" and "b" : use a name cmp
*/

int		params_sort(t_list *a, t_list *b)
{
	return (ft_lststrcmp(a, b));
}
