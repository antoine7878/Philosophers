/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:59:23 by ale-tell          #+#    #+#             */
/*   Updated: 2024/12/10 17:59:25 by ale-tell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

static int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char const *nptr)
{
	int	ret;

	ret = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		return (-2);
	if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		ret = ret * 10 + (*nptr - '0');
		if (ret < 0)
			return (-2);
		nptr++;
	}
	if (*nptr)
		return (-2);
	return (ret);
}
