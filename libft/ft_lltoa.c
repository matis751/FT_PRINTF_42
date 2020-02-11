/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:10:52 by mel-oual          #+#    #+#             */
/*   Updated: 2019/11/09 11:52:19 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include <stdio.h>

static	int	num_len(long long n)
{
	int		len;

	len = 1;
	while ((n /= 10))
		len++;
	return (len);
}

char		*ft_lltoa(long long n)
{
	char	*ret;
	int		overflow;
	int		len;
	int		neg;

	overflow = (n == LONG_MIN);
	if ((neg = n < 0))
		n = -(n + overflow);
	len = num_len(n);
	if ((ret = ft_strnew(len + neg)))
	{
		if (neg)
			ret[0] = '-';
		if (overflow)
		{
			ret[neg + --len] = '8';
			n /= 10;
		}
		while (len--)
		{
			ret[neg + len] = n % 10 + '0';
			n /= 10;
		}
	}
	return (ret);
}
