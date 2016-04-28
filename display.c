/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:11:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void			display_dir(t_dir *rdir, int n)
{
	t_list	*lst;
	char	buffer[2048];

	lst = rdir->content;
	if (n > 0)
		ft_printf("%s:\n", rdir->pathinfo.path);
	if ((rdir->flags & LONG) && (n >= 0) && (lst))
		ft_printf("total %d\n", (int)rdir->blocs);
	while (lst)
	{
		display_file((t_file*)lst->content, rdir, (char*)buffer);
		lst = lst->next;
	}
}

void			display(t_list *lst)
{
	t_dir			*dir;
	int				n;

	n = 0;
	while (lst)
	{
		dir = (t_dir*)lst->content;
		display_dir(dir, n++);
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
