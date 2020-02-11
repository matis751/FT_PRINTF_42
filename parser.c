/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 05:27:56 by mel-oual          #+#    #+#             */
/*   Updated: 2019/11/06 05:29:37 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(t_conv *conv, const char **fmt)
{
	while (**fmt && ft_strchr("#0- +", **fmt))
	{
		if (ft_strlen(conv->flags) < 6 && !ft_strchr(conv->flags, **fmt)) /*nb flag < 6 & flag n'est pas deja parser */
			ft_strncat(conv->flags, *fmt, 1);/*ajoute le flag a la fin*/
		(*fmt)++;
	}
}

static void	parse_width(t_conv *conv, const char **fmt)/*taille*/
{
	if (ft_isdigit(**fmt))/*si est un chiffre*/
		conv->width = ft_atoi(*fmt);
	while (ft_isdigit(**fmt))/*il avance jusque ce soit plus un digit ? comment il geres la ligne av sur cett ligne ?*/
		(*fmt)++;
}

static void	parse_precision(t_conv *conv, const char **fmt)
{
	conv->precision = -1;
	if (**fmt == '.')
	{
		(*fmt)++;
		conv->precision = ft_isdigit(**fmt) ? ft_atoi(*fmt) : 0; /*si c'est un point on recherche le digit d'apres*/
	}
	while (**fmt == '-' || ft_isdigit(**fmt))
		(*fmt)++;
}

static void	parse_len_mod(t_conv *conv, const char **fmt)
{
	while (**fmt && ft_strchr("lLhjz", **fmt))
	{
		if (ft_strlen(conv->len_mod) < 2)/*si y'a moins de deux flags identique a la suite*/
			ft_strncat(conv->len_mod, *fmt, 1);
		(*fmt)++;
	}
}

void		parse_fmt(t_conv *conv, const char **fmt)
{
	parse_flags(conv, fmt); /*dans l'ordes des flags*/
	parse_width(conv, fmt);
	parse_precision(conv, fmt);
	parse_len_mod(conv, fmt);
}
