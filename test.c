#include <string.h>
#include "./libft/libft.h"

int		main(void)
{
	unsigned char reg[5] = {255, 2, 127, 0, 25};
	unsigned char new[5];
	unsigned char new_2[5];

	memcpy(new, reg, 5);
	int i = -1;
	while (++i < 5)
		ft_printf("%u ", new[i]);
	ft_printf("\n");


	ft_memcpy(new_2, reg, 5);
	i = -1;
	while (++i < 5)
		ft_printf("%u ", new_2[i]);
	ft_printf("\n");
}