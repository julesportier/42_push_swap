/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:23:47 by juportie          #+#    #+#             */
/*   Updated: 2025/02/24 14:26:29 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_duplicates(t_dlst *lst)
{
	t_dlst	*last;
	t_dlst	*tmp_node;

	last = lst->prev;
	while (lst != last)
	{
		tmp_node = lst;
		while (tmp_node != last)
		{
			tmp_node = tmp_node->next;
			if (get_member(lst, "value") == get_member(tmp_node, "value"))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_dlst	*parse_args(char **argv)
{
	size_t		i;
	t_dlst	*lst;
	t_dlst	*node;
	t_iflag		i_flag;
	t_elem			*content;

	i = 0;
	lst = NULL;
	while (argv[++i])
	{
		i_flag = ft_atoi_flag(argv[i]);
		if (i_flag.flag)
			exit_error_free("Error", &lst);
		content = ft_calloc(1, sizeof(t_elem));
		if (content == NULL)
			exit_error_free("Error", &lst);
		content->value = i_flag.i;
		content->order = -1;
		node = ft_dlstnew(content);
		ft_cdlstadd_back(&lst, node);
	}
	if (find_duplicates(lst))
		exit_error_free("Error", &lst);
	return (lst);
}
