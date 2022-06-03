/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/03 17:41:18 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expaned_sign(t_list *list, t_node *tmp, char **env)
{
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
		while (env[++i])
		{
			if (!ft_strncmp(tmp->val, env[i], ft_strlen(tmp->val)))
			{
				tmp->val = *(env + i) + ft_strlen(tmp->val) + 1;
				break ;
			}
		}
		if (!env[i])
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

static t_list	*expaned(t_list *list, char **env)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == SIGN)
			expaned_sign(list, tmp, env);
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
	if (!check_syntax(list))
		return (NULL);
	list = expaned(list, env);
	return (list);
}