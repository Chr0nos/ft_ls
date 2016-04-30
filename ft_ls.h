/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 22:52:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/04/30 23:04:11 by snicolet         ###   ########.fr       */
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
	HIDENS = 0x1 << 1,
	LONG = 0x1 << 2,
	REVERSESORT = 0x1 << 3,
	TTIMESORT = 0x1 << 4,
	ATIMESORT = 0x1 << 5,
	CTIMESORT = 0x1 << 6,
	SIZESORT = 0x1 << 7,
	NOSORT = 0x1 << 8,
	HUMAN = 0x1 << 9,
	NODOTANDDOTDOT = 0x1 << 10,
	INODES = 0x1 << 11,
	LTIMESORT = 0x1 << 12,
	UTIMESORT = 0x1 << 13,
	SLASH = 0x1 << 14,
	ONESHOOT = 0x1 << 15,
	FULLTIMESHOW = 0x1 << 16
};

enum				e_lens
{
	ULEN = 0,
	GLEN = 1,
	SLEN = 2,
	LLEN = 3
};

enum				e_stype
{
	ERROR = 1,
	FILEX = 2,
	DIRECTORY = 4
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

char				*getpath(char *dir, char *file);
void				display_dir(t_dir *rdir, int n, int total_dirs,
	int total_files);
void				timeloader(t_file *file, char *buffer);
void				file_init(t_file *file);
void				clean_emptydirs(t_list **root);
void				*clean_file(t_file *file);
void				ft_lstatomisator(void *x, size_t size);
void				rdir_clean(t_dir *rdir);
void				aligner(char *buffer, unsigned int len);
void				ls_dir(t_dir *rdir, int n, int total_dirs, int total_files);
int					add_posix(t_file *file, char *buffer);
int					sorter(t_list *a, t_list *b);
int					usort(t_list *a, t_list *b);
int					usortr(t_list *a, t_list *b);
int					rsort(t_list *a, t_list *b);
int					csort(t_list *a, t_list *b);
int					rcsort(t_list *a, t_list *b);
int					rmsort(t_list *a, t_list *b);
int					ltsort(t_list *a, t_list *b);
int					ltsortr(t_list *a, t_list *b);
int					sizesort(t_list *a, t_list *b);
int					rsizesort(t_list *a, t_list *b);
int					params_sort(t_list *a, t_list *b);
int					parser(int ac, char **av, t_list **targets);
int					display_inode(const t_file *file);
void				*getsorter(int f);
t_dir				*get_newrdir(char *path, int flags);
unsigned int		sizetobuff(off_t nb, char *buffer);
void				display_file(t_file *file, t_dir *dir, char *buffer);
char				*nofile(const char *filepath, char *buffer);
int					get_type(const char *str);
void				putslash_ifneeded(int flags, t_file *file);
int					strpresent(const char *str, const char c);

#endif
