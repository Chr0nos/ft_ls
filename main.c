/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 02:15:10 by snicolet         ###   ########.fr       */
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

	lst = ((t_dir*)(x))->content;
	while (lst)
	{
		file = (t_file*)lst->content;
		free(file->fullpath);
		free(file->de);
		free(lst->content);
		lst = lst->next;
	}
	free(x);
	(void)size;
}

static int 	parser(int ac, char **av, t_list **targets)
{
	int		flags;
	int		p;

	flags = NONE;
	p = 1;
	while (p < ac)
	{
		if (av[p][0] == '-')
		{
			if (ft_match(av[p], "-*R*"))
				flags |= RECURSIVE;
			if (ft_match(av[p], "-*l*"))
				flags |= LONG;
			if (ft_match(av[p], "-*a*"))
				flags |= HIDENS;
			if (ft_match(av[p], "-*r*"))
				flags |= REVERSESORT;
		}
		else
			ft_lstadd(targets, ft_lstnewlink(av[p], 0));
		p++;
	}
	return (flags);
}

int			main(int ac, char **av)
{
	t_list	*targets;
	t_list	*to;
	t_list	*lst;
	int		flags;
	t_lsd	d;

	flags = NONE | RECURSIVE;
	lst = NULL;
	if (ac == 1)
		ls_dir(".", flags, "*", &lst);
	else
	{
		d.match = ft_strdup("*");
		targets = NULL;
		flags = parser(ac, av, &targets);
		to = targets;
		while (targets)
		{
			ls_dir((char*)(targets->content), flags, d.match, &lst);
			targets = targets->next;
		}
		if (to)
			free(to);
	}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
