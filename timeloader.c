#include "ft_ls.h"
#include "libft.h"

void	timeloader(const char *time, char *buffer)
{
	int		space;
	int		len;
	int		timelen;

	space = 0;
	while ((*time) && (*time != ' ') && (space++ < 2))
		time++;
	time += 2;
	timelen = (int)ft_strlen(time);
	ft_memcpy(buffer, time + 4, 3);
	ft_memcpy(buffer + 3, time, 4);
	ft_strcpy(buffer + 7, time + 7);
	len = (int)ft_strlen(buffer);
	if (ft_strcmp(buffer + len - 5, "2016\n") == 0)
		buffer[len - 8] = '\0';
	else
	{
		//todo: gestion de la suppression des secondes sans l annee
	}
}
