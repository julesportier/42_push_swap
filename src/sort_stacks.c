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
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"
#include <stdlib.h>

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

// already checked if given sorted, size == 1 or 2
static void	sort_in_place(t_dlst **stack, t_stack_data *data)
{
	if (data->size == 2)
	{
		r('a', stack, NULL);
		return ;
	}
	else if (data->size == 3)
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

void	sort_stacks(t_dlst **lst, t_stack_data *data)
{
	t_dlst	*stack_b;
	t_stack_data	data_a;
	t_stack_data	data_b;
	int	chunk_size;

	stack_b = NULL;
	store_rank(*lst, data);
	
	// NEW TESTS WITH FIXED MERGE/DEL PAIRS
	// 500 numbers:
	// chunks size 76: w4595 A_MEAN||(4053, 4060, 4058, 4062, 4052) b3619 (iter500*5)
	// chunks size 77: w4545 A_MEAN|4050|(4054, 4045, 4046, 4056, 4049) b3581 (iter500*5)
	// chunks size 78: w4644 A_MEAN|4051.4|(4051, 4046, 4053, 4053, 4054) b3633 (iter500*5)
	// chunks size 79: w4577 A_MEAN|4057.2|(4050, 4050, 4056, 4063, 4067) b3615 (iter500*5)
	// chunks size 80: w4505 A_MEAN|4054|(4049, 4046, 4060, 4061) b3620 (iter500*4)
	// chunks size 82: w4574 A_MEAN|4069|(4072, 4073, 4062) b3672 (iter500*3)
	// best chunk size for 500 numbers is 77
	// 100 numbers:
	// chunks size 36: w672 A_MEAN|563|(562, 563, 563, 563, 563) b480 (iter2000*5)
	// chunks size 37: w675 A_MEAN|562|(563, 562, 562, 562, 562) b482 (iter2000*5)
	// chunks size 38: w681 A_MEAN|563|(563, 562, 564, 562, 562) b453 (iter2000*5)
	// chunks size 39: w683 A_MEAN|563|(564, 564, 563, 562, 564) b482 (iter2000*5)
	// function to get chunk size is f(x) = sqrt(x*11) + 4 (100 -> 37.16; 500 -> 78.16)
	chunk_size = ft_sqrt_floor(data->size * 11) + 4;
	if (DEBUG)
		ft_printf("chunk_size == %d\n", chunk_size);
	presort(lst, &stack_b, chunk_size);
	data_a = get_stack_data(*lst);
	if (!is_sorted(*lst))
		sort_in_place(lst, &data_a);
	while (ft_cdlstsize(stack_b) > 0)
	{
		data_a = get_stack_data(*lst);
		data_b = get_stack_data(stack_b);
		store_op_lists(*lst, stack_b, data_a.size, data_b.size);
		t_dlst	*cheapest = get_cheapest(stack_b);
		free_priciers(stack_b, cheapest);
		apply_operations_list(get_member_oplst(cheapest), lst, &stack_b);
		ft_dlstclear(get_member_oplst(cheapest));
		set_member_oplst(cheapest, NULL);
	}
	t_dlst	*op_lst = get_final_rotations(*lst);
	apply_final_rotations(op_lst, lst, &stack_b);
	ft_dlstclear(op_lst);
}
