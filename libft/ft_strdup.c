/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:54:01 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/20 18:28:15 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)

{
	char	*dest;
	int		i;
	
	if (!s)
		return (NULL);	
	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
	}
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
