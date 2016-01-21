/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 16:49:13 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "pwd.h"
#include "grp.h"

static char	get_type(t_file *file)
{
	const mode_t	mode = file->stats.st_mode;

	if (mode & S_IFBLK)
		return ('b');
	if (mode & S_IFDIR)
		return ('d');
	if (mode & S_IFCHR)
		return ('c');
	if (mode & S_IFIFO)
		return ('f');
	if (mode & S_IFLNK)
		return ('l');
	if (mode & S_IFREG)
		return ('-');
	if (mode & S_IFSOCK)
		return ('s');
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

static void	display_file(t_file *file, t_dir *dir, char *buffer)
{
	int				p;
	struct passwd	*pwd;
	struct group	*grp;
	unsigned int	userlen;

	if (dir->flags & LONG)
	{
		pwd = getpwuid(file->stats.st_uid);
		grp = getgrgid(file->stats.st_gid);
		p = add_posix(file, buffer);
		p += ft_itobuff(buffer + p, (int)file->stats.st_nlink, 10,
				"0123456789");
		buffer[p++] = ' ';
		userlen = (unsigned int)ft_strlen(pwd->pw_name);
		ft_memcpy(&buffer[p], pwd->pw_name, userlen);
		p += userlen;
		buffer[p++] = ' ';
		userlen = (unsigned int)ft_strlen(grp->gr_name);
		ft_memcpy(&buffer[p], grp->gr_name, userlen);
		p += userlen;
		buffer[p++] = ' ';
		ft_strcpy(&buffer[p], file->size_str);
		p += ft_strlen(file->size_str);
		ft_strcpy(&buffer[p], " ");
		ft_putstr(buffer);
	}
	ft_putendl(file->name);
}

static size_t	pre_display(t_list *lst)
{
	t_dir		*dir;
	t_file		*file;
	t_list		*flst;

	while (lst)
	{
		dir = (t_dir*)lst->content;
		flst = dir->content;
		while (flst)
		{
			file = flst->content;
			aligner(file->size_str, 8);
			flst = flst->next;
		}
		lst = lst->next;
	}
	return (0);
}

void		display(t_list *lst)
{
	const size_t	dirs = ft_lstsize(lst) + pre_display(lst);
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
