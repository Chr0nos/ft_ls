/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 13:55:42 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/29 18:23:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>

static char		get_file_type(t_file *file)
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

static void		fix_suid(char *buffer, int perms)
{
	if (perms & S_ISUID)
		buffer[3] = (perms & S_IXUSR) ? 's' : 'S';
	if (perms & S_ISGID)
		buffer[7] = (perms & S_IXGRP) ? 's' : 'S';
}

int				add_posix(t_file *file, char *buffer)
{
	unsigned char	p;
	int				blk;
	int				perms;

	p = 0;
	blk = 0;
	buffer[p++] = get_file_type(file);
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
	fix_suid(buffer, file->stats.st_mode);
	buffer[p] = '\0';
	return (p);
}
