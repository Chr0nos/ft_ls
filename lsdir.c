/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/22 19:11:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

static char			*getpath(char *dir, char *file)
{
	const char	*tab[3] = { dir, file, NULL };
	char		*fp;

	fp = ft_strunsplit(tab, '/');
	return (fp);
}

/*
** this function update user and group info about each file
** it also update rdir to store the user/group lens for column alignement
** (alignement is done into display function, not here)
** called by ls_addfile (below)
*/

static void			update_infos(t_dir *rdir, t_file *file)
{
	struct passwd			*pwd;
	struct group			*grp;
	size_t					lens[4];

	pwd = getpwuid(file->stats.st_uid);
	grp = getgrgid(file->stats.st_gid);
	ft_strcpy(file->user, pwd->pw_name);
	ft_strcpy(file->group, grp->gr_name);
	sizetobuff((off_t)file->stats.st_nlink, file->links);
	lens[ULEN] = ft_strlen(file->user);
	lens[GLEN] = ft_strlen(file->group);
	ft_memset(file->size_str, 0, 48);
	sizetobuff(file->stats.st_size, file->size_str);
	lens[SLEN] = ft_strlen(file->size_str);
	lens[LLEN] = ft_strlen(file->links);
	ft_strcpy(file->time, ctime(&file->stats.st_mtime));
	if (lens[ULEN] > rdir->max.userlen)
		rdir->max.userlen = (unsigned int)lens[ULEN];
	if (lens[GLEN] > rdir->max.grouplen)
		rdir->max.grouplen = (unsigned int)lens[GLEN];
	if (lens[LLEN] > rdir->max.linkslen)
		rdir->max.linkslen = (unsigned int)lens[LLEN];
	if ((!(rdir->flags & HUMAN)) && (lens[SLEN] > rdir->max.filesize))
		rdir->max.filesize = (unsigned int)lens[SLEN];
}

/*
** this function add ONE FILE to a dir file list
** return: a pointer to the t_file if success, NULL otherwise
** todo: find a way to prevent so much calls of getsorter (needed just once)
** called by: ls_dir & ls_dir_open
*/

static t_file		*ls_addfile(t_dir *rdir, const char *name, int (*sort)())
{
	t_file			*file;

	if (!(file = malloc(sizeof(t_file))))
		return (NULL);
	file->name = ft_strdup(name);
	file->fullpath = getpath(rdir->pathinfo.path, file->name);
	if (lstat(file->fullpath, &file->stats) < 0)
	{
		ft_printf("ft_ls: %s: %s\n", file->fullpath, strerror(errno));
		return (clean_file(file));
	}
	rdir->blocs += file->stats.st_blocks;
	if ((rdir->size += file->stats.st_size) && (rdir->flags & LONG))
		update_infos(rdir, file);
	if (rdir->flags & HUMAN)
		ft_wsize((unsigned long long)file->stats.st_size, file->size_str);
	else
		sizetobuff(file->stats.st_size, file->size_str);
	if (rdir->flags & NOSORT)
		ft_lstpush_back(&rdir->content, ft_lstnewlink(file, sizeof(t_file)));
	else
		ft_lstpush_sort(&rdir->content, ft_lstnewlink(file, sizeof(t_file)),
				sort);
	rdir->count++;
	return (file);
}

static DIR			*ls_dir_open(t_dir *rdir)
{
	DIR					*d;
	struct stat			stats;
	const char			*dir = rdir->pathinfo.path;
	char				b[1024];

	if (!(d = opendir(dir)))
	{
		if (lstat(dir, &stats) >= 0)
		{
			ft_strcpy(b, dir);
			ft_strcpy(rdir->pathinfo.path, ".");
			ls_addfile(rdir, b, (int(*)())getsorter(rdir->flags));
		}
		else
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(dir, 2);
			ft_putstr_fd(": Failed to open\n", 2);
			return (NULL);
		}
	}
	return (d);
}

/*
** this function list a dirctory and append it to the dir list (root)
** it need the rdir entry given by the caller (with get_rdir or search_rdir)
** each file is append by ls_addfile
*/

void				ls_dir(t_list **root, t_dir *rdir)
{
	DIR				*d;
	struct dirent	*ent;
	t_file			*file;
	char			*name;
	int				(*sort)();

	if (!(d = ls_dir_open(rdir)))
		return ;
	sort = (int(*)())getsorter(rdir->flags);
	while ((ent = readdir(d)))
	{
		name = ent->d_name;
		if ((name[0] == '.') && (!(rdir->flags & HIDENS)))
			continue ;
		if (((!ft_strcmp(name, ".")) || (!ft_strcmp(name, ".."))) &&
			(rdir->flags & NODOTANDDOTDOT))
			continue ;
		if (!(file = ls_addfile(rdir, ent->d_name, sort)))
			break ;
		if (((ft_strcmp(name, ".")) && (ft_strcmp(name, ".."))))
			if ((ent->d_type == DT_DIR) && (rdir->flags & RECURSIVE))
				ls_dir(root, get_rdir(root, file->fullpath, rdir->flags));
	}
	closedir(d);
}
