/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/09 13:44:31 by snicolet         ###   ########.fr       */
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

int			main(int ac, char **av)
{
	t_list	*lst;
	int		flags;

	flags = NONE | RECURSIVE;
	lst = NULL;
	if (ac == 1)
		ls_dir(".", flags, "*", &lst);
	else
		while (ac-- > 1)
			ls_dir(av[ac], flags, "*", &lst);
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
