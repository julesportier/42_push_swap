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

static int	find_duplicates(t_dlstip *lst)
{
	t_dlstip	*tail;
	t_dlstip	*tmp_node;

	tail = lst->prev;
	while(lst != tail)
	{
		tmp_node = lst;
		while (tmp_node != tail)
		{
			tmp_node = tmp_node->next;
			if (lst->content[0] == tmp_node->content[0])
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_dlstip	*parse_args(char **argv)
{
	size_t	i;
	t_dlstip	*lst;
	t_dlstip	*node;
	t_iflag	i_flag;
	int	*content;

	i = 0;
	lst = NULL;
	while (argv[++i])
	{
		i_flag = ft_atoi_flag(argv[i]);
		if (i_flag.flag)
			exit_error_free("Error", &lst);
		content = malloc(sizeof(int) * 2);
		if (content == NULL)
			exit_error_free("Error", &lst);
		content[0] = i_flag.i;
		content[1] = 0;
		node = ft_dlstip_new(content);
		ft_cdlstip_add_back(&lst, node);
	}
	if (find_duplicates(lst))
		exit_error_free("Error", &lst);
	return (lst);
}
