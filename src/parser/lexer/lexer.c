/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/05 16:58:50 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_sign(t_list *list, t_node *tmp, char **env)
{
	(void)env;
	int	i;

	i = -1;
	tmp = tmp->next;
	if (tmp->val[0] == 0)
	{
		tmp->prev->type = WORD;
		del_node(list, tmp);
	}
	else 
	{
		if (getenv(tmp->val))
			tmp->val = getenv(tmp->val);
		else
			del_node(list, tmp);
		del_node(list, tmp->prev);
	}
}

void	combaine_words(t_list *list)
{
	t_node *tmp;

	tmp = list->tail;
	while (tmp != list->head)
	{
		if (tmp->type == WORD && tmp->prev->type == WORD)
		{
			tmp->prev->val = ft_strjoin(tmp->prev->val, tmp->val);
			tmp = tmp->prev;
			del_node(list, tmp->next);
		}
		else
			tmp = tmp->prev;
	}
}

static t_list	*expand(t_list *list, char **env)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == SIGN)
			expand_sign(list, tmp, env);
		tmp = tmp->next;
	}
	combaine_words(list);
	tmp = list->tail;
	while (tmp != list->head)
	{
		if (tmp->type == WSPACE)
		{
			tmp = tmp->prev;
			del_node(list, tmp->next);
		}
		else
			tmp = tmp->prev;
	}
	if (list->head->type == WSPACE)
		del_node(list, list->head);
	return (list);
}

t_list	*lexer(char *line, char **env)
{ 
	t_list	*list;

	if (!(list = tokenizer(line)))
		return (NULL);
	list = expand(list, env);
	if (!check_syntax(list))
		return (NULL);
	return (list);
}