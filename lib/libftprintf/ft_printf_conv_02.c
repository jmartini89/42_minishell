/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:05:44 by jmartini          #+#    #+#             */
/*   Updated: 2021/03/23 16:05:46 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_pf_setup_d(long int *n, int *len, int *nlen, t_struct *fl)
{
	int	prc_tmp;

	if (fl->zero && fl->prc >= 0)
	{
		fl->width = fl->zero;
		fl->zero = 0;
	}
	prc_tmp = fl->prc;
	fl->prc -= *nlen;
	if (prc_tmp > 0 && fl->prc > 0)
		*len = fl->prc + *nlen;
	if (*n < 0)
		*len += 1;
	if (fl->zero && fl->prc <= 0)
		fl->width = -1;
}

void	ft_pf_conv_d(t_struct *fl, va_list args)
{
	int				len;
	int				nlen;
	long int		n;

	n = va_arg(args, int);
	nlen = ft_pf_nbrlen(n);
	len = nlen;
	if (!ft_pf_exist_write(n, len, fl))
		return ;
	ft_pf_setup_d(&n, &len, &nlen, fl);
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_minus_write(fl, n);
	ft_pf_precision_write(fl);
	ft_pf_zero_write(fl, len);
	ft_pf_putnbr(n);
	fl->cnt += nlen;
	if (fl->pad)
		ft_pf_width_write(fl, len);
}

static void	ft_pf_setup_u(int *len, int *nlen, t_struct *fl)
{
	int	prc_tmp;

	if (fl->zero && fl->prc >= 0)
		fl->width = fl->zero;
	prc_tmp = fl->prc;
	fl->prc -= *nlen;
	if (prc_tmp > 0 && fl->prc > 0)
		*len = fl->prc + *nlen;
	if (fl->zero && fl->prc < 0)
	{
		fl->width = fl->zero;
		fl->pad = 0;
	}
}

void	ft_pf_conv_u(t_struct *fl, va_list args)
{
	int			len;
	int			nlen;
	long int	n;

	n = va_arg(args, unsigned int);
	nlen = ft_pf_nbrlen(n);
	len = nlen;
	if (!ft_pf_exist_write(n, len, fl))
		return ;
	if (fl->zero && fl->prc < 0)
	{
		ft_pf_zero_write(fl, len);
		ft_pf_putnbr(n);
		fl->cnt += nlen;
		return ;
	}
	ft_pf_setup_u(&len, &nlen, fl);
	if (!fl->pad)
		ft_pf_width_write(fl, len);
	ft_pf_precision_write(fl);
	ft_pf_putnbr(n);
	fl->cnt += nlen;
	if (fl->pad)
		ft_pf_width_write(fl, len);
}
