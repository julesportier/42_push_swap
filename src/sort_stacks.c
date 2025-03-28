/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:16:08 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 19:03:36 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_dlst *stack)
{
	t_dlst	*last;
	t_dlst	*prev_node;

	last = stack->prev;
	while (stack != last)
	{
		prev_node = stack;
		stack = stack->next;
		if (get_member(prev_node, "value") > get_member(stack, "value"))
			return (0);
	}
	return (1);
}

static void	sort_in_place(t_dlst **stack, t_stack_data *data)
{
	if (data->size <= 3)
	{
		while (!is_sorted(*stack))
		{
			if (get_member(*stack, "rank") == data->max)
				r('a', stack, NULL);
			else if (get_member((*stack)->prev, "rank") == data->min)
				rr('a', stack, NULL);
			else if (get_member(*stack, "rank") == data->min)
			{
				rr('a', stack, NULL);
				s('a', stack, NULL);
			}
			else if (get_member((*stack)->next, "rank") == data->min)
				s('a', stack, NULL);
		}
	}
}

static void	insert_sort_weighted(t_dlst **stack_a, t_dlst **stack_b)
{
	t_dlst			*cheapest;
	t_stack_data	data_a;
	t_stack_data	data_b;

	while (ft_cdlstsize(*stack_b) > 0)
	{
		data_a = get_stack_data(*stack_a);
		data_b = get_stack_data(*stack_b);
		store_op_lists(*stack_a, *stack_b, data_a.size, data_b.size);
		cheapest = get_cheapest(*stack_b);
		free_priciers(*stack_b, cheapest);
		apply_operations_list(get_member_oplst(cheapest), stack_a, stack_b);
		ft_dlstclear(get_member_oplst(cheapest));
		set_member_oplst(cheapest, NULL);
	}
}

void	sort_stacks(t_dlst **stack_a, t_stack_data *data)
{
	t_dlst			*stack_b;
	t_dlst			*cheapest;
	t_stack_data	data_a;
	int				chunk_size;

	stack_b = NULL;
	store_rank(*stack_a, data);
	chunk_size = ft_sqrt_floor(data->size * 11) + 4;
	presort(stack_a, &stack_b, chunk_size);
	data_a = get_stack_data(*stack_a);
	sort_in_place(stack_a, &data_a);
	insert_sort_weighted(stack_a, &stack_b);
	cheapest = get_final_rotations(*stack_a);
	apply_final_rotations(cheapest, stack_a, &stack_b);
	ft_dlstclear(cheapest);
}
