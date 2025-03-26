/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/23 17:56:44 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"

int	get_content(t_dlst *node)
{
	if (node)
		return(*(int *)(node->content));
	else
		return (-1);

}

void	set_content(t_dlst *node, int operation)
{
	if (node)
		*(int *)(node->content) = operation;
}

char	*optype_to_str(t_dlst *node)
{
	int	operation;
	char	*op;

	if (node == NULL)
		return (NULL);
	operation = get_content(node);
	if ((operation & TYPE) == PUSH)
		op = "p";
	else if ((operation & TYPE) == SWAP)
		op = "s";
	else if ((operation & TYPE) == ROT)
		op = "r";
	else if ((operation & TYPE) == REVROT)
		op = "rr";
	else if ((operation & TYPE) == 0)
		op = "no_op";
	else
		op = NULL;
	return (op);
}

char	*optarget_to_str(t_dlst *node)
{
	int	operation;
	char	*target;

	if (node == NULL)
		return (NULL);
	operation = get_content(node);
	if ((operation & TARGET) == A)
		target = "a";
	else if ((operation & TARGET) == B)
		target = "b";
	else if ((operation & TARGET) == BOTH)
		target = optype_to_str(node);
	else if ((operation & TARGET) == 0)
		target = "no_tar";
	else
		target = NULL;
	return (target);
}

// The string returned must be freed after use.
// The potential check for NULL node must be did before calling this function.
char	*operation_to_str(t_dlst *node)
{
	char	*operation_str;

	operation_str = ft_strjoin(optype_to_str(node), optarget_to_str(node));
	if (operation_str == NULL)
		return (NULL);
	return (operation_str);
}
