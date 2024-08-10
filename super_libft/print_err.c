/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:27:44 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/10 16:16:28 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_err(int count, ...)
{
	int		i;
	char	*str;
	va_list	args;

	i = 0;
	va_start(args, count);
	ft_putstr_fd(RED, 2);
	while (i < count)
	{
		str = va_arg(args, char *);
		ft_putstr_fd(str, 2);
		i++;
	}
	ft_putstr_fd(RESET, 2);
	va_end(args);
	exit (1);
}
