/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 14:48:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

enum e_flags
{
	NONE = 0,
	RECURSIVE = 1,
	HIDENS = 2,
	LONG = 4
};

typedef struct	s_file
{
	struct dirent	*de;
	char			*name;
	char			*fullpath;
	struct stat		stats;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	size_t			count;
	t_list			*content;
}					t_dir;

int					sorter(t_list *a, t_list *b);

#endif
