// int execute()
//     pipe(fd);
//     if (redir->type == '<')
//     {
//         fd[1] = open(redir->filename, O_RDONLY);
//         dup2(fdin, fdd);
//     }
// int execute(t_list *cmd)
// {
//     t_node  node;
//     char    **argv;
//     t_list  red_lst;
//     int     fd[2];
//     int     fdd;
//     int     fdin;

//     node = cmd->head;
//     while (node->next)
//     {
//         pipe(fd);
//         dupe2(fd[1], 0);
//         argv = node->argv;
//         redir = node->red_lst->head;
//         while (redir->next)
//         {
//         }
//     }
// }

int redir_in(t_list *redir, int fd_in)
{
    t_node *node;

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

int redir_out(t_list *redir, int fd_out)
{
    t_node *node;

    node = redir->head;
    while (node)
    {
        if (node->type == REDOUT)
            fd_out = open(node->filename, O_WRONLY | O_CREAT);
        else if (node->type == APPEND)
            fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND);
        node = node->next;
    }
    return fd_out;
}

int execute(t_list *cmds)
{
    t_node *node;
    int     fd[2];
    int     fd_in;
    int     fd_out;
    int     tmp_in;
    int     tmp_out;
    int     r;
    
    node = cmds->head;
    tmp_in = dup(0);
    tmp_out = dup(1);
    fd_in = 0;
    fd_out = 1;
    while (node)
    {
        pipe(fd);
        fd_in = redir_in(node->red, fd_in);
        if (fd_in == -1)
            exit_func("No such file or directory");
        fd_out = redir_out(node->red, fd_out);
        if (fd_out == 1 && node->next)
            dup2(fd[1], 1);
        r = fork();
        if (r == 0)
        {
            execve(node->args[0], node->args,0);
            exit(1);
        }
        else
        {
            wait();
            node = node->next;
    }
}