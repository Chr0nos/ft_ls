/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeloader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:29:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 20:37:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <string.h>
#include <time.h>

void	timeloader(t_file *file, char *buffer)
{
	const time_t	*clock = &file->stats.st_mtime;
	const char		*strtime = ctime(clock);
	char			year[12];
	const size_t	timelen = ft_strlen(strtime);
	const time_t	localtime = time(NULL);

	ft_strncpy(buffer, strtime + 4, timelen - 12);
	if (ft_abs((int)(localtime - *clock)) > 15778800)
	{
		ft_strncpy(year, strtime + timelen - 5, 5);
		ft_stralign_right(year, 6);
		ft_strcpy(buffer + ft_strlen(buffer) - 6, year);
	}
}
