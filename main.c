/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 18:27:37 by snicolet         ###   ########.fr       */
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

	lst = ((t_dir*)(x))->content;
	free(((t_dir*)(x))->path);
	while (lst)
	{
		file = (t_file*)lst->content;
		free(file->fullpath);
		free(file->de);
		free(lst->content);
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(x);
	(void)size;
}

static int	parser(int ac, char **av, t_list **targets)
{
	const char	*strmatch[6] = { "-*R*", "-*l*", "-*a*", "-*r*", "-*f*",
		"-*t*" };
	const int	flagstab[6] = { RECURSIVE, LONG, HIDENS, REVERSESORT, NOSORT,
		MTIMESORT };
	int			mappos;
	int			flags;
	int			p;

	flags = NONE;
	p = 1;
	while (p < ac)
	{
		if (av[p][0] == '-')
		{
			mappos = 6;
			while (mappos--)
				if (ft_match(av[p], strmatch[mappos]))
					flags |= flagstab[mappos];
		}
		else
			ft_lstadd(targets, ft_lstnewlink(av[p], 0));
		p++;
	}
	return (flags);
}

static void	pre_parse(t_lsd *d, t_list **lst, t_list *targets, int flags)
{
	d->match = ft_strdup("*");
	if (!targets)
		ls_dir(".", flags, d->match, lst);
	while (targets)
	{
		ls_dir((char*)(targets->content), flags, d->match, lst);
		targets = targets->next;
	}
	free(d->match);
}

int			main(int ac, char **av)
{
	t_list	*targets;
	t_list	*lst;
	int		flags;
	t_lsd	d;

	lst = NULL;
	if (ac == 1)
		ls_dir(".", NONE, "*", &lst);
	else
	{
		targets = NULL;
		flags = parser(ac, av, &targets);
		pre_parse(&d, &lst, targets, flags);
		ft_lstdel(&targets, 0);
	}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
