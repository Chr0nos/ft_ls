/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 21:14:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/29 18:16:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

char		*getpath(char *dir, char *file)
{
	return (ft_strunsplit((const char*[3]){ dir, file, NULL }, '/'));
}

char		*nofile(const char *filepath, char *buffer)
{
	int		start;
	int		len;

	start = ft_strchrrpos(filepath, '/');
	if (start < 0)
		ft_strcpy(buffer, ".");
	else
	{
		len = (int)ft_strlen(filepath);
		ft_memcpy(buffer, &filepath[start], (unsigned int)(len - start + 1));
	}
	return (buffer);
}
