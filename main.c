/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:56:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/07 23:09:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <dirent.h>

int		ls_dir(char *dir)
{
	t_file			file;
	DIR				*d;
	struct dirent	*ent;

	if (!(d = opendir(dir)))
		return (0);
	while ((ent = readdir(d)))
	{
		file.namelen = ent->d_namlen;
		file.name = ent->d_name;
		ft_putendl(file.name);
	}
	return (1);
}

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		ls_dir(".");
	}
	(void)av;
	return (0);
}
