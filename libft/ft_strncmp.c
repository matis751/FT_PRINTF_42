/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:06:08 by mel-oual          #+#    #+#             */
/*   Updated: 2019/02/16 00:17:24 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char*)s1;
	s4 = (unsigned char*)s2;
	while ((s3[i] || s4[i]) != 0 && i < n)
	{
		if (s3[i] == s4[i])
		{
			i++;
		}
		else
			return (s3[i] - s4[i]);
	}
	return (0);
}
