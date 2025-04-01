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

t_dlst	*get_oplst_totop(int pos, int stack_size, int source_macro)
{
	t_dlst	*op_lst;

	op_lst = NULL;
	if (pos == 1)
		op_lst = add_operation(op_lst, 0, 0);
	else if (pos <= (stack_size / 2 + stack_size % 2) || (stack_size < 3))
	{
		while (pos-- > 1)
		{
			op_lst = add_operation(op_lst, ROT, source_macro);
			if (op_lst == NULL)
				return (NULL);
		}
	}
	else
	{
		while (pos++ <= stack_size)
		{
			op_lst = add_operation(op_lst, REVROT, source_macro);
			if (op_lst == NULL)
				return (NULL);
		}
	}
	return (op_lst);
}

// This function return the insertion pos to have a sorted circular list,
// the head doesn't necessarly corresponding to the smaller (first) element.
// Return val go from 0 (before top) to dest size - 1 (before end)
// (never push to end, just push to top instead)
static int	get_insert_pos(t_dlst *node, t_dlst *stack_a)
{
	int				pos;
	t_stack_data	data_a;
	t_dlst			*last_a;

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

// Append operation the list of operations
// to "insert" the element to the correct position.
// The list is rotating: the "first" element can be everywhere,
// this permit to avoid doing the rotations to point the head
// to the first element everytime.
static t_dlst	*append_oplst_insert(
	int stack_size, int insert_pos, t_dlst *op_lst)
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

t_dlst	*get_op_list(t_dlst *stack_a, t_pos *src, int size_a, int size_b)
{
	t_dlst	*op_lst;
	int		insert_pos;

	op_lst = NULL;
	op_lst = get_oplst_totop(src->pos, size_b, B);
	if (op_lst == NULL)
		return (NULL);
	insert_pos = get_insert_pos(src->node, stack_a);
	op_lst = append_oplst_insert(size_a, insert_pos, op_lst);
	if (op_lst == NULL)
		return (NULL);
	op_lst = simplify_operations(op_lst);
	return (op_lst);
}

// If a malloc fail in an add_operation the current op_lst,
// the two stack are freed and the program exits.
void	store_op_lists(t_dlst *stack_a, t_dlst *stack_b, int size_a, int size_b)
{
	t_pos	top;
	t_pos	bottom;

	top.node = stack_b;
	top.pos = 1;
	bottom.node = stack_b->prev;
	bottom.pos = size_b;
	while (top.pos <= size_b && top.pos <= CALC_DEPTH)
	{
		set_member_oplst(top.node, get_op_list(stack_a, &top, size_a, size_b));
		if (get_member_oplst(top.node) == NULL)
			free_stacks_exit(&stack_a, &stack_b, EXIT_FAILURE);
		top.node = top.node->next;
		if (top.node == stack_b || top.node == bottom.node)
			break ;
		top.pos++;
		set_member_oplst(
			bottom.node, get_op_list(stack_a, &bottom, size_a, size_b));
		if (get_member_oplst(bottom.node) == NULL)
			free_stacks_exit(&stack_a, &stack_b, EXIT_FAILURE);
		bottom.node = bottom.node->prev;
		if (bottom.node == stack_b || bottom.node == top.node)
			break ;
		bottom.pos--;
	}
}
