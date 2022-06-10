/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/10 18:40:03 by mazhari          ###   ########.fr       */
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

static t_list	*expand(t_list *list, char **env, int *status)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == SIGN)
			expand_sign(list, tmp, env);
		else if (tmp->type == EXIT_STATUS)
		{
			tmp->type = WORD;
			tmp->val  = ft_itoa(*status);
		}
		tmp = tmp->next;
	}
	combaine_words(list);
	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == WSPACE)
			del_node(list, tmp);
		tmp = tmp->next;
	}
	return (list);
}

t_list	*lexer(char *line, char **env, int *status)
{ 
	t_list	*list;

	if (!(list = tokenizer(line, status)))
		return (NULL);
	list = expand(list, env, status);
	if (!check_syntax(list, status))
		return (NULL);
	return (list);
}