/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:05:27 by jmartini          #+#    #+#             */
/*   Updated: 2021/03/23 16:12:01 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef unsigned char	t_byte;
typedef struct s_struct
{
	int					zero;
	int					pad;
	int					width;
	int					prc;
	int					cnt;
}						t_struct;

int						ft_printf(const char *str, ...);
char					*ft_pf_flag_pad(char *str, t_struct *fl);
char					*ft_pf_flag_zero(char *str, t_struct *fl, va_list args);
char					*ft_pf_flag_width(char *str, t_struct *fl);
char					*ft_pf_flag_arg(char *str, t_struct *fl, va_list args);
char					*ft_pf_flag_prc(char *str, t_struct *fl, va_list args);
void					ft_pf_conv_c(t_struct *fl, va_list args);
void					ft_pf_conv_s(t_struct *fl, va_list args);
void					ft_pf_conv_p(t_struct *fl, va_list args);
void					ft_pf_conv_perc(t_struct *fl);
void					ft_pf_conv_d(t_struct *fl, va_list args);
void					ft_pf_conv_u(t_struct *fl, va_list args);
void					ft_pf_conv_x(t_struct *fl, va_list args);
void					ft_pf_conv_upx(t_struct *fl, va_list args);
void					ft_pf_conv_n(t_struct *fl, va_list args);
int						ft_pf_isdigit(int c);
size_t					ft_pf_strlen(const char *str);
int						ft_pf_atoi(const char *str);
int						ft_pf_nbrlen(long int n);
int						ft_pf_nbrlen_hex(unsigned long int n);
int						ft_pf_nbrlen_hex_addr(unsigned long long int n);
void					ft_pf_putchar(char c);
void					ft_pf_putstr(char *s);
void					ft_pf_putstrlen(char *s, int len);
void					ft_pf_putnbr(long int n);
void					ft_pf_putnbr_hex(unsigned long int n);
void					ft_pf_putnbr_hex_up(unsigned long int n);
void					ft_pf_putnbr_hex_addr(unsigned long long int n);
void					ft_pf_width_write(t_struct *fl, int len);
void					ft_pf_precision_write(t_struct *fl);
void					ft_pf_zero_write(t_struct *fl, int len);
void					ft_pf_minus_write(t_struct *fl, long int n);
int						ft_pf_exist_write(long int n, int len, t_struct *fl);

#endif
