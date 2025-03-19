/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_simplify_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:18:17 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 10:23:27 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_merge_pair(int op_a, int op_b)
{
	if ((op_a & OPERATION) == (op_b & OPERATION) &&
		(((op_a & TARGET) == A && (op_b & TARGET) == B)
		|| ((op_a & TARGET) == B && (op_b & TARGET) == A)))
	{
		return (1);
	}
	else
		return (0);
}

int	is_del_pair(int op_a, int op_b)
{
	if ((op_a & TARGET) == (op_b & TARGET) &&
		(((op_a & OPERATION) == ROT && (op_b & OPERATION) == REVROT)
		|| ((op_a & OPERATION) == REVROT && (op_b & OPERATION) == ROT)))
	{
		return (1);
	}
	else
		return (0);
}

int	is_pair(int op_a, int op_b)
{
	if (is_merge_pair(op_a, op_b) || is_del_pair(op_a, op_b))
		return (1);
	else
		return (0);
}
