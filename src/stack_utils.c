/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:50:46 by juportie          #+#    #+#             */
/*   Updated: 2025/03/20 17:22:21 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// The four functions above permits to avoid explicit pointer manipulation
// when accessing list members and improve readability.
// e.g.
// (((t_elem *)(node->content))->value);
// become:
// get_member(node, "value")
int	get_member(t_dlst *node, char *member)
{
	if (node == NULL || member == NULL)
		return (-1);
	if (ft_isequalstr("value", member))
		return (((t_elem *)(node->content))->value);
	else if (ft_isequalstr("rank", member))
		return (((t_elem *)(node->content))->rank);
	else
		return (-1);
}

t_dlst	*get_member_oplst(t_dlst *node)
{
	if (node == NULL)
		return (NULL);
	return (((t_elem *)(node->content))->op_lst);
}

int	set_member(t_dlst *node, char *member, int val)
{
	if (node == NULL || member == NULL)
		return (-1);
	if (ft_isequalstr("value", member))
		((t_elem *)(node->content))->value = val;
	else if (ft_isequalstr("rank", member))
		((t_elem *)(node->content))->rank = val;
	else
		return (-1);
	return (0);
}

void	set_member_oplst(t_dlst *node, t_dlst *op_lst)
{
	if (node != NULL)
		((t_elem *)(node->content))->op_lst = op_lst;
}
