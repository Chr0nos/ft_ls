/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/08 01:33:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <string.h>
#include <time.h>

typedef struct	s_file
{
	struct dirent	*de;
	char			*name;
	time_t			ctime;
	time_t			mtime;
	time_t			atime;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	t_list			*content;
}					t_dir;

#endif
