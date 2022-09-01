/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:52:14 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/01 14:41:51 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	p = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
			p = (char *)s + i;
		i++;
	}
	return ((char *)p);
}
