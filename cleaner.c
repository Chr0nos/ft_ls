#include "libft.h"
#include "ft_ls.h"
#include <stdlib.h>

void	clean_file(t_file *file)
{
	free(file->fullpath);
	free(file->name);
	free(file);
}

void	ft_lstatomisator(void *x, size_t size)
{
	t_list	*lst;
	t_file	*file;
	t_list	*next;
	t_dir	*rdir;

	if (!x)
		return ;
	rdir = (t_dir*)x;
	lst = rdir->content;
	free(rdir->path);
	free(rdir->pathinfo.path);
	while (lst)
	{
		file = (t_file*)lst->content;
		clean_file(file);
		next = lst->next;
		free(lst);
		lst = next;
	}
	free(rdir);
	(void)size;
}
