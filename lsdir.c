/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/20 17:07:29 by snicolet         ###   ########.fr       */
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
	DIR				*d;
	struct dirent	*ent;
	t_file			*file;

	if (!(d = ls_dir_open(rdir->pathinfo.path)))
		return ;
	while ((ent = readdir(d)))
	{
		if ((ent->d_name[0] == '.') && (!(rdir->flags & HIDENS)))
			continue ;
		if (!(file = malloc(sizeof(t_file))))
			break ;
		file->de = ft_memdup(ent, sizeof(struct dirent));
		file->fullpath = getpath(rdir->pathinfo.path, file->de->d_name);
		rdir->size += (size_t)file->stats.st_size;
		rdir->blocs += (size_t)file->stats.st_blocks;
		stat(file->fullpath, &file->stats);
		ft_lstpush_sort(&rdir->content, ft_lstnewlink(file, sizeof(t_file)),
				(int(*)())getsorter(rdir->flags));
		if (((ft_strcmp(ent->d_name, ".")) && (ft_strcmp(ent->d_name, ".."))))
			if ((ent->d_type == DT_DIR) && (rdir->flags & RECURSIVE))
				ls_dir(root, get_rdir(root, file->fullpath, rdir->flags));
		rdir->count++;
	}
	closedir(d);
}
