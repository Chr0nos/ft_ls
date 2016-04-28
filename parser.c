/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:34:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/28 19:03:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	add_rest_parametersastargets(int ac, char **av, t_list **targets,
		int p)
{
	while (p < ac)
		ft_lstpush_sort(targets, ft_lstnewlink(av[p++], 0), &ft_lststrcmp);
}

static void	parser_populate_flags(int *tab)
{
	const int	flagstab[12] = { RECURSIVE, LONG, HIDENS, REVERSESORT, NOSORT, \
	TTIMESORT, SIZESORT, HUMAN, HIDENS | NODOTANDDOTDOT, INODES, UTIMESORT, \
 	LTIMESORT };

	ft_memcpy(tab, flagstab, sizeof(int) * 12);
}

int			parser(int ac, char **av, t_list **targets)
{
	const char	*strmatch[12] = { "-*R*", "-*l*", "-*a*", "-*r*", "-*f*",
		"-*t*", "-*S*", "-*h*", "-*A*", "-*i*", "-*u*", "-*c*" };
	int			flagstab[12];
	int			mappos;
	int			flags;
	int			p;

	parser_populate_flags(flagstab);
	flags = NONE;
	p = 1;
	while ((p < ac) && (ft_strcmp(av[p], "--")))
	{
		if (av[p][0] == '-')
		{
			mappos = 12;
			while (mappos--)
				if (ft_match(av[p], strmatch[mappos]))
					flags |= flagstab[mappos];
		}
		else
			ft_lstpush_sort(targets, ft_lstnewlink(av[p], 0), &ft_lststrcmp);
		p++;
	}
	add_rest_parametersastargets(ac, av, targets, p + 1);
	return (flags);
}
