/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_alloc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 12:20:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

static int	*alloc_operation(int operation_type, int target)
{
	int	*op;

	op = ft_calloc(1, sizeof(int));
	if (op == NULL)
		return (NULL);
	*op = (operation_type & OPERATION) | (target & TARGET);
	return (op);
}

// If the allocation fails it free the op_lst and return NULL,
// no other memory is freed.
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
			ft_dlstclear(op_lst);
			return (NULL);
		}
		ft_dlstadd_back(&op_lst, new_node);
	}
	return (op_lst);
}
