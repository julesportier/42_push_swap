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

int	is_sorted(t_dlst *stack)
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

static t_dlst	*get_cheapest(t_dlst *stack)
{
	t_dlst	*node;
	t_dlst	*cheapest;
	int		min_len;
	int		tmp_len;

	node = stack;
	cheapest = node;
	min_len = INT_MAX;
	while (node)
	{
		tmp_len = ft_dlstsize(get_member_oplst(node));
		if (tmp_len > 0
			&& (tmp_len < min_len || (tmp_len == min_len
					&& get_member(node, "rank")
					> get_member(cheapest, "rank"))))
		{
			min_len = tmp_len;
			cheapest = node;
		}
		node = node->next;
		if (node == stack)
			node = NULL;
	}
	return (cheapest);
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
		apply_operations_list(get_member_oplst(cheapest), stack_a, stack_b);
		ft_dlstclear(get_member_oplst(cheapest));
		set_member_oplst(cheapest, NULL);
		free_oplsts(*stack_b);
	}
}

void	sort_stacks(t_dlst **stack_a, t_stack_data *data)
{
	t_dlst			*stack_b;
	t_dlst			*op_lst;
	t_stack_data	data_a;
	int				chunk_size;

	stack_b = NULL;
	store_rank(*stack_a, data);
	chunk_size = ft_sqrt_floor(data->size * 11) + 4;
	presort(stack_a, &stack_b, chunk_size);
	data_a = get_stack_data(*stack_a);
	sort_in_place(stack_a, &data_a);
	insert_sort_weighted(stack_a, &stack_b);
	op_lst = get_final_rotations(*stack_a);
	apply_operations_list(op_lst, stack_a, &stack_b);
	ft_dlstclear(op_lst);
	ft_dlstclear(stack_b);
}
