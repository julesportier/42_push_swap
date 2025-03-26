/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:23:43 by juportie          #+#    #+#             */
/*   Updated: 2025/03/24 10:49:35 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"

t_dlst	*get_oplst_totop(int pos, int stack_size, int source_macro)
{
	t_dlst	*op_lst;

	op_lst = NULL;
	if (stack_size < 2)
	{
		if (DEBUG)
		{
			ft_printf(RED "TEST get_oplst_totop:\n");
			print_op_lst(op_lst);
			ft_printf(NORM);
		}
		return (NULL);
	}
	if (pos <= (stack_size / 2 + stack_size % 2) || stack_size < 3)
	{
		while (pos > 1)
		{
			op_lst = add_operation(op_lst, ROT, source_macro);
			if (op_lst == NULL)
				return (NULL);
			pos--;
		}
		// Don't use the swap to have more simplification possibilities
		//while (pos > 2)
		//{
		//	op_lst = add_operation(op_lst, ROT, source_macro);
		//	pos--;
		//}
		//if (pos == 2)
		//	op_lst = add_operation(op_lst, SWAP, source_macro);
	}
	else if (pos > (stack_size / 2 + stack_size % 2))
	{
		while (pos <= stack_size)
		{
			op_lst = add_operation(op_lst, REVROT, source_macro);
			if (op_lst == NULL)
				return (NULL);
			pos++;
		}
	}
	if (DEBUG)
	{
		ft_printf(RED "TEST get_oplst_totop:\n");
		print_op_lst(op_lst);
		ft_printf(NORM);
	}
	return (op_lst);
}

// This function return the insertion pos to have a sorted circular list,
// the head doesn't necessarly corresponding to the smaller (first) element.
// Return val go from 0 (to top) to dest size - 1 (before end) (never push to end)
static int	get_insert_pos(t_dlst *node, t_dlst *stack_a)
{
	int	pos;
	t_stack_data	data_a;
	t_dlst	*last_a;

	pos = 0;
	data_a = get_stack_data(stack_a);
	last_a = stack_a->prev;
	if (get_member(node, "rank") < get_member(last_a, "rank")
			|| get_member(node, "rank") > data_a.max)
	{
		while (get_member(stack_a, "rank") != data_a.min)
		{
			stack_a = stack_a->next;
			pos++;
		}
	}
	if (get_member(node, "rank") > data_a.max)
		return (pos);
	while (get_member(node, "rank") > get_member(stack_a, "rank")
			&& stack_a != last_a)
	{
		stack_a = stack_a->next;
		pos++;
	}
	return (pos);
}

// Append the list of operations to "insert" the element to the correct position,
// the list is rotating: the "first" element can be everywhere,
// this permit to avoid doing the rotations to point the head
// to the first element everytime.
static t_dlst	*append_oplst_insert(int stack_size, int insert_pos, t_dlst *op_lst)
{
	if (insert_pos <= (stack_size / 2 + stack_size % 2) || stack_size < 3)
	{
		while (insert_pos > 0)
		{
			op_lst = add_operation(op_lst, ROT, A);
			if (op_lst == NULL)
				return (NULL);
			insert_pos--;
		}
	}
	else if (insert_pos > (stack_size / 2 + stack_size % 2))
	{
		while (insert_pos < stack_size)
		{
			op_lst = add_operation(op_lst, REVROT, A);
			if (op_lst == NULL)
				return (NULL);
			insert_pos++;
		}
	}
	op_lst = add_operation(op_lst, PUSH, A);
	return (op_lst);
}

// If a malloc fail in an add_operation the current op_lst, the two stack are freed
// and the program exits.
void	store_op_lists(t_dlst *stack_a, t_dlst *stack_b, int size_a, int size_b)
{
	int	insert_pos;
	int	src_pos;
	t_dlst	*op_lst;
	t_dlst	*node;

	node = stack_b;
	src_pos = 1;
	while (node)
	{
		op_lst = get_oplst_totop(src_pos, size_b, B);
		insert_pos = get_insert_pos(node, stack_a);
		op_lst = append_oplst_insert(size_a, insert_pos, op_lst);
		if (op_lst == NULL)
			free_stacks_exit(&stack_a, &stack_b, EXIT_FAILURE);
		if (DEBUG)
		{
			ft_printf(MAG "TEST store_op_lists %d:\n", src_pos);
			print_op_lst(op_lst);
			ft_printf(NORM);
		}
		op_lst = simplify_operations(op_lst);
		((t_elem*)(node->content))->op_lst = op_lst;
		if (DEBUG)
		{
			ft_printf(MAG "TEST store_op_lists simplified %d:\n", src_pos);
			print_op_lst(((t_elem*)(node->content))->op_lst);
			ft_printf(NORM "\n");
		}
		node = node->next;
		if (node == stack_b)
			node = NULL;
		src_pos++;
	}
}
