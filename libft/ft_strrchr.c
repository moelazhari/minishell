/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:52:14 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/16 15:04:45 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = (char *)s;
	while (str[len] != (char)c)
	{
		if (len == 0)
			return (NULL);
		len--;
	}
	return (str + len);
}
