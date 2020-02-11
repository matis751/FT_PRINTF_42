/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cov_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:27:37 by mel-oual          #+#    #+#             */
/*   Updated: 2019/11/09 12:50:14 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	arg(t_conv *conv, va_list ap)
{
	if (conv->type == 'D')
		ft_memmove(conv->len_mod, "l", 2);
	if (ft_strequ(conv->len_mod, "z"))
		return (va_arg(ap, ssize_t));
	if (ft_strequ(conv->len_mod, "j"))
		return (va_arg(ap, intmax_t));
	if (ft_strequ(conv->len_mod, "hh"))
		return ((char)va_arg(ap, int));
	if (ft_strequ(conv->len_mod, "h"))
		return ((short)va_arg(ap, int));
	if (ft_strequ(conv->len_mod, "l"))
		return (va_arg(ap, long));
	if (ft_strequ(conv->len_mod, "ll"))
		return (va_arg(ap, long long));
	return (va_arg(ap, int));
}

static void			build_conv(t_conv *conv)
{
	conv->len = ft_strlen(conv->str);
	if (*conv->str == '-')
	{
		conv->lead = ft_strdup("-");
		ft_memmove(conv->str, conv->str + 1, conv->len--);
	}
	leader(conv);
	if (conv->precision == 0 && *conv->str == '0')
	{
		*conv->str = '\0';
		conv->len = 0;
	}
	else if (conv->precision == -1 && has(conv->flags, "0") &&
			!has(conv->flags, "-") &&
			conv->width > (conv->lead_len + conv->len))
		zero(conv, conv->width - (conv->lead_len + conv->len));
	else if (conv->precision > conv->len)
		zero(conv, conv->precision - conv->len);
	width(conv);
}

int					conv_int(t_conv *conv, va_list ap)
{
	conv->str = ft_lltoa(arg(conv, ap));
	build_conv(conv);
	return (print(conv));
}
