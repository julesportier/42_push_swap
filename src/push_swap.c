/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/26 13:21:59 by juportie         ###   ########.fr       */
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

static int	is_sorted(t_dlsti *lst, int check(int a, int b))
{
	t_dlsti	*tail;
	t_dlsti	*prev_node;

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

static t_stack_data	store_stack_data(t_dlsti *lst)
{
	t_dlsti	*tail;
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

// already checked if given sorted, size == 1 or 2
static void	sort_in_place(t_dlsti **lst, t_stack_data *data)
{
	if (data->size == 2)
	{
		ft_putendl_fd("ra", 1);
		return ;
	}
	while (!is_sorted(*lst, is_superior))
	{
		if ((*lst)->content == data->max)
			r('a', lst, NULL);
		else if ((*lst)->prev->content == data->min)
			rr('a', lst, NULL);
		else if ((*lst)->content == data->min)
		{
			rr('a', lst, NULL);
			s('a', lst, NULL);
		}
		else if ((*lst)->next->content == data->min)
			s('a', lst, NULL);
	}
}

static void	sort_stack(t_dlsti **lst, t_stack_data *data)
{
	if (data->size <= 3)
		sort_in_place(lst, data);
}

int	main(int argc, char **argv)
{
	t_dlsti	*lst;
	t_stack_data	data;

	if (argc < 2)
		exit(EXIT_FAILURE);
	lst = parse_args(argv);
	ft_print_dlsti(lst);
	if (is_sorted(lst, is_superior))
	{
		ft_putendl_fd("ascending sort", 1);
		exit(EXIT_SUCCESS);
	}
	data = store_stack_data(lst);
	ft_printf("max == %d\nmin == %d\nsize == %d\n", data.max, data.min, data.size);
	sort_stack(&lst, &data);
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
