/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/10 14:56:38 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <string.h>
# include <time.h>
# include <sys/stat.h>

enum				e_flags
{
	NONE = 0,
	RECURSIVE = 1,
	HIDENS = 2,
	LONG = 4,
	REVERSESORT = 8,
	MTIMESORT = 16,
	ATIMESORT = 32,
	CTIMESORT = 64,
	SIZESORT = 128,
	NOSORT = 256,
	HUMAN = 512
};

typedef struct		s_file
{
	struct dirent	*de;
	char			*name;
	char			*fullpath;
	struct stat		stats;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	size_t			count;
	size_t			size;
	t_list			*content;
	int				flags;
	char			padding[4];
}					t_dir;

typedef struct		s_lsd
{
	t_dir			*rdir;
	char			*match;
	struct dirent	*ent;
	t_list			**root;
}					t_lsd;

void				display(t_list *lst);
void				ls_dir(char *dir, int flags, char *match, t_list **root);
int					sorter(t_list *a, t_list *b);
int					rsort(t_list *a, t_list *b);
int					csort(t_list *a, t_list *b);
int					rcsort(t_list *a, t_list *b);
int					msort(t_list *a, t_list *b);
int					rmsort(t_list *a, t_list *b);
int					sizesort(t_list *a, t_list *b);
int					rsizesort(t_list *a, t_list *b);

#endif
