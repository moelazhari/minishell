/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:50:58 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/30 21:18:10 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_sign(t_list *list, t_node *tmp)
{
	int		i;
	char	*str;
	
	i = -1;
	tmp = tmp->next;
	// if (tmp->prev->prev && tmp->prev->prev->type == HEREDOC)
	// {
	// 	tmp->prev->val = ft_strjoin("$", tmp->val);
	// 	del_node(list, tmp);
	// }
	if (tmp->val[0] == 0)
	{
		tmp->prev->type = WORD;
		tmp->prev->val	= ft_strdup("$");
		del_node(list, tmp);
	}
	else 
	{
		str = tmp->val;
		tmp->val = ft_strdup(get_env_var(tmp->val));
		free(str);
		if (!tmp->val)
		{
			if (tmp->prev->prev && (tmp->prev->prev->type == REDOUT ||\
			tmp->prev->prev->type == REDIN || tmp->prev->prev->type == APPEND))
			{
				ft_putstr_fd("bash: ambiguous redirect\n", 2);
				return (0);
			}	
			del_node(list, tmp);
		}
		del_node(list, tmp->prev);
	}
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
	while (tmp != list->tail)
	{
		if (tmp->type == WSPACE)
			del_node(list, tmp);
		// if (tmp->val[0] == 0)
		// 	del_node(list, tmp);	
		tmp = tmp->next;
	}
}

static t_list	*expand(t_list *list)
{
	t_node	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == SIGN)
		{
			if (!expand_sign(list, tmp))
				return (NULL);
		}
		else if (tmp->type == EXIT_STATUS)
		{
			tmp->type = WORD;
			tmp->val  = ft_itoa(g_data.status);
		}
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
	list = expand(list);
	if (!list || !list->n)
		return (clear_list(list));
	if (!check_syntax(list))
		return (clear_list(list));
	// t_node	*node;
	// node = list->head;
	// while (node)
	// {
	// 	printf("%d:%s\n", node->type, node->val);
	// 	node = node->next;
	// }
	return (list);
}