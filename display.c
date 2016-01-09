/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/09 15:43:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static char	get_type(t_file *file)
{
	if (file->de->d_type == DT_BLK)
		return ('b');
	if (file->de->d_type == DT_DIR)
		return ('d');
	if (file->de->d_type == DT_CHR)
		return ('c');
	if (file->de->d_type == DT_FIFO)
		return ('f');
	if (file->de->d_type == DT_LNK)
		return ('l');
	if (file->de->d_type == DT_REG)
		return ('-');
	if (file->de->d_type == DT_SOCK)
		return ('s');
	return ('u');
}

static void	display_posix(t_file *file)
{
	char			buffer[11];
	unsigned char	p;

	p = 0;
	buffer[p++] = get_type(file);
	buffer[p++] = ' ';
	buffer[p] = '\0';
	ft_putstr(buffer);
}

void		display(t_list *lst)
{
	const size_t	dirs = ft_lstsize(lst);
	t_dir			*dir;
	t_file			*file;
	t_list			*dl;

	while (lst)
	{
		dir = (t_dir*)lst->content;
		if (dirs > 1)
		{
			ft_putstr(dir->path);
			ft_putstr(":\n");
		}
		else if (dir->flags & LONG)
			ft_printf("Total: %d\n", (int)dir->count);
		dl = dir->content;
		while (dl)
		{
			file = (t_file*)dl->content;
			if (dir->flags & LONG)
				display_posix(file);
			ft_putendl(file->name);
			dl = dl->next;
		}
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
