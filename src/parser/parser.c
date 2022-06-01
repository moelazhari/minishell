/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:20:49 by mazhari           #+#    #+#             */
/*   Updated: 2022/06/01 21:36:42 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_red(t_red   *red)
{
	t_red_node  *tmp;
	int i;

	i = 0;
    if (!red)
        return ;
	tmp = red->head;
	while (tmp)
	{
		printf("%d node taype: %d val: %s\n", i, tmp->type, tmp->filename);
		tmp = tmp->next;
	}
}

static  t_red   *get_red(t_list *list)
{
    t_red  *red;
    t_node  *tmp;

    red = new_red();
    tmp = list->head;
    while (tmp && tmp->type != PIPE)
    {
        if (ft_strchr("<>", tmp->val[0]))
        {
            if (tmp->type == REDIN)
                red = push_back_red(red, REDIN, tmp->next->val);
            else if (tmp->type == REDOUT)
                red = push_back_red(red, REDOUT, tmp->next->val);
            else if (tmp->type == APPEND)
                red = push_back_red(red, APPEND, tmp->next->val);
            else if (tmp->type == HEREDOC)
                red = push_back_red(red, HEREDOC, tmp->next->val);
            tmp = tmp->next->next;
        }
        tmp = tmp->next;
    }
    if (!red->head)
    {
        red = NULL;
        free(red);
    }
    print_red(red);
    return (red);
}

// static  t_node  *get_args(char **args, t_cmd *cmd, t_red *red, t_list *list)
// {
//     t_node *tmp;
//     int i;

//     i = 0;
//     tmp = list->head;
//     while (tmp && tmp->type != PIPE)
//     {
//         i++;
//         tmp = tmp->next;
//     }
//     args = malloc(sizeof(char *) * i);
//     tmp = list->head;
//     while (tmp && tmp->type != PIPE)
//     {
//         args[i++] = tmp->val;
//         push_back_cmd(cmd, args, red);
//         tmp = tmp->next;
//     }
//     args[i] = NULL;
//     return (tmp);
// }

t_cmd  *paser(t_list *list)
{
    t_cmd  *cmd;
    t_node *tmp;
    t_red  *red;
    char   **args;

    args = NULL;
    cmd = new_cmd();
    tmp = list->head;
    red = get_red(list);
    // tmp = get_args(args, cmd, red, list);
    // if (!tmp)
    //     return (cmd);
    // else
    // {
    //     list->head = tmp->next;
    //     del_node(list, tmp);
    //     paser(list);
    // }
    return (cmd);
}