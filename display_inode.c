#include "ft_ls.h"
#include "libft.h"
#include "sys/stat.h"

int		display_inode(const t_file *file)
{
	ft_putnbr((int)file->stats.st_ino);
	ft_putchar(' ');
	return (0);
}
