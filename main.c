/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 22:55:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
** returns the number of directories in the arguments list
** called by: pre_parse
*/

static void	pre_parse_get_dirs_count(t_list *targets, int *dirs, int *files)
{
	char	*item;
	int		type;

	*dirs = 0;
	*files = 0;
	while (targets)
	{
		type = get_type(item);
		item = (char*)targets->content;
		if (type == DIRECTORY)
			(*dirs)++;
		else if (type == FILEX)
			(*files)++;
		targets = targets->next;
	}
}

/*
** here the targets list contains char *
** called by: main
*/

static void	pre_parse(t_list *targets, int flags)
{
	t_dir			*rdir;
	int				n;
	int				dirs_count;
	int				files_count;

	pre_parse_get_dirs_count(targets, &dirs_count, &files_count);
	if (flags & RECURSIVE)
		dirs_count = 1;
	if ((!targets) && ((rdir = get_newrdir(".", flags))))
		ls_dir(rdir, 0, dirs_count, 0);
	n = 0;
	while (targets)
	{
		if ((rdir = get_newrdir((char*)(targets->content), flags)))
			ls_dir(rdir, n++, dirs_count, files_count);
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
		ls_dir(get_newrdir(".", NONE), 0, 0, 0);
	else if (checkpute(ac, av))
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
	else
	{
		targets = NULL;
		flags = parser(ac, av, &targets);
		if (flags >= 0)
			pre_parse(targets, flags);
		ft_lstdel(&targets, 0);
	}
	return (0);
}
