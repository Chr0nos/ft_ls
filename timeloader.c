/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeloader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:29:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/08 00:15:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <string.h>
#include <time.h>

static size_t	strrchrpos(const char *str, int c)
{
	size_t	n;

	n = ft_strlen(str);
	while ((n) && (str[n] == c))
		n--;
	while ((str[n] != c) && (n--))
		;
	return (n + 1);
}

static size_t	strseek(const char *str)
{
	size_t	p;

	p = 4;
	while ((str[p]) && (str[p] == ' '))
		p++;
	while ((str[p] != ' ') && (str[p]))
		p++;
	return (p - 1);
}

void	timeloader(t_file *file, char *buffer)
{
	const char		*strtime = ctime(&file->stats.st_mtime);
	char			year[12];
	const size_t	timelen = ft_strlen(strtime);
	ssize_t			timediff;
	size_t			epos;

	ft_strncpy(buffer, strtime + 4, timelen - 12);
	timediff = time(NULL) - file->stats.st_mtime;
	if ((timediff > 15778800) || (timediff < -15778800))
	{
		ft_strcpy(year, strtime + strrchrpos(strtime, ' '));
		ft_stralign_right(year, 6 + ((ft_strlen(year) == 6) ? 1 : 0));
		epos = strseek(strtime);
		buffer[epos] = ' ';
		ft_strcpy(buffer + epos + 1 , year);
	}
}
