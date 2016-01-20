/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/20 11:26:12 by snicolet         ###   ########.fr       */
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
	t_list	*file_item;
	char	*name;

	ft_printf("listing: %s\n", x->ent->d_name);
	if ((!(x->rdir->flags & HIDENS)) && (x->ent->d_name[0] == '.'))
		return (0);
	file.de = ft_memdup(x->ent, sizeof(struct dirent));
	name = file.de->d_name;
	file.fullpath = getpath(x->rdir->pathinfo.path, name);
	if (stat(file.fullpath, &file.stats) < 0)
		ft_printf("failed to stat: %s: %s\n", file.fullpath, strerror(errno));
	x->rdir->size += (size_t)file.stats.st_size;
	x->rdir->blocs += (size_t)file.stats.st_blocks;
	if (!(file_item = ft_lstnew(&file, sizeof(t_file))))
	{
		free(file.de);
		return (0);
	}
	ft_lstadd(x->root, file_item);
	//ft_lstpush_sort(x->root, file_item, (int(*)())x->sorter);
	if ((x->ent->d_type == DT_DIR) && (x->rdir->flags & RECURSIVE) &&
			(ft_strcmp(name, ".") != 0) && (ft_strcmp(name, "..")))
		ls_dir(x->root, get_rdir(x->root, file.fullpath, x->rdir->flags));
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
	lsd.sorter = (int *)getsorter(rdir->flags);
	lsd.root = root;
	lsd.rdir = rdir;
	while ((lsd.ent = readdir(d)))
		if (lsd_append(&lsd))
			rdir->count++;
	closedir(d);
}
