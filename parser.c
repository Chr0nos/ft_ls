/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:34:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/22 13:41:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	add_rest_parametersastargets(int ac, char **av, t_list **targets,
		int p)
{
	while (p < ac)
		ft_lstadd(targets, ft_lstnewlink(av[p++], 0));
}

int			parser(int ac, char **av, t_list **targets)
{
	const char	*strmatch[9] = { "-*R*", "-*l*", "-*a*", "-*r*", "-*f*",
		"-*t*", "-*S*", "-*h*", "-*A*" };
	const int	flagstab[9] = { RECURSIVE, LONG, HIDENS, REVERSESORT, NOSORT,
		MTIMESORT, SIZESORT, HUMAN, HIDENS | NODOTANDDOTDOT };
	int			mappos;
	int			flags;
	int			p;

	flags = NONE;
	p = 1;
	while ((p < ac) && (ft_strcmp(av[p], "--")))
	{
		if (av[p][0] == '-')
		{
			mappos = 9;
			while (mappos--)
				if (ft_match(av[p], strmatch[mappos]))
					flags |= flagstab[mappos];
		}
		else
			ft_lstadd(targets, ft_lstnewlink(av[p], 0));
		p++;
	}
	add_rest_parametersastargets(ac, av, targets, p + 1);
	return (flags);
}
