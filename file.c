/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:51:32 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 14:51:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	file_init(t_file *file)
{
	ft_memset(file->size_str, 0, 48);
	ft_memset(file->user, 0, 256);
	ft_memset(file->group, 0, 256);
	ft_memset(file->links, 0, 8);
	ft_memset(file->time, 0, 64);
}
