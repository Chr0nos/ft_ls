/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 16:41:46 by snicolet         ###   ########.fr       */
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
	t_dir	*dir;

	lst = NULL;
	if (ac == 1)
	{
		dir = ls_dir(".", NONE, "*");
		if (dir)
			ft_lstadd(&lst, ft_lstnewlink(dir, sizeof(t_dir)));
	}
	else
		while (ac-- > 1)
		{
			dir = ls_dir(av[ac], NONE, "*");
			if (dir)
				ft_lstadd(&lst, ft_lstnewlink(dir, sizeof(t_dir)));
		}
	if (lst)
	{
		display(lst);
		ft_lstdel(&lst, &ft_lstatomisator);
	}
	return (0);
}
