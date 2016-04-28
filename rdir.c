/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:49:35 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:14:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

static int			showerror(char *path)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

inline static void	rdir_init(t_dir *rdir, const int flags, char *path)
{
	rdir->pathinfo.path = ft_strdup(path);
	rdir->pathinfo.file = NULL;
	rdir->max.filesize = (flags & HUMAN) ? 5 : 0;
	rdir->max.userlen = 0;
	rdir->max.grouplen = 0;
	rdir->max.linkslen = 0;
	rdir->path = ft_strdup(path);
	rdir->content = NULL;
	rdir->flags = flags;
	rdir->size = 0;
	rdir->blocs = 0;
	rdir->count = 0;
}

t_dir				*get_newrdir(char *path, int flags)
{
	t_dir			*rdir;

	if (!(rdir = malloc(sizeof(t_dir))))
		return (NULL);
	rdir_init(rdir, flags, path);
	if ((stat(path, &rdir->stats) < 0) && (showerror(path)))
	{
		rdir_clean(rdir);
		return (NULL);
	}
	return (rdir);
}

void				rdir_clean(t_dir *rdir)
{
	free(rdir->path);
	free(rdir->pathinfo.path);
	free(rdir);
}
