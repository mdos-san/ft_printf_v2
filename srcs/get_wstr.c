#include "libftprintf.h"

char	*get_wstr(int *istr)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (istr == NULL)
		return (ft_strdup("(null)"));
	while (istr[i])
	{
		if (ret)
			ret = ft_strjoin(ret, get_wchar(istr[i]));
		else
			ret = get_wchar(istr[i]);
		++i;
	}
	return (ret);
}
