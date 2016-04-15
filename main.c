/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/03/19 19:39:32 by snicolet         ###   ########.fr       */
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
	n = ((targets) && (targets->next)) ? 1 : 0;
	while (targets)
	{
		if ((rdir = get_newrdir((char*)(targets->content), flags)))
			ls_dir(rdir, n);
		targets = targets->next;
		if (targets)
			ft_putchar('\n');
	}
}

static int	checkpute(int ac, char **av)
{
	while (ac--)
		if (!ft_strlen(av[ac]))
			return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_list	*targets;
	int		flags;

	if (ac == 1)
		ls_dir(get_newrdir(".", NONE), 0);
	else if (checkpute(ac, av))
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
	else
	{
		targets = NULL;
		flags = parser(ac, av, &targets);
		pre_parse(targets, flags);
		ft_lstdel(&targets, 0);
	}
	return (0);
}
