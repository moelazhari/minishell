/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:20:49 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/03 15:56:08 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    print_red(t_red *red)
// {
// 	t_red_node  *tmp;
// 	int i;

// 	i = 0;
//     if (!red)
//         return ;
// 	tmp = red->head;
//     printf("number of nodes %d: \n", red->n);
// 	while (tmp)
// 	{
// 		printf("%d node taype: %d val: %s\n", i, tmp->type, tmp->filename);
// 		tmp = tmp->next;
//         i++;
// 	}
// }


void    join_nodes(t_list *list, t_node *tmp)
{    
    if (list->n == 0 || list->n == 1)
        return ;
    if (tmp->type == PIPE)
        tmp = tmp->prev;
	while (tmp != list->head)
	{
        tmp->prev->val = ft_strjoin(ft_strjoin(tmp->prev->val , " "), tmp->val);
        tmp = tmp->prev;	
		del_node(list, tmp->next);
    }
}

t_node  *remove_red(t_list *list, t_node *tmp)
{
    t_node *ret;

    ret = tmp;
    if (list->n == 0 || list->n == 1)
        return (NULL);
    while (tmp != list->head)
    {
        if (tmp->type == WORD && ft_strchr("<>", tmp->prev->val[0]))
            del_node(list, tmp);
        else if (ft_strchr("<>", tmp->val[0]))
            del_node(list, tmp);
       tmp = tmp->prev;
    }
    if (ft_strchr("<>", tmp->val[0]))
        del_node(list, tmp);
    join_nodes(list, ret);
    return (tmp);
}

static  t_red   *get_red(t_list *list)
{
    t_red   *red;
    t_node  *tmp;

    red = new_red();
    tmp = list->head;
    while (tmp != list->tail && tmp->type != PIPE)
    {
        if (ft_strchr("<>", tmp->val[0]))
        {
            if (tmp->type == REDIN)
                push_back_red(red, REDIN, tmp->next->val);
            else if (tmp->type == REDOUT)
                push_back_red(red, REDOUT, tmp->next->val);
            else if (tmp->type == APPEND)
                push_back_red(red, APPEND, tmp->next->val);
            else if (tmp->type == HEREDOC)
                push_back_red(red, HEREDOC, tmp->next->val);
        }
        tmp = tmp->next;
    }
    remove_red(list, tmp);
    if (red->n == 0)
        free(red);
    return (red);
}

// void	print_cmd(t_cmd   *cmd)
// {
// 	t_cmd_node  *tmp;
// 	int i;

// 	i = -1;
//     if (!cmd)
//         return ;
// 	tmp = cmd->head;
//     printf("number of nodes %d: \n", cmd->n);
    
// 	while (tmp)
// 	{
//         while (tmp->args[i])
//         {
// 		    printf("node args: %s ", tmp->args[i]);
//             i++;
//         }
// 		tmp = tmp->next;
// 	}
// }

t_cmd  *paser(t_list *list, t_cmd *cmd)
{
    t_node  *tmp;
    t_red   *red;
    char    **args;

    tmp = list->head;
    red = get_red(list);
    args = ft_split(list->head->val, ' ');
    push_back_cmd(cmd, args, red);
    // if (list->n == 1)
    // {
        del_node(list, list->head);
        free(list);
        return (cmd);
    // }
    // else
    // {
    //     list->head = list->head->next->next;
    //     del_node(list, tmp->prev);
    //     paser(list, cmd);
    // }
    return (cmd);
}