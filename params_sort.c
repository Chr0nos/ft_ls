/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:23:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 20:37:05 by snicolet         ###   ########.fr       */
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
	const char	*as = (const char *)a->content;
	const char	*bs = (const char *)b->content;
	const int	at = get_type(as);
	const int	bt = get_type(bs);

	if ((at == ERROR) && (strcmp(as, bs) != 0))
		return (1);
	else if ((at == FILEX) && (bt != FILEX))
		return (1);
	else if ((at == DIRECTORY) && (bt != DIRECTORY))
		return (1);
	return (strcmp(as, bs));
}
