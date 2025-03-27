/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_cheapest.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:17 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 14:48:19 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

t_dlst	*get_cheapest(t_dlst *stack)
{
	t_dlst	*node;
	t_dlst	*cheapest;
	int	min_len;
	int	tmp_len;

	node = stack;
	cheapest = node;
	min_len = INT_MAX;
	while (node)
	{
		if (get_member_oplst(node))
		{
			tmp_len = ft_dlstsize(get_member_oplst(node));
			if (tmp_len < min_len)
			{
				min_len = tmp_len;
				cheapest = node;
			}
		}
		node = node->next;
		if (node == stack)
			node = NULL;
	}
	return (cheapest);
}

void	free_priciers(t_dlst *stack, t_dlst *cheapest)
{
	t_dlst	*head;
	t_dlst	*op_lst;

	head = stack;
	while (stack)
	{
		op_lst = get_member_oplst(stack);
		if (op_lst != get_member_oplst(cheapest))
		{
			ft_dlstclear(op_lst);
			set_member_oplst(stack, NULL);
		}
		stack = stack->next;
		if (stack == head)
			stack = NULL;
	}
}
