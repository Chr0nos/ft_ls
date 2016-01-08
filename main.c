/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 14:50:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

t_dir		*ls_dir(char *dir, int flags)
{
	t_file			file;
	t_dir			*rdir;
	DIR				*d;
	struct dirent	*ent;
	size_t			items;

	if (!(d = opendir(dir)))
		return (0);
	if (!(rdir = malloc(sizeof(t_dir))))
		return (NULL);
	items = 0;
	rdir->path = ft_strdup(dir);
	rdir->content = NULL;
	while ((ent = readdir(d)))
	{
		if ((!(flags & HIDENS)) && (ent->d_name[0] == '.'))
			continue ;
		file.de = ft_memdup(ent, sizeof(struct dirent));
		file.name = file.de->d_name;
		file.fullpath = ft_strjoin(dir, file.name);
		stat(file.fullpath, &file.stats);
		ft_lstpush_back(&rdir->content, ft_lstnew(&file, sizeof(t_file)));
		items++;
	}
	rdir->count = items;
	closedir(d);
	//ft_lstsort(&rdir->content, &sorter);
	return (rdir);
}

static void	ft_lstatomisator(void *x, size_t size)
{
	t_list	*lst;
	t_file	*file;

	lst = ((t_dir*)(x))->content;
	while (lst)
	{
		file = (t_file*)lst->content;
		free(file->de);
		free(lst->content);
		lst = lst->next;
	}
	free(x);
	(void)size;
}

void		display(t_list *lst)
{
	t_dir	*dir;
	t_file	*file;
	t_list	*dl;

	while (lst)
	{
		dir = (t_dir*)lst->content;
		//ft_printf("dir path: %s items: %d\n", dir->path, (int)dir->count);
		dl = dir->content;
		while (dl)
		{
			file = (t_file*)dl->content;
			ft_putendl(file->name);
			dl = dl->next;
		}
		lst = lst->next;
	}
}

int			main(int ac, char **av)
{
	t_list	*lst;
	t_dir	*dir;

	(void)av;
	lst = NULL;
	if (ac == 1)
	{
		dir = ls_dir(".", NONE);
		ft_lstadd(&lst, ft_lstnewlink(dir, sizeof(t_dir)));
	}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
