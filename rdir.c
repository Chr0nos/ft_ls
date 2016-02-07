/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:49:35 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/08 00:25:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

static int		showerror(char *path)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

t_dir			*get_newrdir(char *path, int flags)
{
	t_dir			*rdir;

	if (!(rdir = malloc(sizeof(t_dir))))
		return (NULL);
	rdir->path = ft_strdup(path);
	rdir->content = NULL;
	rdir->flags = flags;
	rdir->size = 0;
	rdir->blocs = 0;
	rdir->count = 0;
	rdir->pathinfo.path = ft_strdup(path);
	rdir->pathinfo.file = NULL;
	if ((stat(path, &rdir->stats) < 0) && (showerror(path)))
	{
		rdir_clean(rdir);
		return (NULL);
	}
	rdir->max.filesize = (flags & HUMAN) ? 5 : 0;
	rdir->max.userlen = 0;
	rdir->max.grouplen = 0;
	rdir->max.linkslen = 0;
	return (rdir);
}

void			rdir_clean(t_dir *rdir)
{
	free(rdir->path);
	free(rdir->pathinfo.path);
	free(rdir);
}
