#include "minishell.h"

int redir_in(t_red *redir, int fd_in)
{
    t_red_node *node;

    node = redir->head;
    while (node)
    {
        if (node->type == REDIN)
        {
            fd_in = open(node->filename, O_RDONLY);
            if (fd_in == -1)
                return -1;
        }
        node = node->next;
    }
    return fd_in;
}

int redir_out(t_red *redir, int fd_out)
{
    t_red_node *node;

    node = redir->head;
    while (node)
    {
        if (node->type == REDOUT)
            fd_out = open(node->filename, O_WRONLY | O_CREAT, 0777);
        else if (node->type == APPEND)
            fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
        node = node->next;
    }
    return fd_out;
}

void execute(t_cmd *cmds)
{
    t_cmd_node *node;
    int     fd[2];
    int     fd_in;
    int     fd_out;
    int     tmp_in;
    int     tmp_out;
    int     r;
    char    *path;
    char    **splited_path;
    

    path = getenv("PATH");
    splited_path = ft_split(path, ':');
    node = cmds->head;
    tmp_in = dup(0);
    tmp_out = dup(1);
    fd_in = 0;
    while (node)
    {
        fd_out = 1;
        pipe(fd);
        fd_in = redir_in(node->red, fd_in);
        //if (fd_in == -1)
            //exit("No such file or directory");
        //    exit(1);
        dup2(fd_in, 0);
        fd_out = redir_out(node->red, fd_out);
        r = fork();
        if (r == 0)
        {
            if (fd_out == 1 && node->next)
                dup2(fd[1], 1);
            else if (fd_out != 1)
                dup2(fd_out,1);
            if (ft_strchr(node->args[0], '/'))
                execve(node->args[0], node->args, NULL);
            else
                while (*splited_path)
                    execve(ft_strjoin(ft_strjoin(*splited_path++, "/"), node->args[0]), node->args, NULL);
            perror("execv");
            exit(0);
        }
        else
        {
            wait(0);
            node = node->next;
            close(fd[1]);
            dup2(fd[0], fd_in);
        }
    }
    dup2(tmp_in,0);
    dup2(tmp_out,1);
} 