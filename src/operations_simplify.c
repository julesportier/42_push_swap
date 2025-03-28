/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_simplify.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:18:17 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 14:30:19 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_merge_pair_size(t_dlst *op_lst)
{
	int		i;
	t_dlst	*begin;
	t_dlst	*end;

	i = 0;
	begin = op_lst;
	end = op_lst->next;
	while (is_merge_pair(get_operation(begin), get_operation(end)))
	{
		i++;
		begin = begin->prev;
		if (begin == NULL)
			return (i);
		end = end->next;
		if (end == NULL)
			return (i);
	}
	return (i);
}

static t_dlst	*simplify_merge_pair(t_dlst *op_lst)
{
	int	pairs;
	int	i;

	pairs = get_merge_pair_size(op_lst);
	i = pairs;
	while (--i > 0)
		op_lst = op_lst->prev;
	i = pairs;
	while (i-- > 0)
	{
		set_operation(op_lst, (get_operation(op_lst) & TYPE) | BOTH);
		ft_dlstremove(&(op_lst->next));
		op_lst = op_lst->next;
	}
	return (op_lst);
}

static t_dlst	*simplify_del_pair(t_dlst *op_lst)
{
	t_dlst	*temp;

	temp = op_lst;
	if (op_lst->prev != NULL)
		op_lst = op_lst->prev;
	else
		op_lst = op_lst->next->next;
	ft_dlstremove(&(temp->next));
	ft_dlstremove(&temp);
	return (op_lst);
}

t_dlst	*simplify_operations(t_dlst *op_lst)
{
	t_dlst	*temp;

	while (op_lst != NULL && op_lst->next != NULL)
	{
		if (get_operation(op_lst) == 0)
		{
			temp = op_lst;
			op_lst = op_lst->next;
			ft_dlstremove(&temp);
		}
		else if (!is_pair(get_operation(op_lst), get_operation(op_lst->next)))
			op_lst = op_lst->next;
		else if (
			is_merge_pair(get_operation(op_lst), get_operation(op_lst->next)))
			op_lst = simplify_merge_pair(op_lst);
		else if (
			is_del_pair(get_operation(op_lst), get_operation(op_lst->next)))
			op_lst = simplify_del_pair(op_lst);
	}
	return (ft_dlsthead(op_lst));
}
