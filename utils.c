/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:27:55 by mel-oual          #+#    #+#             */
/*   Updated: 2019/11/02 22:50:21 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_swap(t_conv *conv, char *fix, t_field field)
{
	if (field == STR) /*field == null*/
	{
		free(conv->str);
		conv->str = fix;
	}
	else
	{
		free(conv->lead);
		conv->lead = fix;
	}
}

void	leader(t_conv *conv)/*format leader*/
{
	if (ft_strchr("dDifF", conv->type)) /*Ajoute les convertisseur dans lead*/
	{
		if (conv->lead)
			;
		else if (has(conv->flags, "+"))
			conv->lead = ft_strdup("+");
		else if (has(conv->flags, " "))
			conv->lead = ft_strdup(" ");
		else
			return ;
		conv->lead_len = 1;
	}
	if (!ft_strchr(conv->flags, '#') || ft_strchr("uU", conv->type)) /*si pas de # ou type Uu*/
		return ;/*sort de la fonction*/
	if (ft_strchr("oO", conv->type) && conv->len >= conv->precision &&
			(*conv->str != '0' || conv->precision == 0))/*Cas ou oO len > precision prmier char != 0 et precision = 0*/
		conv->lead = ft_strdup("0"); /*lead == 0*/
	else if (*conv->str == '0')
		;
	else if (conv->type == 'x')
		conv->lead = ft_strdup("0x");
	else if (conv->type == 'X')
		conv->lead = ft_strdup("0X");
	if (conv->lead)
		conv->lead_len = ft_strlen(conv->lead);
}

void	zero(t_conv *conv, int n) /*gere les 0*/
{
	char	*fix;

	if (n > 0)
	{
		fix = ft_strnew(conv->lead_len + n);/*creer une chaine taille de lead*/
		ft_memmove(fix, conv->lead, conv->lead_len);/*ajoute a fix lead*/
		ft_memset(fix + conv->lead_len, '0', n);
		free_swap(conv, fix, LEAD);
		conv->lead_len += n;
	}
}

void	width(t_conv *conv)/**/
{
	char	*fix;
	int		diff;

	diff = conv->width - (conv->lead_len + conv->len);/*taille de fmt - taille lead et len*/
	if (diff > 0) /*s'il ya une difference*/
	{
		if (ft_strchr(conv->flags, '-'))/*recherce*/
		{
			fix = ft_strnew(conv->len + diff);/*nouvelle chaine diff + len*/
			ft_memmove(fix, conv->str, conv->len);
			ft_memset(fix + conv->len, ' ', diff); /*on pose diff  * ' ' a la fin de fix*/
			free_swap(conv, fix, STR);
		}
		else
		{
			fix = ft_strnew(diff + conv->lead_len);
			ft_memset(fix, ' ', diff);
			ft_memmove(fix + diff, conv->lead, conv->lead_len);
			free_swap(conv, fix, LEAD);
		}
	}
}

int		print(t_conv *conv)
{
	int		printed;

	printed = 0;
	if (conv->lead)
		printed = ft_putstr(conv->lead);
	printed += ft_putstr(conv->str);
	free(conv->lead);
	free(conv->str);
	return (printed);
}
