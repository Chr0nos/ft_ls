/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/19 09:07:16 by snicolet         ###   ########.fr       */
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

static int			lsd_append(t_lsd *x)
{
	t_file	file;

	if (((!(x->rdir->flags & HIDENS)) && (x->ent->d_name[0] == '.')) ||
			(!ft_match(x->ent->d_name, x->match)))
		return (0);
	file.de = ft_memdup(x->ent, sizeof(struct dirent));
	file.name = file.de->d_name;
	file.fullpath = getpath(x->rdir->pathinfo.path, file.name);
	if (stat(file.fullpath, &file.stats) < 0)
		ft_printf("failed to stat: %s: %s\n", file.fullpath, strerror(errno));
	if ((x->ent->d_type == DT_DIR) && (x->rdir->flags & RECURSIVE) &&
			(ft_strcmp(file.name, ".") != 0) && (ft_strcmp(file.name, "..")))
		ls_dir(x->root, get_rdir(x->root, file.fullpath, x->rdir->flags));
	x->rdir->size += (size_t)file.stats.st_size;
	x->rdir->blocs += (size_t)file.stats.st_blocks;
	ft_lstpush_sort(x->root, ft_lstnew(&x->rdir->content, sizeof(t_file)), &sort);
	return (1);
}

static DIR			*ls_dir_open(char *dir)
{
	DIR	*d;

	if (!(d = opendir(dir)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": Failed to open\n", 2);
		return (NULL);
	}
	return (d);
}

void				ls_dir(t_list **root, t_dir *rdir)
{
	DIR			*d;
	t_lsd		lsd;

	if (!(d = ls_dir_open(rdir->pathinfo.path)))
		return ;
	lsd.root = root;
	lsd.rdir = rdir;
	lsd.match = rdir->pathinfo.filemask;
	while ((lsd.ent = readdir(d)))
		if (lsd_append(&lsd))
			rdir->count++;
	closedir(d);
	ft_strdel(&rdir->pathinfo.filemask);
}
