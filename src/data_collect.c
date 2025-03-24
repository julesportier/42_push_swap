/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_collect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:15:05 by juportie          #+#    #+#             */
/*   Updated: 2025/03/24 09:22:07 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"

static int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

static int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

t_stack_data	get_stack_data(t_dlst *stack)
{
	t_dlst		*head;
	t_stack_data	data;

	ft_bzero(&data, sizeof(t_stack_data));
	if (stack)
	{
		data = (t_stack_data){
			.max = get_member(stack, "value"), .min = get_member(stack, "value")};
		head = stack;
	}
	while (stack)
	{
		data.max = max(data.max, get_member(stack, "value"));
		data.min = min(data.min, get_member(stack, "value"));
		data.size++;
		stack = stack->next;
		if (stack == head)
			break ;
	}
	return (data);
}

void	store_rank(t_dlst *stack, t_stack_data *data)
{
	t_dlst	*head;
	t_dlst	*min;
	int			i;

	head = stack;
	min = stack;
	i = 1;
	while (i <= data->size)
	{
		stack = head;
		while (get_member(stack, "rank") != -1)
			stack = stack->next;
		min = stack;
		while (1)
		{
			if (get_member(stack, "rank") == -1 && get_member(stack, "value") < get_member(min, "value"))
				min = stack;
			stack = stack->next;
			if (stack == head)
				break ;
		}
		set_member(min, "rank", i);
		i++;
	}
}

// needs data updated to the current state of the stack
void	store_cost(t_dlst *stack, t_stack_data *data)
{
	t_dlst	*head;
	int			i;

	head = stack;
	set_member(stack, "mv_nbr", 1);
	set_member(stack, "cost",
			get_member(stack, "rank") + get_member(stack, "mv_nbr"));
	i = 0;
	while (++i < (data->size / 2 + data->size % 2))
	{
		stack = stack->next;
		set_member(stack, "mv_nbr", 2 * i);
		set_member(stack, "cost",
				get_member(stack, "rank") + get_member(stack, "mv_nbr"));
	}
	i = 0;
	stack = head->prev;
	while (++i < (data->size / 2 + 1))
	{
		set_member(stack, "mv_nbr", 2 * i);
		set_member(stack, "cost",
				get_member(stack, "rank") + get_member(stack, "mv_nbr"));
		stack = stack->prev;
	}
}

// Starts at 0 if insert_pos is top
static int	get_insert_pos(t_dlst *target, t_dlst *src_node)
{
	int	insert_pos;
	t_dlst	*head;

	insert_pos = 0;
	head = target;
	while (get_member(target, "rank") < get_member(src_node, "rank"))
	{
		insert_pos++;
		target = target->next;
		if (target == head)
			break ;
	}
	return (insert_pos);
}

void	store_cost_insert_a(t_dlst *stack_a, t_dlst *stack_b, t_stack_data *data)
{
	int	i;
	t_dlst	*head;
	t_stack_data	data_b;

	data_b = get_stack_data(stack_b);
	store_cost(stack_b, &data_b);
	head = stack_b;
	while (stack_b)
	{
		i = get_insert_pos(stack_a, stack_b);
		if (DEBUG)
			ft_printf("i == %d\n", i);
		// TODO move this to get_top_moves(int	item_place)
		if (i < (data->size / 2 + data->size % 2) && i > 1)
			i = i * 2;
		else if (i >= (data->size / 2 + data->size % 2) && i > 1)
			i = (get_stack_data(stack_a).size - i) * 2;
		// END TODO
		set_member(stack_b, "mv_nbr",
				get_member(stack_b, "mv_nbr")  + i);
		set_member(stack_b, "cost",
				get_member(stack_b, "mv_nbr")
				+ (data->size - get_member(stack_b, "rank")));
		if (stack_b->next != head)
			stack_b = stack_b->next;
		else
			stack_b = NULL;
	}
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(stack_a);
		ft_putendl_fd("stack_b :", 1);
		print_stack(head);
		usleep(USLEEP);
	}
}

// stack != NULL must be checked before calling this function.
// Returns 1 for head, stack size for last.
int	get_value_pos(t_dlst *stack, int value)
{
	int	min_pos;
	t_dlst	*head;

	min_pos = 1;
	head = stack;
	while (get_member(stack, "value") != value)
	{
		min_pos++;
		stack = stack->next;
		if (stack == head)
			break ;
	}
	return (min_pos);
}
