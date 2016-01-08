/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 01:49:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

t_dir		*ls_dir(char *dir, int rec)
{
	t_file			*file;
	t_dir			*rdir;
	DIR				*d;
	struct dirent	*ent;
	size_t			items;

	if (!(d = opendir(dir)))
		return (0);
	if (!(file = malloc(sizeof(t_file))))
		return (NULL);
	if (!(rdir = malloc(sizeof(t_dir))))
	{
		free(file);
		return (NULL);
	}
	items = 0;
	rdir->path = ft_strdup(dir);
	rdir->content = NULL;
	while ((ent = readdir(d)))
	{
		file->de = ft_memdup(ent, sizeof(struct dirent));
		file->name = file->de->d_name;
		ft_lstpush_back(&rdir->content, ft_lstnewlink(file, sizeof(t_file)));
		(void)rec;
		items++;
	}
	closedir(d);
	return (rdir);
}

static void	ft_lstatomisator(void *x, size_t size)
{
	(void)size;
	free(x);
}

void		display(t_list *lst)
{
	t_dir	*dir;
	t_file	*file;
	t_list	*fl;

	while (lst)
	{
		dir = (t_dir*)lst->content;
		fl = dir->content;
		while (fl)
		{
			file = (t_file*)fl->content;
			ft_putendl(file->name);
			fl = fl->next;
		}
		lst = lst->next;
	}
}

int			main(int ac, char **av)
{
	t_list	*lst;

	(void)av;
	lst = NULL;
	if (ac == 1)
	{
		ft_lstadd(&lst, ft_lstnewlink(ls_dir(".", 0), sizeof(t_dir)));
	}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
