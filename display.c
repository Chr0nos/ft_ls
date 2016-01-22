/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 22:29:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "pwd.h"
#include "grp.h"
#include <unistd.h>

static char	get_type(t_file *file)
{
	const mode_t	mode = file->stats.st_mode;

	if (S_ISLNK(mode))
		return ('l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISFIFO(mode))
		return ('f');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISREG(mode))
		return ('-');
	return ('u');
}

static int	add_posix(t_file *file, char *buffer)
{
	unsigned char	p;
	int				blk;
	int				perms;

	p = 0;
	blk = 0;
	buffer[p++] = get_type(file);
	while (blk < 3)
	{
		perms = (int)file->stats.st_mode >> (2 - blk) * 3;
		buffer[p] = (perms & S_IROTH) ? 'r' : '-';
		buffer[p + 1] = (perms & S_IWOTH) ? 'w' : '-';
		buffer[p + 2] = (perms & S_IXOTH) ? 'x' : '-';
		p += 3;
		blk++;
	}
	buffer[p++] = ' ';
	buffer[p] = '\0';
	return (p);
}

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

static void	display_file(t_file *file, t_dir *dir, char *buffer)
{
	size_t	p;

	if (dir->flags & LONG)
	{
		aligner(file->size_str, dir->max.filesize);
		aligner(file->links, dir->max.linkslen);
		aligner(file->user, dir->max.userlen);
		aligner(file->group, dir->max.grouplen);
		p = (size_t)add_posix(file, buffer);
		p += ft_strxcpy(buffer + p, file->links, ft_strlen(file->links));
		p += ft_strxcpy(buffer + p, file->user, ft_strlen(file->user));
		p += ft_strxcpy(buffer + p, file->group, ft_strlen(file->group));
		p += ft_strxcpy(buffer + p, file->size_str, ft_strlen(file->size_str));
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

void		display(t_list *lst)
{
	const size_t	dirs = ft_lstsize(lst);
	t_dir			*dir;
	t_list			*dl;
	char			buffer[2048];

	while (lst)
	{
		dir = (t_dir*)lst->content;
		if (!dir)
			continue ;
		if (dirs > 1)
			ft_printf("%s:\n", dir->pathinfo.path);
		if (dir->flags & LONG)
			ft_printf("total %d\n", (int)dir->blocs);
		dl = dir->content;
		while (dl)
		{
			display_file((t_file*)dl->content, dir, (char*)buffer);
			dl = dl->next;
		}
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
