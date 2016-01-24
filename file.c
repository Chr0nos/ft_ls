#include "ft_ls.h"
#include "libft.h"

void	file_init(t_file *file)
{
	ft_memset(file->size_str, 0, 48);
	ft_memset(file->user, 0, 256);
	ft_memset(file->group, 0, 256);
	ft_memset(file->links, 0, 8);
	ft_memset(file->time, 0, 64);
}
