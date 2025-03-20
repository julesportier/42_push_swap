/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:26:20 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 12:20:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"
#include "push_swap.h"
#include "../libft/src/ft_printf.h"

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

static void	print_op(t_dlst *node)
{
	int	content;
	char	*op;
	char	*target;

	if (node == NULL)
		return ;
	content = get_content(node);
	op = "?";
	target = "?";
	if ((content & OPERATION) == PUSH)
		op = "p";
	else if ((content & OPERATION) == SWAP)
		op = "s";
	else if ((content & OPERATION) == ROT)
		op = "r";
	else if ((content & OPERATION) == REVROT)
		op = "rr";
	if ((content & TARGET) == A)
		target = "a";
	else if ((content & TARGET) == B)
		target = "b";
	else if ((content & TARGET) == BOTH)
		target = "both";
	ft_printf("%s, %s\n", op, target);
}

void	print_op_lst(t_dlst *lst)
{
	while (lst)
	{
		print_op(lst);
		lst = lst->next;
	}
}
