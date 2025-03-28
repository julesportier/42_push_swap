/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_simplify_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:29:53 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 14:30:32 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_merge_pair(int op_a, int op_b)
{
	if ((op_a & TYPE) == (op_b & TYPE)
		&& (((op_a & TARGET) == A && (op_b & TARGET) == B)
			|| ((op_a & TARGET) == B && (op_b & TARGET) == A)))
	{
		return (1);
	}
	else
		return (0);
}

int	is_del_pair(int op_a, int op_b)
{
	if ((op_a & TARGET) == (op_b & TARGET)
		&& (((op_a & TYPE) == ROT && (op_b & TYPE) == REVROT)
			|| ((op_a & TYPE) == REVROT && (op_b & TYPE) == ROT)
			|| ((op_a & TYPE) == SWAP && (op_b & TYPE) == SWAP)))
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
