/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:49:35 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/20 16:04:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

static int		showerror(char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No fuck file or directory\n", 2);
	return (1);
}

static t_dir	*get_newrdir(char *path, int flags)
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
	rdir->size_str = NULL;
	rdir->pathinfo.path = path;
	if ((stat(path, &rdir->stats) < 0) && (showerror(path)))
	{
		free(rdir);
		return (NULL);
	}
	return (rdir);
}

t_dir			*get_rdir(t_list **root, char *path, int flags)
{
	t_list		*lst;
	t_dir		*rdir;
	
	lst = *root;
	while (lst)
	{
		rdir = (t_dir*)(lst->content);
		if (ft_strcmp(rdir->pathinfo.path, path) == 0)
			return (rdir);
		lst = lst->next;
	}
	rdir = get_newrdir(path, flags);
	if (!rdir)
		return (NULL);
	ft_lstpush_back(root, ft_lstnewlink(rdir, sizeof(t_dir)));
	return (rdir);
}
