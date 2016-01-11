/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:40:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 18:08:17 by snicolet         ###   ########.fr       */
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

static char	*getpath(char *dir, char *file)
{
	const char	*tab[3] = { dir, file, NULL };
	char		*fp;

	fp = ft_strunsplit(tab, '/');
	return (fp);
}

static int	lsd_append(t_lsd *x)
{
	t_file	file;

	if (((!(x->rdir->flags & HIDENS)) && (x->ent->d_name[0] == '.')) ||
			(!ft_match(x->ent->d_name, x->match)))
		return (0);
	file.de = ft_memdup(x->ent, sizeof(struct dirent));
	file.name = file.de->d_name;
	file.fullpath = getpath(x->rdir->path, file.name);
	stat(file.fullpath, &file.stats);
	if ((x->ent->d_type == DT_DIR) && (x->rdir->flags & RECURSIVE) &&
			(ft_strcmp(file.name, ".") != 0) && (ft_strcmp(file.name, "..")))
		ls_dir(file.fullpath, x->rdir->flags, x->match, x->root);
	x->rdir->size += (unsigned long long)file.stats.st_blocks;
	ft_lstpush_back(&x->rdir->content, ft_lstnew(&file, sizeof(t_file)));
	return (1);
}

static DIR	*ls_dir_open(char *dir)
{
	DIR	*d;

	if (!(d = opendir(dir)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	return (d);
}

static void	sort(t_dir *rdir)
{
	const int		f = rdir->flags;

	if (f & NOSORT)
		return ;
	else if (f & MTIMESORT)
		ft_lstsort(&rdir->content, (f & REVERSESORT) ? &msort : &rmsort);
	else if (f & CTIMESORT)
		ft_lstsort(&rdir->content, (f & REVERSESORT) ? &rcsort : &csort);
	else
		ft_lstsort(&rdir->content, (f & REVERSESORT) ? &rsort : &sorter);
}

void		ls_dir(char *dir, int flags, char *match, t_list **root)
{
	t_dir			*rdir;
	DIR				*d;
	size_t			items;
	t_lsd			lsd;

	if ((!(d = ls_dir_open(dir))) ||
			(!(rdir = malloc(sizeof(t_dir)))))
		return ;
	items = 0;
	rdir->path = ft_strdup(dir);
	rdir->content = NULL;
	rdir->flags = flags;
	rdir->size = 0;
	lsd.match = match;
	lsd.root = root;
	lsd.rdir = rdir;
	while ((lsd.ent = readdir(d)))
		if (lsd_append(&lsd))
			items++;
	rdir->count = items;
	closedir(d);
	sort(rdir);
	ft_lstadd(root, ft_lstnewlink(rdir, sizeof(t_dir)));
}
