/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/07 23:05:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <string.h>
#include <time.h>

typedef struct	s_file
{
	char		*name;
	size_t		namelen;
	char		*path;
	size_t		size;
	time_t		ctime;
	time_t		mtime;
	time_t		atime;
}				t_file;

#endif
