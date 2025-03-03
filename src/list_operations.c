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

void	rot(t_dlsti **stack)
{
	if (stack && *stack)
		*stack = (*stack)->next;
}

void	rev_rot(t_dlsti **stack)
{
	if (stack && *stack)
		*stack = (*stack)->prev;
}

void	swap(t_dlsti **stack)
{
	int	tmp;

	if (stack && *stack)
	{
		tmp = (*stack)->content;
		(*stack)->content = (*stack)->next->content;
		(*stack)->next->content = tmp;
	}
}

void	push(t_dlsti **target, t_dlsti **source)
{
	t_dlsti	*tmp;

	if (target && source && *source)
	{
		(*source)->next->prev = (*source)->prev;
		(*source)->prev->next = (*source)->next;
		if ((*source)->next != *source)
			tmp = (*source)->next;
		else
			tmp = NULL;
		ft_cdlsti_add_front(target, *source);
		*source = tmp;
	}
}

void	push_push(t_dlsti **lst_a, t_dlsti **lst_b)
{
	t_dlsti	*tmp_a;
	t_dlsti	*tmp_b;

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
