/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:16:08 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:39 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"
#include <stdlib.h>

int	is_superior(int a, int b)
{
	if (a > b)
		return (1);
	return (0);
}

//static int	is_inferior(int a, int b)
//{
//	if (a < b)
//		return (1);
//	return (0);
//}

int	is_sorted(t_dlst *stack, int check(int a, int b))
{
	t_dlst	*last;
	t_dlst	*prev_node;

	last = stack->prev;
	while (stack != last)
	{
		prev_node = stack;
		stack = stack->next;
		if (check(get_member(prev_node, "value"), get_member(stack, "value")))
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
		while (!is_sorted(*stack, is_superior))
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
	//limit = data->size / 2 + data->size % 2;
	store_rank(*lst, data);
	
	// need to fine tune 3 and 5
	// 500 numbers:
	// chunks size 33: w5310 a4745 b4391 (iter500)
	// chunks size 34: w5239 a4707 b4375 (iter500)
	// chunks size 35: w5218 a4675 b4289 (iter500)
	// chunks size 36: w5127 a4644 b4261 (iter500)
	// chunks size 37: w5221 a4616 b4210 (iter500)
	// chunks size 38: w5050 a4585 b4196 (iter500)
	// chunks size 88: w4806 a4296 b3852 (iter500)
	// chunks size 82: w4759 a4295 b3944 (iter500)
	// chunks size 80: w4786 a4287 b3823 (iter500)
	// chunks size 68: w4775 a4276 b3946 (iter500)
	// chunks size 73: w4750 a4275 b3925 (iter500)
	// chunks size 75: w4748 a4273 b3933 (iter500)
	// chunks size 79: w4769 a4269 b3896 (iter500*4)
	// chunks size 78: w4768(4826) A_MEAN|4266.5|(4269, 4262, 4267, 4271, 4263) b3800 (iter500*5)
	// chunks size 77: w4821 A_MEAN|4265.8|(4259, 4266, 4262, 4269, 4273) b3781 (iter500*5)
	// chunks size 76: w4718 A_MEAN|4262.67|(4268, 4258, 4260, 4261, 4268, 4261) b3806 (iter500*6)
	// chunks size 75: w4830 A_MEAN|4267|(4261, 4281, 4264, 4258, 4271) b3820 (iter500*5)
	// chunks size 74: w4745 A_MEAN|4271|(4273, 4271, 4272, 4277, 4262) b3838 (iter500*5)
	// best chunk size for 500 numbers is 76
	// 100 numbers:
	// chunks size 13: W$751 a631 b559 (iter2000)
	// chunks size 53: W$739 a602 b504 (iter2000)
	// chunks size 48: W$715 a598 b514 (iter2000)
	// chunks size 43: W$674 a584 b505 (iter2000)
	// chunks size 41: W$706 a580 b498 (iter2000)
	// chunks size 40: W$696 a579 b494 (iter2000)
	// chunks size 39: W$691 a578 b495 (iter2000)
	// chunks size 38: W$695(1x715) a579 b500 (iter2000*10)
	// chunks size 37: W$693 a577 b486 (iter2000*10)
	// chunks size 36: W$696 a577 b506 (iter2000*6)
	// chunks size 35: W$692 a578 b502 (iter2000*3)
	// chunks size 34: W$710 a578 b504 (iter2000*3)
	// chunks size 33: W$701 a581 b501 (iter2000*3)
	// chunks size 23: W$689 a584 b506 (iter2000)
	// best chunk size for 100 numbers is 37
	// function to get chunk size is f(x) = sqrt(x*10) + 6 (100 -> 37.62; 500 -> 76.71)
	chunk_size = ft_sqrt_floor(data->size * 10) + 6;
	if (DEBUG)
		ft_printf("chunk_size == %d\n", chunk_size);
	presort(lst, &stack_b, chunk_size);
	data_a = get_stack_data(*lst);
	if (!is_sorted(*lst, is_superior))
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
