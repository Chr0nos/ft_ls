/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 13:55:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/22 14:39:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>

static char		get_type(t_file *file)
{
	const mode_t	mode = file->stats.st_mode;

	if (S_ISLNK(mode))
		return ('l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISFIFO(mode))
		return ('f');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISREG(mode))
		return ('-');
	return ('u');
}

int				add_posix(t_file *file, char *buffer)
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
		if ((blk == 2) && (perms & S_ISVTX))
			buffer[p + 2] = (perms & S_IXOTH) ? 't' : 'T';
		else
			buffer[p + 2] = (perms & S_IXOTH) ? 'x' : '-';
		p += 3;
		blk++;
	}
	buffer[p++] = ' ';
	buffer[p] = '\0';
	return (p);
}
