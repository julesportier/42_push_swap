/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_simplify.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:18:17 by juportie          #+#    #+#             */
/*   Updated: 2025/03/23 16:58:15 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Doesn't handle "pp" as it can only be usefull
// if pushing alternatively from one stack to another.
// e.g. [rb, pb, rrb, pa] or [ra, pa, rra, pb]
static int	is_merge_pair(int op_a, int op_b)
{
	if ((op_a & TYPE) == (op_b & TYPE)
		&& (op_a & TYPE) != PUSH
		&& (((op_a & TARGET) == A && (op_b & TARGET) == B)
		|| ((op_a & TARGET) == B && (op_b & TARGET) == A)))
	{
		return (1);
	}
	else
		return (0);
}

static int	is_del_pair(int op_a, int op_b)
{
	if ((op_a & TARGET) == (op_b & TARGET) &&
		(((op_a & TYPE) == ROT && (op_b & TYPE) == REVROT)
		|| ((op_a & TYPE) == REVROT && (op_b & TYPE) == ROT)
		|| ((op_a & TYPE) == SWAP && (op_b & TYPE) == SWAP)))
	{
		return (1);
	}
	else
		return (0);
}

static int	is_pair(int op_a, int op_b)
{
	if (is_merge_pair(op_a, op_b) || is_del_pair(op_a, op_b))
		return (1);
	else
		return (0);
}

t_dlst	*simplify_operations(t_dlst *op_lst)
{
	t_dlst	*temp;

	while (op_lst != NULL && op_lst->next != NULL)
	{
		if (get_content(op_lst) == 0)
		{
			temp = op_lst;
			op_lst = op_lst->next;
			ft_dlstremove(&temp);
		}
		else if (!is_pair(get_content(op_lst), get_content(op_lst->next)))
			op_lst = op_lst->next;
		else if (is_merge_pair(get_content(op_lst), get_content(op_lst->next)))
		{
			set_content(op_lst, (get_content(op_lst) & TYPE) | BOTH);
			ft_dlstremove(&(op_lst->next));
			op_lst = op_lst->next;
		}
		else if (is_del_pair(get_content(op_lst), get_content(op_lst->next)))
		{
			temp = op_lst;
			op_lst = op_lst->next->next;
			ft_dlstremove(&(temp->next));
			ft_dlstremove(&temp);
		}
	}
	op_lst = ft_dlsthead(op_lst);
	return (op_lst);
}
