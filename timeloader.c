#include "ft_ls.h"
#include "libft.h"

void	timeloader(const char *time, char *buffer)
{
	int		timelen;

	timelen = (int)ft_strlen(time);
	ft_strncpy(buffer, time + 4, (size_t)(timelen - 12));
	if (ft_strcmp(time + timelen - 5, "2016\n") == 0)
	{
		ft_strncat(buffer, time + timelen - 5, 5);
		buffer[ft_strlen(buffer) - 6] = ' ';
	}
}
