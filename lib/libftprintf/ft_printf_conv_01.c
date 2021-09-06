/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:05:39 by jmartini          #+#    #+#             */
/*   Updated: 2021/03/23 16:05:41 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_conv_c(t_struct *fl, va_list args)
{
	int			len;

	len = 1;
	fl->cnt += len;
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_zero_write(fl, len);
	ft_pf_putchar(va_arg(args, int));
	if (fl->pad)
		ft_pf_width_write(fl, len);
}

void	ft_pf_conv_s(t_struct *fl, va_list args)
{
	int			len;
	char		*tmp;

	tmp = va_arg(args, char *);
	if (!tmp)
		tmp = "(null)";
	if (fl->prc > -1 && fl->prc < (int)ft_pf_strlen(tmp))
		len = fl->prc;
	else
		len = ft_pf_strlen(tmp);
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_putstrlen(tmp, len);
	fl->cnt += len;
	if (fl->pad)
		ft_pf_width_write(fl, len);
}

void	ft_pf_conv_p(t_struct *fl, va_list args)
{
	int						len;
	unsigned long long int	n;

	n = va_arg(args, unsigned long long int);
	len = ft_pf_nbrlen_hex_addr(n) + 2;
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_putstr("0x");
	ft_pf_putnbr_hex_addr(n);
	fl->cnt += len;
	if (fl->pad)
		ft_pf_width_write(fl, len);
}

void	ft_pf_conv_perc(t_struct *fl)
{
	int			len;

	len = 1;
	fl->cnt += len;
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_zero_write(fl, len);
	ft_pf_putchar('%');
	if (fl->pad)
		ft_pf_width_write(fl, len);
}
