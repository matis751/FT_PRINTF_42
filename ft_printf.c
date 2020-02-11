/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:30:50 by mel-oual          #+#    #+#             */
/*   Updated: 2019/10/31 16:28:39 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		has(char *field, char *str)
{
	while (*str)
	{
		if (!ft_strchr(field, *str))/*recherche un c dans une string*/
			return (0);/*si ne trouve rien renvoie 0*/
		str++;/*si trouve la chaine r*/
	}
	return (1);
}

int		convert(const char **fmt, va_list ap)
{
	int					i;
	t_conv				conv; /*list de conversiion*/
	const t_able		table[] = {	{"c", &conv_char}, {"s", &conv_str},
								{"p", &conv_ptr}, {"diD", &conv_int},
								{"ouxOUX", &conv_uint}, {"%", &conv_mod},
								{"fF", &conv_float}, {NULL, NULL}}; /*table 2 elemements keys & function*/

	ft_bzero(&conv, sizeof(t_conv));
	(*fmt)++;
	parse_fmt(&conv, fmt); /*cherche les flags et avance jusqu'a la lettre*/
	while (**fmt)
	{
		conv.type = *(*fmt)++;
		i = -1;
		while (table[++i].func)
			if (ft_strchr(table[i].key, conv.type))
				return (table[i].func(&conv, ap));
	}
	return (0);
}

int		ft_read_sec(const char **fmt, va_list ap)
{
	int				index;
	int				len_printed;

	len_printed = 0;
	index = -1;
	while ((*fmt)[++index]) /*cherche %*/
		if ((*fmt)[index] == '%')
			break ;
	len_printed = write(1, *fmt, index); /*ecrit jusque %*/
	*fmt += index; /*avance jusque %*/
	if (**fmt == '%')
		len_printed += convert(fmt, ap);
	return (len_printed);
}

int		ft_printf(const char *fmt, ...)
{
	va_list			ap;
	int				len;

	va_start(ap, fmt); /*Initialise Va_list*/
	len = 0;
	while (*fmt)
		len += ft_read_sec(&fmt, ap);
	va_end(ap);
	return (len);
}
