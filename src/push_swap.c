/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/24 14:26:23 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ftpf_printf.h"
#include <stdlib.h>

static int	is_superior(int a, int b)
{
	if (a > b)
		return (1);
	return (0);
}

static int	is_inferior(int a, int b)
{
	if (a < b)
		return (1);
	return (0);
}

static int	is_sorted(t_dlisti *lst, int check(int a, int b))
{
	t_dlisti	*tail;
	t_dlisti	*prev_node;

	tail = lst->prev;
	while(lst != tail)
	{
		prev_node = lst;
		lst = lst->next;
		if (check(prev_node->content, lst->content))
			return (0);
	}
	return (1);
}

static t_stack_data	store_stack_data(t_dlisti *lst)
{
	t_dlisti	*tail;
	t_stack_data	data;

	data = (t_stack_data){.max=lst->content, .min=lst->content, .size=0};
	tail = lst->prev;
	while (1)
	{
		if (lst->content > data.max)
			data.max = lst->content;
		else if (lst->content < data.min)
			data.min = lst->content;
		data.size++;
		if (lst == tail)
			return (data);
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_dlisti	*lst;
	t_stack_data	data;

	if (argc < 2)
		exit(EXIT_FAILURE);
	lst = parse_args(argv);
	ft_print_dlsti(lst);
	if (is_sorted(lst, is_superior))
		ft_putendl_fd("ascending sort", 1);
	if (is_sorted(lst, is_inferior))
		ft_putendl_fd("descending sort", 1);
	data = store_stack_data(lst);
	ft_printf("max == %d\nmin == %d\nsize == %d\n", data.max, data.min, data.size);
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
