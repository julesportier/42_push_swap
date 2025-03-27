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
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"

// The four functions above permits to avoid direct pointer manipulation
// to access list members to improve readability.
// e.g.
// (((t_elem *)(node->content))->value);
// become:
// get_member(node, "value")
int	get_member(t_dlst *node, char *member)
{
	if (node == NULL || member == NULL)
		return (-1);
	if (ft_strncmp("value", member, 5) == 0)
		return (((t_elem *)(node->content))->value);
	else if (ft_strncmp("rank", member, 4) == 0)
		return (((t_elem *)(node->content))->rank);
	else
	{
		ft_putendl_fd("get_member error: wrong member name", 2);
		return (-1);
	}
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
	if (ft_strncmp("value", member, 5) == 0)
		((t_elem *)(node->content))->value = val;
	else if (ft_strncmp("rank", member, 4) == 0)
		((t_elem *)(node->content))->rank = val;
	else
	{
		ft_putendl_fd("get_member error: wrong member name", 2);
		return (-1);
	}
	return (0);
}

void	set_member_oplst(t_dlst *node, t_dlst *op_lst)
{
	((t_elem *)(node->content))->op_lst = op_lst;
}


void	print_stack(t_dlst *lst)
{
	t_dlst	*head;

	head = lst;
	while (lst)
	{
		ft_printf(
			"node %p; next %p; prev %p :: "
			"content->{ value: %d, rank: %d, &op_lst: %p}\n",
			lst, lst->next, lst->prev,
			get_member(lst, "value"),
			get_member(lst, "rank"),
			get_member_oplst(lst)
		);
		if (lst->next == head)
			return ;
		lst = lst->next;
	}
}
