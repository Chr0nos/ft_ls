/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 22:43:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void	ft_lstatomisator(void *x, size_t size)
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
		free(file->fullpath);
		free(file->name);
		free(lst->content);
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(x);
	(void)size;
}

static void	pre_parse(t_list **lst, t_list *targets, int flags)
{
	t_dir	*rdir;

	if ((!targets) && ((rdir = get_rdir(lst, ".", flags))))
		ls_dir(lst, rdir);
	while (targets)
	{
		if ((rdir = get_rdir(lst, (char*)(targets->content), flags)))
			ls_dir(lst, rdir);
		targets = targets->next;
	}
}

int			main(int ac, char **av)
{
	t_list	*targets;
	t_list	*lst;
	int		flags;

	lst = NULL;
	if (ac == 1)
		ls_dir(&lst, get_rdir(&lst, ".", NONE));
	else
	{
		targets = NULL;
		flags = parser(ac, av, &targets);
		pre_parse(&lst, targets, flags);
		ft_lstdel(&targets, 0);
	}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
