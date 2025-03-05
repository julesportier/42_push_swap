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

static int	is_sorted(t_dlstip *lst, int check(int a, int b))
{
	t_dlstip	*tail;
	t_dlstip	*prev_node;

	tail = lst->prev;
	while (lst != tail)
	{
		prev_node = lst;
		lst = lst->next;
		if (check(prev_node->content[0], lst->content[0]))
			return (0);
	}
	return (1);
}

static void	store_pos(t_dlstip *lst, t_stack_data *data)
{
	t_dlstip	*head;
	t_dlstip	*min;
	int			i;

	head = lst;
	min = lst;
	i = 0;
	while (i < data->size)
	{
		lst = head;
		while (lst->content[1] != -1)
			lst = lst->next;
		min = lst;
		while (1)
		{
			if (lst->content[1] == -1 && lst->content[0] < min->content[0])
				min = lst;
			lst = lst->next;
			if (lst == head)
				break ;
		}
		min->content[1] = i;
		i++;
	}
}

static t_stack_data	store_stack_data(t_dlstip *lst)
{
	t_dlstip		*tail;
	t_stack_data	data;

	if (!lst)
	{
		data = (t_stack_data){0, 0, 0};
		return (data);
	}
	data = (t_stack_data){
		.max = lst->content[0], .min = lst->content[0], .size = 0};
	tail = lst->prev;
	while (1)
	{
		if (lst->content[0] > data.max)
			data.max = lst->content[0];
		else if (lst->content[0] < data.min)
			data.min = lst->content[0];
		data.size++;
		if (lst == tail)
			return (data);
		lst = lst->next;
	}
}

// already checked if given sorted, size == 1 or 2
static void	sort_in_place(t_dlstip **lst, t_stack_data *data)
{
	if (data->size == 2)
	{
		ft_putendl_fd("ra", 1);
		return ;
	}
	while (!is_sorted(*lst, is_superior))
	{
		if ((*lst)->content[0] == data->max)
			r('a', lst, NULL);
		else if ((*lst)->prev->content[0] == data->min)
			rr('a', lst, NULL);
		else if ((*lst)->content[0] == data->min)
		{
			rr('a', lst, NULL);
			s('a', lst, NULL);
		}
		else if ((*lst)->next->content[0] == data->min)
			s('a', lst, NULL);
	}
}

static void	sort_stack(t_dlstip **lst, t_stack_data *data)
{
	if (data->size <= 3)
		sort_in_place(lst, data);
	else
		store_pos(*lst, data);
}

int	main(int argc, char **argv)
{
	t_dlstip		*lst;
	t_dlstip		*stack;
	t_stack_data	data;

	if (argc < 2)
		exit(EXIT_FAILURE);
	stack = NULL;
	lst = parse_args(argv);
	print_stack(lst);
	if (is_sorted(lst, is_superior))
	{
		// DEBUG
		ft_putendl_fd("ascending sort", 1);
		// END
		exit(EXIT_SUCCESS);
	}
	data = store_stack_data(lst);
	ft_printf("max == %d\nmin == %d\nsize == %d\n", data.max, data.min, data.size);
	sort_stack(&lst, &data);
	print_stack(lst);
	int	i = 3;
	ft_dlstip_clear(&lst);
	ft_dlstip_clear(&stack);
	//t_dlisti	*new_node = ft_dlstip_new(1);
	//ft_cdlstip_add_back(&lst, new_node);
	//print_stack(lst);
	//t_dlisti	*new_node2 = ft_dlstip_new(2);
	//ft_cdlstip_add_back(&lst, new_node2);
	//print_stack(lst);
	//t_dlisti	*new_node3 = ft_dlstip_new(3);
	//ft_cdlstip_add_back(&lst, new_node3);
	//print_stack(lst);
	exit(EXIT_SUCCESS);
}
