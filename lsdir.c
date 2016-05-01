/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/01 17:19:18 by snicolet         ###   ########.fr       */
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

	file_init(file);
	pwd = getpwuid(file->stats.st_uid);
	grp = getgrgid(file->stats.st_gid);
	ft_strcpy(file->user, pwd->pw_name);
	ft_strcpy(file->group, grp->gr_name);
	sizetobuff((off_t)file->stats.st_nlink, file->links);
	lens[ULEN] = ft_strlen(file->user);
	lens[GLEN] = ft_strlen(file->group);
	sizetobuff(file->stats.st_size, file->size_str);
	lens[SLEN] = ft_strlen(file->size_str);
	lens[LLEN] = ft_strlen(file->links);
	timeloader(file, file->time, rdir->flags);
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
		ft_printf("ls: %s: %s\n", file->fullpath, strerror(errno));
		return (clean_file(file));
	}
	rdir->blocs += file->stats.st_blocks;
	if (((rdir->size += file->stats.st_size) + 1) && (rdir->flags & LONG))
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

static DIR			*ls_dir_open(t_dir *rdir, int total_items, int total_files)
{
	DIR					*d;
	struct stat			stats;
	const char			*dir = rdir->pathinfo.path;
	char				b[1024];

	if (!(d = opendir(dir)))
	{
		if ((lstat(dir, &stats) >= 0) && (!(stats.st_mode & S_IFDIR)))
		{
			ft_strcpy(b, dir);
			ft_strcpy(rdir->pathinfo.path, ".");
			if (ls_addfile(rdir, b, (int(*)())getsorter(rdir->flags)))
				display_dir(rdir, -1, total_items, total_files);
		}
		else
		{
			ft_strcpy(b, "ls: ");
			ft_strcat(b, dir);
			ft_strcat(b, ": ");
			ft_strcat(b, strerror(errno));
			ft_putendl_fd(b, 2);
			return (NULL);
		}
	}
	return (d);
}

inline static int	ls_dir_while(struct dirent *ent, t_list **rlst, t_dir *rdir,
		int (*sort)())
{
	char	*name;
	t_file	*file;

	name = ent->d_name;
	if ((name[0] == '.') && (!(rdir->flags & HIDENS)))
		return (0);
	if (((!ft_strcmp(name, ".")) || (!ft_strcmp(name, ".."))) &&
		(rdir->flags & NODOTANDDOTDOT))
		return (0);
	if (!(file = ls_addfile(rdir, ent->d_name, sort)))
		return (-1);
	if (((file->stats.st_mode & S_IFDIR) && (rdir->flags & RECURSIVE)) &&
		(((ft_strcmp(name, ".")) && (ft_strcmp(name, "..")))))
	{
		ft_lstpush_sort(rlst,
			ft_lstnewlink(get_newrdir(file->fullpath, rdir->flags), 0),
			&ls_sortrdir);
	}
	return (1);
}

/*
** this function list a dirctory and append it to the dir list (root)
** it need the rdir entry given by the caller (with get_rdir or search_rdir)
** each file is append by ls_addfile
** total_dirs and total_files are the total IN PARAMETER not in the list
** i mean the ones in the arv[] tab
*/

void				ls_dir(t_dir *rdir, int n, int total_dirs, int total_files)
{
	DIR				*d;
	struct dirent	*ent;
	int				(*sort)();
	t_list			*rlst;

	sort = (int(*)())getsorter(rdir->flags);
	if ((rdir->flags & NODIRENTER) && (get_type(rdir->path) == DIRECTORY))
	{
		ls_addfile(rdir, rdir->path, sort);
		display_dir(rdir, n, -1, -1);
		return ;
	}
	if (!(d = ls_dir_open(rdir, total_dirs, total_files)))
		return ;
	rlst = NULL;
	while (((ent = readdir(d))) && (ls_dir_while(ent, &rlst, rdir, sort) >= 0))
		;
	closedir(d);
	display_dir(rdir, n, total_dirs, total_files);
	while (rlst)
	{
		ls_dir((t_dir*)(rlst->content), 1, total_dirs, total_files);
		rlst = rlst->next;
	}
}
