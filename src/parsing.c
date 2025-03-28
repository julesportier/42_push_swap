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

static t_dlst	*alloc_element(char *nbr)
{
	t_iflag	i_flag;
	t_dlst	*node;
	t_elem	*content;

	i_flag = ft_atoi_flag(nbr);
	if (i_flag.flag)
	{
		ft_putendl_fd("Error", 2);
		return (NULL);
	}
	content = ft_calloc(1, sizeof(t_elem));
	if (content == NULL)
		return (NULL);
	content->value = i_flag.nbr;
	content->rank = -1;
	node = ft_dlstnew(content);
	return (node);
}

static t_dlst	*add_arg(char *arg, t_dlst **lst)
{
	int		i;
	char	**splits;
	t_dlst	*node;

	i = 0;
	splits = ft_split(arg, ' ');
	if (splits == NULL)
		return (NULL);
	while (splits[i])
	{
		node = alloc_element(splits[i]);
		if (node == NULL)
		{
			ft_cdlstclear(lst);
			free_splits(splits);
			return (NULL);
		}
		ft_cdlstadd_back(lst, node);
		i++;
	}
	free_splits(splits);
	return (*lst);
}

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
	size_t	i;
	t_dlst	*lst;

	i = 0;
	lst = NULL;
	while (argv[++i])
	{
		lst = add_arg(argv[i], &lst);
		if (lst == NULL)
			exit(EXIT_FAILURE);
	}
	if (find_duplicates(lst))
	{
		ft_putendl_fd("Error", 2);
		free_stacks_exit(&lst, NULL, EXIT_FAILURE);
	}
	return (lst);
}
