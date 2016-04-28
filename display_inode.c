/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_inode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:06:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:06:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include "sys/stat.h"

int		display_inode(const t_file *file)
{
	ft_putnbr((int)file->stats.st_ino);
	ft_putchar(' ');
	return (0);
}
