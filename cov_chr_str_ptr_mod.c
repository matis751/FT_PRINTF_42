/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cov_chr_str_ptr_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:27:22 by mel-oual          #+#    #+#             */
/*   Updated: 2019/11/07 14:25:58 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			conv_char(t_conv *conv, va_list ap)
{
	char *fix;
	char pad;

	if (conv->width > 1)
	{
		fix = ft_strnew(conv->width - 1);/*ft_strnew de la taille du digit*/
		pad = (has(conv->flags, "0")/*si flag contiens "0"*/ && !has(conv->flags, "-"))/*et si flag contiens pas "-"*/ ? '0' : ' ';/*pad == 0 sinn ' '*/
		ft_memset(fix, pad, conv->width - 1);
		if (has(conv->flags, "-"))/*affiche le c en 1*/
		{
			ft_putchar(va_arg(ap, int));
			ft_putstr(fix);
		}
		else/*inverse*/
		{
			ft_putstr(fix);
			ft_putchar(va_arg(ap, int));
		}
		free(fix);
		return (conv->width);
	}
	ft_putchar(va_arg(ap, int));
	return (1);
}

int			conv_str(t_conv *conv, va_list ap) /*string*/
{
	conv->str = va_arg(ap, char *);
	if (!conv->str)
		conv->str = ft_strdup("(null)");
	else
		conv->str = ft_strdup(conv->str);
	conv->len = ft_strlen(conv->str);
	if (conv->precision >= 0 && conv->len > conv->precision)/*si str > precision*/
	{
		conv->str[conv->precision] = '\0';/*coupe la chaine*/
		conv->len = conv->precision;/*taille de len == nouvelle chaine*/
	}
	width(conv);/**/
	return (print(conv));
}

int			conv_mod(t_conv *conv, va_list ap)
{
	(void)ap;
	conv->str = ft_strdup("%");
	conv->len = 1;
	if (has(conv->flags, "0") && !has(conv->flags, "-") &&
		conv->width > conv->len)
		zero(conv, conv->width - conv->len);
	width(conv);
	return (print(conv));
}

int			conv_ptr(t_conv *conv, va_list ap)/*pointeur*/
{
	conv->str = ft_ulltoa_base(va_arg(ap, long), 16);/*transforme ull en char **/
	free_swap(conv, ft_strjoin("0x", conv->str), STR);
	conv->len = ft_strlen(conv->str);
	width(conv);
	return (print(conv));
}
