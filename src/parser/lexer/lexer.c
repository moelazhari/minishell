/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-khad <yel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/08/30 14:05:35 by yel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_sign(t_list *list, t_node *tmp)
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

void	combaine_words(t_list *list)
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

void	del_space(t_list *list)
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

static t_list	*expand(t_list *list)
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
			rm_char(tmp->next->val, "\"'");
		tmp = tmp->next;
	}
	if (list->n)
	{
		combaine_words(list);
		del_space(list);
	}
	return (list);
}

t_list	*lexer(char *line)
{
	t_list	*list;

	list = tokenizer(line);
	if (!list)
		return (clear_list(list));
	if (!expand(list))
		return (clear_list(list));
	if (!check_syntax(list))
		return (clear_list(list));
	return (list);
}
