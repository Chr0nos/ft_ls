/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 16:46:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	pre_parse_get_dirs_count(t_list *targets)
{
	char	*item;
	int		dirs;

	dirs = 0;
	while (targets)
	{
		item = (char*)targets->content;
		if (get_type(item) == DIRECTORY)
			dirs++;
		targets = targets->next;
	}
	return (dirs);
}

/*
** here the targets list contains char *
*/

static void	pre_parse(t_list *targets, int flags)
{
	t_dir			*rdir;
	int				n;
	int				total_dirs_bool;

	total_dirs_bool = pre_parse_get_dirs_count(targets);
	n = (total_dirs_bool == 0) ? -1 : 0;
	if (flags & RECURSIVE)
	{
		total_dirs_bool = 1;
		n = 1;
	}
	if ((!targets) && ((rdir = get_newrdir(".", flags))))
		ls_dir(rdir, 0, total_dirs_bool);
	while (targets)
	{
		if ((rdir = get_newrdir((char*)(targets->content), flags)))
			ls_dir(rdir, n++, total_dirs_bool);
		targets = targets->next;
	}
}

/*
** this function is used to know if there is a empty parameter
** example: ./ft_ls main.c Makefile ""
** called by: main()
*/

static int	checkpute(int ac, char **av)
{
	while (ac--)
		if (av[ac][0] == '\0')
			return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_list	*targets;
	int		flags;

	if (ac == 1)
		ls_dir(get_newrdir(".", NONE), 0, 0);
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
