/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/01 16:53:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void			putslash_ifneeded(int flags, t_file *file)
{
	ft_putstr(file->name);
	if ((flags & SLASH) && (file->stats.st_mode & S_IFDIR))
		ft_putchar('/');
	ft_putchar('\n');
}

/*
** this function will display the current dir
** if n is >= to 0 a new line will be inserted before
** called by: ls_dir_open / ls_dir
*/

void			display_dir(t_dir *rdir, int n, int total_dirs, int total_files)
{
	t_list	*lst;
	char	buffer[2048];

	(void)total_files;
	lst = rdir->content;
	if ((rdir->stats.st_mode & S_IFDIR) && (!(rdir->flags & NODIRENTER)))
	{
		if (n > 0)
			ft_putchar('\n');
		if (total_dirs >= 1)
			ft_printf("%s:\n", rdir->pathinfo.path);
		if ((rdir->flags & LONG) && (rdir->count > 0))
			ft_printf("total %d\n", (int)rdir->blocs);
	}
	while (lst)
	{
		display_file((t_file*)lst->content, rdir, (char*)buffer);
		lst = lst->next;
	}
}
