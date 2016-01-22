/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 12:31:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/22 15:34:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <string.h>
#include <stdlib.h>

void	*clean_file(t_file *file)
{
	free(file->fullpath);
	free(file->name);
	free(file);
	return (NULL);
}

/*
** this function is called a the very end of the program,
** consider it as the garbage collector, it here to prevent any memory leak
*/

void	ft_lstatomisator(void *x, size_t size)
{
	t_list	*lst;
	t_file	*file;
	t_list	*next;
	t_dir	*rdir;

	if (!x)
		return ;
	rdir = (t_dir*)x;
	lst = rdir->content;
	free(rdir->path);
	free(rdir->pathinfo.path);
	while (lst)
	{
		file = (t_file*)lst->content;
		clean_file(file);
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(rdir);
	(void)size;
}

/*
** this function is called just before the display (in the main)
** purpose: remove any empty directory in the display list
** this case can occurs when ls is required to list a file inside a directory
** with insufisent perms: ex: ./ft_ls -l /Library/Scripts/42/munki
*/

void	clean_emptydirs(t_list **root)
{
	t_dir	*rdir;
	t_list	*lst;
	t_list	*next;

	lst = *root;
	while (lst)
	{
		rdir = (t_dir*)lst->content;
		next = lst->next;
		if (rdir->count == 0)
		{
			rdir_clean(rdir);
			ft_lstremove(&lst, root, 0);
		}
		lst = next;
	}
}
