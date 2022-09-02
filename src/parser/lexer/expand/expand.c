/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:26:00 by mazhari           #+#    #+#             */
/*   Updated: 2022/09/02 11:31:15 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	expand_sign(t_list *list, t_node *tmp)
{
	int		i;
	char	*str;

	i = -1;
	tmp = tmp->next;
	str = tmp->val;
	tmp->val = ft_strdup(get_env_var(tmp->val));
	free(str);
	if (!tmp->val)
		tmp->val = ft_strdup("");
	del_node(list, tmp->prev);
	return (1);
}

static char	*rm_char(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
	return (str);
}

static void	combaine_words(t_list *list)
{
	t_node	*tmp;
	char	*str;

	if (list->n <= 1)
		return ;
	tmp = list->tail;
	while (tmp != list->head)
	{
		if (tmp->type == WORD && tmp->prev->type == WORD)
		{
			free(tmp->prev->val);
			str = ft_strjoin(tmp->prev->val, tmp->val);
			tmp->prev->val = str;
			tmp = tmp->prev;
			del_node(list, tmp->next);
		}
		else
			tmp = tmp->prev;
	}
}

static void	del_space(t_list *list)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == WSPACE)
			del_node(list, tmp);
		tmp = tmp->next;
	}
}

t_list	*expand(t_list *list)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp && tmp->type == SIGN)
		{
			if (!expand_sign(list, tmp))
				return (NULL);
		}
		else if (tmp && tmp->type == EXIT_STATUS)
		{
			tmp->type = WORD;
			tmp->val = ft_itoa(g_data.status);
		}
		else if (tmp && tmp->next && tmp->type == HEREDOC)
			rm_char(tmp->next->val);
		tmp = tmp->next;
	}
	if (list->n)
	{
		combaine_words(list);
		del_space(list);
	}
	return (list);
}
