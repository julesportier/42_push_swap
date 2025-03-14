/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:19 by juportie          #+#    #+#             */
/*   Updated: 2025/02/26 13:41:40 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/ft_printf.h"

void	s(char name, t_dlstip **stack_a, t_dlstip **stack_b)
{
	swap(stack_a);
	if (name == 's')
		swap(stack_b);
	ft_printf("s%c\n", name);
}

void	p(char name, t_dlstip **stack_a, t_dlstip **stack_b)
{
	if (name == 'p')
		push_push(stack_a, stack_b);
	else
		push(stack_a, stack_b);
	ft_printf("p%c\n", name);
}

void	r(char name, t_dlstip **stack_a, t_dlstip **stack_b)
{
	rot(stack_a);
	if (name == 'r')
		rot(stack_b);
	ft_printf("r%c\n", name);
}

void	rr(char name, t_dlstip **stack_a, t_dlstip **stack_b)
{
	rev_rot(stack_a);
	if (name == 'r')
		rev_rot(stack_b);
	ft_printf("rr%c\n", name);
}

void	print_stack(t_dlstip *stack)
{
	t_dlstip	*head;
	int			value;
	int			order;
	int			mv_nbr;
	int			cost;

	head = stack;
	while (stack)
	{
		value = stack->content[0];
		order = stack->content[1];
		mv_nbr = stack->content[2];
		cost = stack->content[3];
		ft_printf("node %X; next %X; prev %X; content [%d, order: %d, mv_nbr: %d, cost: %d]\n",
			stack, stack->next, stack->prev, value, order, mv_nbr, cost);
		if (stack->next == head)
			return ;
		stack = stack->next;
	}
}
