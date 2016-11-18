#include "libftprintf.h"

char	*ft_itoa_base(int nbr, unsigned int base)
{
	int		i;
	int		mod;
	char	buf[1024];
	int		neg;

	i = 0;
	ft_bzero(buf, 1024);
	if (nbr == 0)
		return (ft_strdup("0"));
	neg = (nbr < 0) ? -1 : 1;
	while (nbr != 0)
	{
		mod = nbr % base;
		if (mod <= 9)
			buf[1022 - i] = mod * neg + 48;
		else
		{
			mod -= 10;
			buf[1022 - i] = mod * neg + 97;
		}
		nbr /= base;
		++i;
	}
	return (ft_strdup(buf + 1022 - i + 1));
}

char	*ft_uitoa_base(unsigned int nbr, unsigned int base)
{
	int		i;
	int		mod;
	char	buf[1024];

	i = 0;
	ft_bzero(buf, 1024);
	if (nbr == 0)
		return (ft_strdup("0"));
	while (nbr != 0)
	{
		mod = nbr % base;
		if (mod <= 9)
			buf[1022 - i] = mod + 48;
		else
		{
			mod -= 10;
			buf[1022 - i] = mod + 97;
		}
		nbr /= base;
		++i;
	}
	return (ft_strdup(buf + 1022 - i + 1));
}
