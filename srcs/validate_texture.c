#include "../incl/cub3D.h"

int	validate_texture(char *content)
{
	int	len;

	if (content)
	{
		len = ft_strlen(content);
		if (len < 6 || !ft_strnstr(&content[len - 5], ".png\n", 5)
			|| ft_strnstr(&content[len - 6], "/.png\n", 6))
			return (err(TEXT_EXT), FAIL);
	}
	return (SUCCESS);
}
