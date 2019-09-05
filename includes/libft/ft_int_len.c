/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 21:09:01 by kblack            #+#    #+#             */
/*   Updated: 2018/08/27 21:24:12 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_int_len(int n)
{
	size_t	i;

	i = 1;
	while ((n /= 10))
		i++;
	return (i);
}