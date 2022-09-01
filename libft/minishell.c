/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:41 by yel-khad          #+#    #+#             */
/*   Updated: 2022/08/24 17:35:42 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

int	ft_startcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] && s2[i] == s1[i])
		return (1);
	return (0);
}

int	ft_asciicmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}
