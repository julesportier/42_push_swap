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
	t_dlst			*head;
	t_stack_data	data;

	ft_bzero(&data, sizeof(t_stack_data));
	if (stack)
	{
		data = (t_stack_data){
			.max = get_member(stack, "rank"), .min = get_member(stack, "rank")};
		head = stack;
	}
	while (stack)
	{
		data.max = max(data.max, get_member(stack, "rank"));
		data.min = min(data.min, get_member(stack, "rank"));
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
	int		i;

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
			if (get_member(stack, "rank") == -1
				&& get_member(stack, "value") < get_member(min, "value"))
				min = stack;
			stack = stack->next;
			if (stack == head)
				break ;
		}
		set_member(min, "rank", i);
		i++;
	}
}

// stack != NULL must be checked before calling this function.
// Returns 1 for head, stack size for last.
int	get_rank_pos(t_dlst *stack, int rank)
{
	int		rank_pos;
	t_dlst	*head;

	rank_pos = 1;
	head = stack;
	while (get_member(stack, "rank") != rank)
	{
		rank_pos++;
		stack = stack->next;
		if (stack == head)
			break ;
	}
	return (rank_pos);
}
