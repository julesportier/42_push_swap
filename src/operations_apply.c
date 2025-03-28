/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_apply.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:28:54 by juportie          #+#    #+#             */
/*   Updated: 2025/03/23 18:32:57 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

static t_dlst	**get_target(int op, t_dlst **stack_a, t_dlst **stack_b)
{
	if ((op & TARGET) == A)
		return (stack_a);
	else
		return (stack_b);
}

static t_dlst	**get_source(int op, t_dlst **stack_a, t_dlst **stack_b)
{
	if ((op & TARGET) == A)
		return (stack_b);
	else
		return (stack_a);
}

static void	apply_operation(t_dlst *op_lst, t_dlst **stack_a, t_dlst **stack_b)
{
	int	op;
	t_dlst	**target;
	t_dlst	**source;
	char	*target_key;

	op = get_operation(op_lst);
	target = get_target(op, stack_a, stack_b);
	source = get_source(op, stack_a, stack_b);
	target_key = optarget_to_str(op_lst);
	if (target_key == NULL)
		return ;
	if ((op & TYPE) == PUSH)
		p(*target_key, target, source);
	else if ((op & TYPE) == SWAP)
		s(*target_key, target, source);
	else if ((op & TYPE) == ROT)
		r(*target_key, target, source);
	else if ((op & TYPE) == REVROT)
		rr(*target_key, target, source);
}

void	apply_operations_list(t_dlst *op_lst, t_dlst **stack_a, t_dlst **stack_b)
{
	while (op_lst)
	{
		apply_operation(op_lst, stack_a, stack_b);
		op_lst = op_lst->next;
	}
}
