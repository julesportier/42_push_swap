/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_rotations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:10:37 by juportie          #+#    #+#             */
/*   Updated: 2025/03/24 09:30:58 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlst	*get_final_rotations(t_dlst *stack_a)
{
	t_dlst			*op_lst;
	t_stack_data	data;
	int				min_pos;

	if (stack_a == NULL)
		return (NULL);
	data = get_stack_data(stack_a);
	min_pos = get_rank_pos(stack_a, data.min);
	op_lst = get_oplst_totop(min_pos, data.size, A);
	return (op_lst);
}

void	apply_final_rotations(
	t_dlst *op_lst, t_dlst **stack_a, t_dlst **stack_b)
{
	if (op_lst != NULL && stack_a != NULL)
		apply_operations_list(op_lst, stack_a, stack_b);
}
