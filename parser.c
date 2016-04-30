/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 15:34:54 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 23:04:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#define NBFLAGS 15

static void	add_rest_parametersastargets(int ac, char **av, t_list **targets,
		int p)
{
	while (p < ac)
		ft_lstpush_sort(targets, ft_lstnewlink(av[p++], 0), &params_sort);
}

static void	parser_setflag(int flag, int *flags)
{
	if (flag == ONESHOOT)
		*flags = (*flags & ~LONG);
	else if (flag == LONG)
		*flags = (*flags & ~ONESHOOT);
	*flags |= flag;
}

/*
** this function evaluate each separated item argument starting with -
** ex: -alSh
** called by: parser()
** returns:
** 0 in case of success
** < 0 in case of error
*/

static int	parser_eval(const char *av, const char *strmap, const int *flagstab,
	int *flags)
{
	int		p;
	int		idx;

	p = 0;
	while (av[p] != '\0')
	{
		idx = strpresent(strmap, av[p]);
		if (idx >= 0)
			parser_setflag(flagstab[idx], flags);
		else
		{
			ft_putstr("ls: illegal option -- ");
			ft_putchar(av[p]);
			ft_putstr("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			return (-1);
		}
		p++;
	}
	return (0);
}

static void	parser_populate_flags(int *tab, int *p, int *flags)
{
	const int	flagstab[NBFLAGS] = { RECURSIVE, LONG, HIDENS, REVERSESORT, \
	TTIMESORT, SIZESORT, HUMAN, HIDENS | NODOTANDDOTDOT, INODES, UTIMESORT, \
	LTIMESORT, HIDENS | NOSORT, SLASH, ONESHOOT, FULLTIMESHOW };

	ft_memcpy(tab, flagstab, sizeof(int) * NBFLAGS);
	*flags = NONE;
	*p = 1;
}

/*
** called by : main
*/

int			parser(int ac, char **av, t_list **targets)
{
	const char	*strmap = "RlartShAiucfp1T";
	int			flagstab[NBFLAGS];
	int			flags;
	int			p;

	parser_populate_flags(flagstab, &p, &flags);
	while ((p < ac) && (ft_strcmp(av[p], "--")))
	{
		if (av[p][0] == '-')
		{
			if (parser_eval(&av[p][1], strmap, flagstab, &flags) < 0)
				return (-1);
		}
		else
			ft_lstpush_sort(targets, ft_lstnewlink(av[p], 0), &params_sort);
		p++;
	}
	add_rest_parametersastargets(ac, av, targets, p + 1);
	return (flags);
}
