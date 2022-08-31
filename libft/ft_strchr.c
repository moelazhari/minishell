/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:51:44 by mazhari           #+#    #+#             */
/*   Updated: 2021/11/09 17:22:20 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	char	*str;
	str = (char *)s;
	i = 0;

	while (str[i] && str[i] != (char)c)
		i++;
	if (!str[i])
		return (NULL);
	return (str + i);
}
