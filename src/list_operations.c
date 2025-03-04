/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:15:48 by juportie          #+#    #+#             */
/*   Updated: 2025/02/26 13:17:59 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot(t_dlstip **stack)
{
	if (stack && *stack)
		*stack = (*stack)->next;
}

void	rev_rot(t_dlstip **stack)
{
	if (stack && *stack)
		*stack = (*stack)->prev;
}

void	swap(t_dlstip **stack)
{
	int	tmp;

	if (stack && *stack)
	{
		tmp = (*stack)->content[0];
		(*stack)->content[0] = (*stack)->next->content[0];
		(*stack)->next->content[0] = tmp;
	}
}

void	push(t_dlstip **target, t_dlstip **source)
{
	t_dlstip	*tmp;

	if (target && source && *source)
	{
		(*source)->next->prev = (*source)->prev;
		(*source)->prev->next = (*source)->next;
		if ((*source)->next != *source)
			tmp = (*source)->next;
		else
			tmp = NULL;
		ft_cdlstip_add_front(target, *source);
		*source = tmp;
	}
}

void	push_push(t_dlstip **lst_a, t_dlstip **lst_b)
{
	t_dlstip	*tmp_a;
	t_dlstip	*tmp_b;

	tmp_a = NULL;
	tmp_b = NULL;
	if (lst_a && lst_b && *lst_a && *lst_b)
	{
		push(&tmp_a, lst_a);
		push(&tmp_b, lst_b);
		push(lst_a, &tmp_b);
		push(lst_b, &tmp_a);
	}
}
