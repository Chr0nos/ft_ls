/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 21:14:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/02/07 21:14:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

char		*getpath(char *dir, char *file)
{
	const char	*tab[3] = { dir, file, NULL };
	char		*fp;

	fp = ft_strunsplit(tab, '/');
	return (fp);
}
