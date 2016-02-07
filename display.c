/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 20:54:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "pwd.h"
#include "grp.h"
#include <unistd.h>

static void		display_link(const char *path)
{
	char		buffer[1024];
	ssize_t		rl;

	ft_strcpy(buffer, " -> ");
	rl = readlink(path, buffer + 4, 1024);
	buffer[rl + 4] = '\0';
	ft_putendl(buffer);
}

static size_t	ft_strxcpy(char *dest, const char *src, const size_t len)
{
	ft_memcpy(dest, src, len);
	dest[len] = ' ';
	dest[len + 1] = '\0';
	return (len + 1);
}

/*
** this function is here to display ONE file to the terminal
** the buffer is in the stack, i use write to prevent the ft_strlen of ft_putstr
** p = the current lenght of the buffer
*/

static void		display_file(t_file *file, t_dir *dir, char *buffer)
{
	size_t	p;

	if (dir->flags & LONG)
	{
		ft_stralign_right(file->size_str, dir->max.filesize);
		ft_stralign_right(file->links, dir->max.linkslen + 1);
		ft_stralign_left(file->user, dir->max.userlen + 1);
		ft_stralign_left(file->group, dir->max.grouplen + 1);
		p = (size_t)add_posix(file, buffer);
		p += ft_strxcpy(buffer + p, file->links, ft_strlen(file->links));
		p += ft_strxcpy(buffer + p, file->user, ft_strlen(file->user));
		p += ft_strxcpy(buffer + p, file->group, ft_strlen(file->group));
		p += ft_strxcpy(buffer + p, file->size_str, ft_strlen(file->size_str));
		p += ft_strxcpy(buffer + p, file->time, ft_strlen(file->time) - 1);
		write(1, buffer, p);
		if (S_ISLNK(file->stats.st_mode))
		{
			ft_putstr(file->name);
			display_link(file->fullpath);
		}
		else
			ft_putendl(file->name);
	}
	else
		ft_putendl(file->name);
}

void			display_dir(t_dir *rdir, int n)
{
	t_list	*lst;
	char	buffer[2048];

	lst = rdir->content;
	if (n > 0)
		ft_printf("%s:\n", rdir->pathinfo.path);
	if ((rdir->flags & LONG) && (n >= 0) && (lst))
		ft_printf("total %d\n", (int)rdir->blocs);
	while (lst)
	{
		display_file((t_file*)lst->content, rdir, (char*)buffer);
		lst = lst->next;
	}
}

void			display(t_list *lst)
{
	t_dir			*dir;
	int				n;

	n = 0;
	while (lst)
	{
		dir = (t_dir*)lst->content;
		display_dir(dir, n++);
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
