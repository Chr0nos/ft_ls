/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 13:05:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void	pre_parse(t_list *targets, int flags)
{
	t_dir			*rdir;
	int				n;

	if ((!targets) && ((rdir = get_newrdir(".", flags))))
		ls_dir(rdir, 0);
	n = 0;
	while (targets)
	{
		if ((rdir = get_newrdir((char*)(targets->content), flags)))
			ls_dir(rdir, n++);
		targets = targets->next;
		if (targets)
			ft_putchar('\n');
	}
}

int			main(int ac, char **av)
{
	t_list	*targets;
	int		flags;

	if (ac == 1)
		ls_dir(get_newrdir(".", NONE), 0);
	else
	{
		targets = NULL;
		flags = parser(ac, av, &targets);
		pre_parse(targets, flags);
		ft_lstdel(&targets, 0);
	}
	return (0);
}
