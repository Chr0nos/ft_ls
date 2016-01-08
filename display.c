/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 16:39:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void		display(t_list *lst)
{
	const size_t	dirs = ft_lstsize(lst);
	t_dir			*dir;
	t_file			*file;
	t_list			*dl;

	while (lst)
	{
		dir = (t_dir*)lst->content;
		if (dirs > 1)
		{
			ft_putstr(dir->path);
			ft_putstr(":\n");
		}
		dl = dir->content;
		while (dl)
		{
			file = (t_file*)dl->content;
			ft_putendl(file->name);
			dl = dl->next;
		}
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
