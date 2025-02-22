/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/22 13:12:45 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include <stdlib.h>

static int	find_duplicates(t_dlisti *lst)
{
	t_dlisti	*tail;
	t_dlisti	*tmp_node;

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

static t_dlisti	*parse_args(char **argv)
{
	size_t	i;
	t_dlisti	*lst;
	t_dlisti	*node;
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

int	main(int argc, char **argv)
{
	t_dlisti	*lst;

	if (argc < 2)
		exit(EXIT_FAILURE);
	lst = parse_args(argv);
	ft_print_dlsti(lst);
	ft_cdlsti_clear(&lst);
	//t_dlisti	*new_node = ft_dlsti_new(1);
	//ft_cdlsti_add_back(&lst, new_node);
	//ft_print_dlsti(lst);
	//t_dlisti	*new_node2 = ft_dlsti_new(2);
	//ft_cdlsti_add_back(&lst, new_node2);
	//ft_print_dlsti(lst);
	//t_dlisti	*new_node3 = ft_dlsti_new(3);
	//ft_cdlsti_add_back(&lst, new_node3);
	//ft_print_dlsti(lst);
	exit(EXIT_SUCCESS);
}
