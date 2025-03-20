/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 12:20:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"
#include "../libft/src/ft_printf.h"

static int	*alloc_operation(int operation_type, int target)
{
	int	*op;

	op = ft_calloc(1, sizeof(int));
	if (op == NULL)
		return (NULL);
	*op = (operation_type & OPERATION) | (target & TARGET);
	return (op);
}

t_dlst	*add_operation(t_dlst *op_lst, int operation_type, int target)
{
	t_dlst	*new_node;
	int	*op;

	if (operation_type != 0 && target != 0)
	{
		op = alloc_operation(operation_type, target);
		if (op == NULL)
			return (NULL);
		new_node = ft_dlstnew(op);
		if (new_node == NULL)
		{
			free(op);
			// needs to free op_lst too
			// and all allocated memory
			// after that: EXIT_FAILURE
			return (NULL);
		}
		ft_dlstadd_back(&op_lst, new_node);
	}
	return (op_lst);
}

static void	print_op(t_dlst *node)
{
	int	content;
	char	*op;
	char	*target;

	if (node)
	{
		content = *(int *)(node->content);
		if (content == -1)
			return ;
		if ((content & OPERATION) == PUSH)
			op = "p";
		else if ((content & OPERATION) == SWAP)
			op = "s";
		else if ((content & OPERATION) == ROT)
			op = "r";
		else if ((content & OPERATION) == REVROT)
			op = "rr";
		else
			op = "?";
		if ((content & TARGET) == A)
			target = "a";
		else if ((content & TARGET) == B)
			target = "b";
		else if ((content & TARGET) == BOTH)
			target = "both";
		else
			target = "?";
		ft_printf("%s, %s\n", op, target);
	}
}

void	print_op_lst(t_dlst *lst)
{
	while (lst)
	{
		print_op(lst);
		lst = lst->next;
	}
}

int	get_content(t_dlst *node)
{
	if (node)
		return(*(int *)(node->content));
	else
		return (-1);

}
void	set_content(t_dlst *node, int operation)
{
	if (node)
		*(int *)(node->content) = operation;
}
