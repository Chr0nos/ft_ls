/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeloader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:29:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 20:34:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <string.h>
#include <time.h>

static void	monthtostr(char *buff, int m)
{
	const char	*months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
		"Aug", "Sep", "Oct", "Nov", "Dec" };

	ft_strcpy(buff, months[m]);
}

void	timeloader(t_file *file, char *buffer)
{
	const time_t	*clock = &file->stats.st_mtime;
	char			*strtime;
	char			year[12];
	size_t			timelen;
	const time_t	localtime = time(NULL);

	(void)monthtostr;
	strtime = ctime(clock);
	timelen = ft_strlen(strtime);
	ft_strncpy(buffer, strtime + 4, timelen - 12);
	if (ft_abs((int)(localtime - *clock)) > 15778800)
	{
		ft_strncpy(year, strtime + timelen - 5, 5);
		ft_stralign_right(year, 6);
		ft_strcpy(buffer + ft_strlen(buffer) - 6, year);
	}
}
