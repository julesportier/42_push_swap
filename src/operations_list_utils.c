/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/21 13:31:51 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

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

static char	*optype_to_str(t_dlst *node)
{
	int	content;
	char	*op;

	if (node == NULL)
		return (NULL);
	content = get_content(node);
	if ((content & OPERATION) == PUSH)
		op = "p";
	else if ((content & OPERATION) == SWAP)
		op = "s";
	else if ((content & OPERATION) == ROT)
		op = "r";
	else if ((content & OPERATION) == REVROT)
		op = "rr";
	else
		op = NULL;
	return (op);
}

static char	*optarget_to_str(t_dlst *node)
{
	int	content;
	char	*target;

	if (node == NULL)
		return (NULL);
	content = get_content(node);
	if ((content & TARGET) == A)
		target = "a";
	else if ((content & TARGET) == B)
		target = "b";
	else if ((content & TARGET) == BOTH)
		target = "both";
	else
		target = NULL;
	return (target);
}

// The string returned must be freed after use.
// The potential check for NULL node must be did before calling this function.
char	*operation_to_str(t_dlst *node)
{
	int	content;
	char	*op_type;
	char	*operation;

	content = get_content(node);
	op_type = optype_to_str(node);
	if ((content & TARGET) == BOTH)
	{
		if ((content & OPERATION) == ROT || (content & OPERATION) == REVROT)
			operation = ft_strjoin(op_type, "r");
		else
			operation = ft_strjoin(op_type, op_type);
	}
	else
		operation = ft_strjoin(op_type, optarget_to_str(node));
	if (operation == NULL)
		return (NULL);
	return (operation);
}
