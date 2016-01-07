/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 00:12:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int			ls_dir(char *dir, t_list **lst, int rec)
{
	t_file			file;
	DIR				*d;
	struct dirent	*ent;

	if (!(d = opendir(dir)))
		return (0);
	while ((ent = readdir(d)))
	{
		file.path = ft_strdup(dir);
		file.de = ft_memdup(ent, sizeof(struct dirent));
		file.name = file.de->d_name;
		ft_lstpush_back(lst, ft_lstnew(&file, sizeof(t_file)));
		(void)rec;
	}
	closedir(d);
	return (1);
}

static void	ft_lstatomisator(void *x, size_t size)
{
	t_file	*f;

	(void)size;
	f = (t_file*)x;
	free(f->de);
	free(x);
}

void		display(t_list *lst)
{
	t_file	*file;

	while (lst)
	{
		file = (t_file*)(lst->content);
		ft_putendl(file->de->d_name);
		lst = lst->next;
	}
}

int			main(int ac, char **av)
{
	t_list	*lst;

	lst = NULL;
	if (ac == 1)
		ls_dir(".", &lst, 0);
	else
		while (--ac)
			ls_dir(av[ac], &lst, 0);
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
