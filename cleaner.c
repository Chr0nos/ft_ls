/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 12:31:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/22 13:44:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <string.h>
#include <stdlib.h>

void	*clean_file(t_file *file)
{
	free(file->fullpath);
	free(file->name);
	free(file);
	return (NULL);
}

void	ft_lstatomisator(void *x, size_t size)
{
	t_list	*lst;
	t_file	*file;
	t_list	*next;
	t_dir	*rdir;

	if (!x)
		return ;
	rdir = (t_dir*)x;
	lst = rdir->content;
	free(rdir->path);
	free(rdir->pathinfo.path);
	while (lst)
	{
		file = (t_file*)lst->content;
		clean_file(file);
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(rdir);
	(void)size;
}
