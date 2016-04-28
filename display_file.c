/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:14:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <grp.h>
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

static size_t	display_file_prepair(t_file *file, char *buffer)
{
	size_t	p;

	p = (size_t)add_posix(file, buffer);
	p += ft_strxcpy(buffer + p, file->links, ft_strlen(file->links));
	p += ft_strxcpy(buffer + p, file->user, ft_strlen(file->user));
	p += ft_strxcpy(buffer + p, file->group, ft_strlen(file->group));
	p += ft_strxcpy(buffer + p, file->size_str, ft_strlen(file->size_str));
	p += ft_strxcpy(buffer + p, file->time, ft_strlen(file->time) - 1);
	return (p);
}

/*
** this function is here to display ONE file to the terminal
** the buffer is in the stack, i use write to prevent the ft_strlen of ft_putstr
** p = the current lenght of the buffer
*/

void			display_file(t_file *file, t_dir *dir, char *buffer)
{
	if (dir->flags & INODES)
		display_inode(file);
	if (dir->flags & LONG)
	{
		ft_stralign_right(file->size_str, dir->max.filesize);
		ft_stralign_right(file->links, dir->max.linkslen + 1);
		ft_stralign_left(file->user, dir->max.userlen + 1);
		ft_stralign_left(file->group, dir->max.grouplen + 1);
		write(1, buffer, display_file_prepair(file, buffer));
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
