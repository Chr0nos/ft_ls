/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 13:12:10 by snicolet         ###   ########.fr       */
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

static char			*getpath(char *dir, char *file)
{
	const char	*tab[3] = { dir, file, NULL };
	char		*fp;

	fp = ft_strunsplit(tab, '/');
	return (fp);
}
/*
** this function add ONE FILE to a dir file list
** return: a pointer to the t_file if success, NULL otherwise
** todo: find a way to prevent so much calls of getsorter (needed just once)
*/

static t_file		*ls_addfile(t_dir *rdir, const char *name, int (*sort)())
{
	t_file			*file;

	if (!(file = malloc(sizeof(t_file))))
		return (NULL);
	file->name = ft_strdup(name);
	file->fullpath = getpath(rdir->pathinfo.path, file->name);
	if (stat(file->fullpath, &file->stats) < 0)
	{
		ft_printf("failed to stat: %s\n", name);
		free(file->fullpath);
		free(file->name);
		free(file);
		return (NULL);
	}
	rdir->size += file->stats.st_size;
	rdir->blocs += file->stats.st_blocks;
	sizetobuff(file->stats.st_size, file->size_str);
	if (rdir->flags & NOSORT)
		ft_lstpush_back(&rdir->content, ft_lstnewlink(file, sizeof(t_file)));
	else
		ft_lstpush_sort(&rdir->content, ft_lstnewlink(file, sizeof(t_file)), 
				sort);
	return (file);
}

static DIR			*ls_dir_open(char *dir)
{
	DIR					*d;

	if (!(d = opendir(dir)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": Failed to open\n", 2);
		return (NULL);
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
	int				(*sort)();

	if (!(d = ls_dir_open(rdir->pathinfo.path)))
		return ;
	sort = (int(*)())getsorter(rdir->flags);
	while ((ent = readdir(d)))
	{
		if ((ent->d_name[0] == '.') && (!(rdir->flags & HIDENS)))
			continue ;
		if (!(file = ls_addfile(rdir, ent->d_name, sort)))
			break ;
		if (((ft_strcmp(ent->d_name, ".")) && (ft_strcmp(ent->d_name, ".."))))
			if ((ent->d_type == DT_DIR) && (rdir->flags & RECURSIVE))
				ls_dir(root, get_rdir(root, file->fullpath, rdir->flags));
		rdir->count++;
	}
	closedir(d);
}
