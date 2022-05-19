# include <stdlib.h>

typedef struct	s_node
{
	int				type;
	struct s_node	*prev;
	char			*val;
	struct s_node	*next;
}				t_node;

typedef struct	s_list
{
	int		n; // number of node;
	t_node	*head; // the beginning of the list
	t_node	*tail; // the end of the list
}				t_list;	

t_node	*new_node(int type, char *val)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	new->type = type;
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_node	*push_back(t_list *list, int type, char *val)
{
	t_node	*new;

	new = new_node(type, val);
	new->prev = list->tail;
	if (list->tail)
		list->tail->next = new;
	else
		list->head = new;
	list->tail = new;
	(list->n)++;
	return (new);
}

t_list	*new_list(void)
{
	t_list *list;	

	list = malloc(sizeof(t_list));
	list->n = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

void print_list(t_list *list)
{
	t_node *tmp;
	int i;

	tmp = list->head;
	i = 0;

	printf("number of nodes %d\n", list->n);
	while (i < list->n)
	{
		printf("%s\n", tmp->val);
		tmp = tmp->next;
		i++;
	}
}

int main()
{
	t_list *list;

	list = new_list();
	push_back(list, 69, "1");
	push_back(list, 69, "2");
	push_back(list, 69, "3");
	push_back(list, 69, "4");
	push_back(list, 69, "5");
	push_back(list, 69, "6");
		
	 print_list(list);
}