#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

int		show_error(t_dir *rdir)
{
	char	error[1024];

	ft_strcpy(error, "ft_ls: ");
	ft_strcat(error, rdir->pathinfo.path);
	ft_strcat(error, ": ");
	ft_strcat(error, strerror(rdir->err));
	ft_putendl_fd(error, 2);
	return (0);
}
