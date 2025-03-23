/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_cheapest.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:17 by juportie          #+#    #+#             */
/*   Updated: 2025/03/23 18:30:02 by juportie         ###   ########.fr       */
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
		tmp_len = ft_dlstsize(get_member_oplst(stack));
		if (tmp_len < min_len)
		{
			min_len = tmp_len;
			cheapest = node;
		}
		node = node->next;
		if (node == stack)
			node = NULL;
	}
	return (cheapest);
}

void	free_priciers(t_dlst *stack, t_dlst *cheapest)
{
	t_dlst	*node;
	t_dlst	*op_lst;

	node = stack;
	while (node)
	{
		op_lst = get_member_oplst(stack);
		if (op_lst != get_member_oplst(cheapest))
		{
			ft_dlstclear(op_lst);
			set_member_oplst(stack, NULL);
		}
		node = node->next;
		if (node == stack)
			node = NULL;
	}
}

t_dlst	*merge_op_lsts(t_dlst *main_oplst, t_dlst *cheapest_oplst)
{
	if (main_oplst)
		main_oplst->next = cheapest_oplst;
	else
		main_oplst = cheapest_oplst;
	return (main_oplst);
}
