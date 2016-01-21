/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/01/21 15:52:19 by snicolet         ###   ########.fr       */
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
	HUMAN = 512,
	NODOTANDDOTDOT = 1024
};

enum				e_lens
{
	ULEN = 0,
	GLEN = 1,
	SLEN = 2,
	LLEN = 3
};

typedef struct		s_filepath
{
	char			*path;
	char			*file;
}					t_filepath;

typedef struct		s_file
{
	char			*name;
	char			*fullpath;
	char			size_str[48];
	char			user[256];
	char			group[256];
	char			links[8];
	char			time[64];
	struct stat		stats;
}					t_file;

typedef struct		s_max
{
	unsigned int	filesize;
	unsigned int	userlen;
	unsigned int	grouplen;
	unsigned int	linkslen;
	unsigned int	padding;
}					t_max;

typedef struct		s_dir
{
	int				flags;
	t_max			max;
	char			*path;
	t_list			*content;
	size_t			count;
	off_t			size;
	off_t			blocs;
	struct stat		stats;
	t_filepath		pathinfo;
}					t_dir;

void				aligner(char *buffer, unsigned int len);
void				display(t_list *lst);
void				ls_dir(t_list **root, t_dir *rdir);
int					sorter(t_list *a, t_list *b);
int					rsort(t_list *a, t_list *b);
int					csort(t_list *a, t_list *b);
int					rcsort(t_list *a, t_list *b);
int					msort(t_list *a, t_list *b);
int					rmsort(t_list *a, t_list *b);
int					sizesort(t_list *a, t_list *b);
int					rsizesort(t_list *a, t_list *b);
int					parser(int ac, char **av, t_list **targets);
void				*getsorter(int f);
t_dir				*search_rdir(t_list *lst, char *path);
t_dir				*get_rdir(t_list **root, char *path, int flags);
unsigned int		sizetobuff(off_t nb, char *buffer);

#endif
