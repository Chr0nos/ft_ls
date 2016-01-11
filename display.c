/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:38:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/11 23:34:17 by snicolet         ###   ########.fr       */
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

static int	display_posix(t_file *file, char *buffer)
{
	unsigned char	p;
	int				blk;
	int				perms;

	p = 0;
	blk = 0;
	buffer[p++] = get_type(file);
	while (blk < 3)
	{
		perms = (int)file->stats.st_mode >> (2 - blk) * 3;
		buffer[p] = (perms & S_IROTH) ? 'r' : '-';
		buffer[p + 1] = (perms & S_IWOTH) ? 'w' : '-';
		buffer[p + 2] = (perms & S_IXOTH) ? 'x' : '-';
		p += 3;
		blk++;
	}
	buffer[p++] = ' ';
	buffer[p] = '\0';
	return (p);
}

static void	display_file(t_file *file, t_dir *dir, char *buffer)
{
	int	p;

	if (dir->flags & LONG)
	{
		p = display_posix(file, buffer);
		p += ft_itobuff(buffer + p, (int)file->stats.st_nlink, 10,
				"0123456789");
		buffer[p++] = ' ';
		buffer[p] = '\0';
		ft_putstr(buffer);
	}
	ft_putendl(file->name);
}

void		display(t_list *lst)
{
	const size_t	dirs = ft_lstsize(lst);
	t_dir			*dir;
	t_file			*file;
	t_list			*dl;
	char			buffer[20];

	while (lst)
	{
		dir = (t_dir*)lst->content;
		if (dirs > 1)
			ft_printf("%s:\n", dir->pathinfo.path);
		if (dir->flags & LONG)
			ft_printf("Total: %d\n", (int)dir->size);
		dl = dir->content;
		while (dl)
		{
			file = (t_file*)dl->content;
			display_file(file, dir, (char*)buffer);
			dl = dl->next;
		}
		lst = lst->next;
		if (lst)
			ft_putchar('\n');
	}
}
