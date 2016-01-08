/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 16:58:47 by snicolet         ###   ########.fr       */
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

static int	lsd_append(t_dir *rdir, int flags, char *match, struct dirent *ent)
{
	t_file	file;

	if (((!(flags & HIDENS)) && (ent->d_name[0] == '.')) ||
			(!ft_match(ent->d_name, match)))
		return (0);
	file.de = ft_memdup(ent, sizeof(struct dirent));
	file.name = file.de->d_name;
	file.fullpath = ft_strjoin(rdir->path, file.name);
	stat(file.fullpath, &file.stats);
	ft_lstpush_back(&rdir->content, ft_lstnew(&file, sizeof(t_file)));
	return (1);
}

t_dir		*ls_dir(char *dir, int flags, char *match)
{
	t_dir			*rdir;
	DIR				*d;
	struct dirent	*ent;
	size_t			items;

	if (!(d = opendir(dir)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	if (!(rdir = malloc(sizeof(t_dir))))
		return (NULL);
	items = 0;
	rdir->path = ft_strdup(dir);
	rdir->content = NULL;
	while ((ent = readdir(d)))
	{
		if (lsd_append(rdir, flags, match, ent))
			items++;
	}
	rdir->count = items;
	closedir(d);
	ft_lstsort(&rdir->content, &sorter);
	return (rdir);
}
