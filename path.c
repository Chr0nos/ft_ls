/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 17:30:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/19 22:35:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

int		delpathinfo(t_filepath *file)
{
	if (file)
	{
		if (file->path)
			free(file->path);
		if (file->filemask)
			free(file->filemask);
	}
	return (1);
}
