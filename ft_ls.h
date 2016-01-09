/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/09 13:52:59 by snicolet         ###   ########.fr       */
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
	LONG = 4
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

#endif
