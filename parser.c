/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:34:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 15:35:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		parser(int ac, char **av, t_list **targets)
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
	p++;
	while (p < ac)
		ft_lstadd(targets, ft_lstnewlink(av[p++], 0));
	return (flags);
}
