/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:53:49 by juportie          #+#    #+#             */
/*   Updated: 2025/03/25 10:39:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"

static t_dlst	*add_top_to_top(t_dlst *op_lst)
{
	op_lst = add_operation(op_lst, PUSH, B);
	return (op_lst);
}

static t_dlst	*add_top_to_bottom(t_dlst *op_lst)
{
	op_lst = add_operation(op_lst, PUSH, B);
	if (op_lst != NULL)
		op_lst = add_operation(op_lst, ROT, B);
	return (op_lst);
}

//static t_dlst	*add_bottom_to_top(t_dlst *op_lst)
//{
//	op_lst = add_operation(op_lst, REVROT, A);
//	if (op_lst != NULL)
//		op_lst = add_operation(op_lst, PUSH, B);
//	return (op_lst);
//}

static int	item_presort(
	t_dlst **stack_a, t_dlst **stack_b, int chunk_size, int i)
{
	static int	chunk_nbr = 2;
	t_dlst	*op_lst;

	op_lst = NULL;
	if (get_member(*stack_a, "rank") <= chunk_size * (chunk_nbr - 1))
	{
		op_lst = add_top_to_top(op_lst);
		i++;
	}
	else if (get_member(*stack_a, "rank") <= chunk_size * chunk_nbr)
	{
		op_lst = add_top_to_bottom(op_lst);
		i++;
	}
	// just more moves
	//else if (get_member((*stack_a)->prev, "rank") <= chunk_size * chunk_nbr)
	//{
	//	op_lst = add_bottom_to_top(op_lst);
	//	i++;
	//}
	else
		op_lst = add_operation(op_lst, ROT, A);
	if (DEBUG)
	{
		ft_printf(CYN "get_presort_oplst loop %d:\n", i);
		print_op_lst(op_lst);
		ft_printf(NORM);
		usleep(USLEEP);
	}
	if (i > chunk_size * chunk_nbr)
		chunk_nbr += 2;
	// CHECK FOR FREE MAIN OP_LST TOO
	if (op_lst == NULL)
		free_stacks_exit(stack_a, stack_b, EXIT_FAILURE);
	op_lst = simplify_operations(op_lst);
	if (DEBUG)
	{
		ft_printf(CYN "get_presort_oplst simplified:\n");
		print_op_lst(op_lst);
		ft_printf(NORM);
	}
	apply_operations_list(op_lst, stack_a, stack_b);
	if (DEBUG)
	{
		ft_putendl_fd(CYN "stack_a :", 1);
		print_stack(*stack_a);
		ft_putendl_fd("stack_b :", 1);
		print_stack(*stack_b);
		ft_putendl_fd(NORM, 1);
	}
	ft_dlstclear(op_lst);
	return (i);
}

void	presort(t_dlst **stack_a, t_dlst **stack_b, int chunk_size)
{
	int	i;
	t_stack_data	data_a;

	i = 1;
	data_a = get_stack_data(*stack_a);
	while (i <= data_a.size - 3)
	{
		i = item_presort(stack_a, stack_b, chunk_size, i);
	}
}
