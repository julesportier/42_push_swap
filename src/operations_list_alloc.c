/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_alloc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/23 16:58:08 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

static int	*alloc_operation(int operation_type, int target)
{
	int	*op;

	op = malloc(1 * sizeof(int));
	if (op == NULL)
		return (NULL);
	*op = (operation_type & TYPE) | (target & TARGET);
	return (op);
}

// If the allocation fails it free the op_lst and return NULL,
// no other memory is freed.
t_dlst	*add_operation(t_dlst *op_lst, int type, int target)
{
	t_dlst	*new_node;
	int		*op;

	if (target >= 0 && target <= TARGET
		&& (type == 0 || type == PUSH || type == SWAP
			|| type == ROT || type == REVROT))
	{
		op = alloc_operation(type, target);
		if (op == NULL)
		{
			ft_dlstclear(op_lst);
			return (NULL);
		}
		new_node = ft_dlstnew(op);
		if (new_node == NULL)
		{
			free(op);
			ft_dlstclear(op_lst);
			return (NULL);
		}
		ft_dlstadd_back(&op_lst, new_node);
		return (op_lst);
	}
	else
		return (NULL);
}
