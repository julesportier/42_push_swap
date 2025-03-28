/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:53:49 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 16:53:50 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_dlst	*add_top_to_top(t_dlst *op_lst)
{
	op_lst = add_operation(op_lst, PUSH, B);
	return (op_lst);
}

static t_dlst	*add_top_to_bottom(t_dlst *op_lst)
{
	op_lst = add_operation(op_lst, PUSH, B);
	if (op_lst != NULL)
	{
		op_lst = add_operation(op_lst, ROT, B);
	}
	return (op_lst);
}

static int	item_presort(
	t_dlst **stack_a, t_dlst **stack_b, int chunk_size, int item_nbr)
{
	static int	chunk_nbr = 2;
	t_dlst		*op_lst;

	op_lst = NULL;
	if (get_member(*stack_a, "rank") <= chunk_size * (chunk_nbr - 1))
	{
		op_lst = add_top_to_top(op_lst);
		item_nbr++;
	}
	else if (get_member(*stack_a, "rank") <= chunk_size * chunk_nbr)
	{
		op_lst = add_top_to_bottom(op_lst);
		item_nbr++;
	}
	else
		op_lst = add_operation(op_lst, ROT, A);
	if (op_lst == NULL)
		free_stacks_exit(stack_a, stack_b, EXIT_FAILURE);
	if (item_nbr > chunk_size * chunk_nbr)
		chunk_nbr += 2;
	op_lst = simplify_operations(op_lst);
	apply_operations_list(op_lst, stack_a, stack_b);
	ft_dlstclear(op_lst);
	return (item_nbr);
}

void	presort(t_dlst **stack_a, t_dlst **stack_b, int chunk_size)
{
	int				item_nbr;
	t_stack_data	data_a;

	item_nbr = 1;
	data_a = get_stack_data(*stack_a);
	while (item_nbr <= data_a.size - 3)
	{
		item_nbr = item_presort(stack_a, stack_b, chunk_size, item_nbr);
	}
}
