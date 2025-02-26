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

static int	find_duplicates(t_dlsti *lst)
{
	t_dlsti	*tail;
	t_dlsti	*tmp_node;

	tail = lst->prev;
	while(1)
	{
		tmp_node = lst;
		while (tmp_node != tail)
		{
			tmp_node = tmp_node->next;
			if (lst->content == tmp_node->content)
				return (1);
		}
		if (lst == tail)
			return (0);
		lst = lst->next;
	}
}

t_dlsti	*parse_args(char **argv)
{
	size_t	i;
	t_dlsti	*lst;
	t_dlsti	*node;
	t_iflag	i_flag;

	i = 0;
	lst = NULL;
	while (argv[++i])
	{
		i_flag = ft_atoi_flag(argv[i]);
		if (i_flag.flag)
			exit_error_free("Error", &lst);
		node = ft_dlsti_new(i_flag.i);
		ft_cdlsti_add_back(&lst, node);
	}
	if (find_duplicates(lst))
		exit_error_free("Error", &lst);
	return (lst);
}
