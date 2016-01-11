/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:49:35 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/11 21:31:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

static int		makepathinfo(const char *dir, t_filepath *info)
{
	const int		slash_pos = ft_strchrrpos(dir, '/');
	struct stat		st;

	stat(dir, &st);
	if (st.st_mode & S_IFDIR)
	{
		info->path = ft_strdup(dir);
		info->filemask = ft_strdup("*");
	}
	else if (st.st_mode & (S_IFIFO | S_IFREG | S_IFCHR | S_IFMT | S_IFBLK |
				S_IFLNK | S_IFSOCK))
	{
		if (slash_pos > 0)
		{
			info->path = ft_strndup(dir, (unsigned int)slash_pos);
			info->filemask = ft_strdup(dir + (unsigned int)slash_pos + 1);
		}
		else
		{
			info->path = ft_strdup(".");
			info->filemask = ft_strdup(dir);
		}
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No fuck file or directory\n", 2);
		return (0);
	}
	return (1);
}

static t_dir	*get_newrdir(char *path, int flags)
{
	t_dir	*rdir;

	if (!(rdir = malloc(sizeof(t_dir))))
		return (NULL);
	rdir->path = ft_strdup(path);
	rdir->content = NULL;
	rdir->flags = flags;
	rdir->size = 0;
	rdir->count = 0;
	if (makepathinfo(path, &rdir->pathinfo) == 0)
	{
		delpathinfo(&rdir->pathinfo);
		free(rdir);
		return (NULL);
	}
	return (rdir);
}

t_dir			*get_rdir(t_list **root, char *path, int flags)
{
	t_list	*lst;
	t_dir	*rdir;

	lst = *root;
	while (lst)
	{
		if (ft_strcmp(((t_dir*)lst->content)->path, path) == 0)
			return ((t_dir*)lst->content);
		lst = lst->next;
	}
	rdir = get_newrdir(path, flags);
	if (!rdir)
		return (NULL);
	ft_lstadd(root, ft_lstnewlink(rdir, sizeof(t_dir)));
	return (rdir);
}
