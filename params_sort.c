/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:23:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 20:28:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <sys/stat.h>

static int		get_type(const char *str)
{
	struct stat		st;

	if (lstat(str, &st) >= 0)
	{
		if (st.st_mode & S_IFDIR)
			return (DIRECTORY);
		return (FILEX);
	}
	return (ERROR);
}

/*
** this function is the sorter of the arguments that ls will take care of
** behind the t_list * there is a simple char *
** about the desired order:
** 1 : errors
** 2 : files
** 3 : directories
** in case of same categories between "a" and "b" : use a name cmp
*/

int				params_sort(t_list *a, t_list *b)
{
	int			at;
	int			bt;
	const char	*as;
	const char	*bs;

	as = (const char *)a->content;
	bs = (const char *)b->content;
	at = get_type(as);
	bt = get_type(bs);
	if (at == FILEX)
	{
		if (bt != FILEX)
			return (1);
	}
	else if (at == DIRECTORY)
	{
		if (bt != DIRECTORY)
			return (1);
	}
	return (ft_lststrcmp(a, b));
}
