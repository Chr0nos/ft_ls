/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:34:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/03 13:31:34 by snicolet         ###   ########.fr       */
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

int			parser(int ac, char **av, t_list **targets)
{
	const char	*strmatch[11] = { "-*R*", "-*l*", "-*a*", "-*r*", "-*f*",
		"-*t*", "-*S*", "-*h*", "-*A*", "-*i*", "-*u*" };
	const int	flagstab[11] = { RECURSIVE, LONG, HIDENS, REVERSESORT, NOSORT,
		MTIMESORT, SIZESORT, HUMAN, HIDENS | NODOTANDDOTDOT, INODES, LTIMESORT };
	int			mappos;
	int			flags;
	int			p;

	flags = NONE;
	p = 1;
	while ((p < ac) && (ft_strcmp(av[p], "--")))
	{
		if (av[p][0] == '-')
		{
			mappos = 11;
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
/*
int			parser(int ac, char **av, t_list **targets)
{
	const char	*args = "RlarftShA";
	const int	flagstab[9] = { RECURSIVE, LONG, HIDENS, REVERSESORT, NOSORT,
		MTIMESORT, SIZESORT, HUMAN, HIDENS | NODOTANDDOTDOT };
	int			mappos;
	int			flags;
	int			p;

	p = 0;
	while (p < ac)
	{
		if ((av[p][0] == '-') && (av[p][1]))
		{
			mappos = 0;
		}
		p++;
	}
}
*/
