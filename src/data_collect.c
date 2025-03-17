/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_collect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:15:05 by juportie          #+#    #+#             */
/*   Updated: 2025/03/10 09:21:00 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"

static int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

static int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

t_stack_data	get_lst_data(t_dlst *lst)
{
	t_dlst		*head;
	t_stack_data	data;

	ft_bzero(&data, sizeof(t_stack_data));
	if (lst)
	{
		data = (t_stack_data){
			.max = get_member(lst, "value"), .min = get_member(lst, "value")};
		head = lst;
	}
	while (lst)
	{
		data.max = max(data.max, get_member(lst, "value"));
		data.min = min(data.min, get_member(lst, "value"));
		data.size++;
		lst = lst->next;
		if (lst == head)
			break ;
	}
	return (data);
}

void	store_order(t_dlst *lst, t_stack_data *data)
{
	t_dlst	*head;
	t_dlst	*min;
	int			i;

	head = lst;
	min = lst;
	i = 1;
	while (i <= data->size)
	{
		lst = head;
		while (get_member(lst, "order") != -1)
			lst = lst->next;
		min = lst;
		while (1)
		{
			if (get_member(lst, "order") == -1 && get_member(lst, "value") < get_member(min, "value"))
				min = lst;
			lst = lst->next;
			if (lst == head)
				break ;
		}
		set_member(min, "order", i);
		i++;
	}
}

// needs data updated to the current state of the stack
void	store_cost(t_dlst *lst, t_stack_data *data)
{
	t_dlst	*head;
	int			i;

	head = lst;
	set_member(lst, "mv_nbr", 1);
	set_member(lst, "cost",
			get_member(lst, "order") + get_member(lst, "mv_nbr"));
	i = 0;
	while (++i < (data->size / 2 + data->size % 2))
	{
		lst = lst->next;
		set_member(lst, "mv_nbr", 2 * i);
		set_member(lst, "cost",
				get_member(lst, "order") + get_member(lst, "mv_nbr"));
	}
	i = 0;
	lst = head->prev;
	while (++i < (data->size / 2 + 1))
	{
		set_member(lst, "mv_nbr", 2 * i);
		set_member(lst, "cost",
				get_member(lst, "order") + get_member(lst, "mv_nbr"));
		lst = lst->prev;
	}
}

void	store_cost_insert_a(t_dlst *stack_a, t_dlst *stack_b, t_stack_data *data)
{
	int	i;
	t_dlst	*tmp_node;
	t_dlst	*head;
	t_stack_data	data_b;

	data_b = get_lst_data(stack_b);
	store_cost(stack_b, &data_b);
	head = stack_b;
	while (stack_b)
	{
		i = 0;
		tmp_node = stack_a;
		while (get_member(tmp_node, "order") < get_member(stack_b, "order"))
		{
			i++;
			tmp_node = tmp_node->next;
			if (tmp_node == stack_a)
				break ;
		}
		if (DEBUG)
			ft_printf("i == %d\n", i);
		// TODO move this to get_top_moves(int	item_place)
		if (i < (data->size / 2 + data->size % 2) && i > 1)
			i = i * 2;
		else if (i >= (data->size / 2 + data->size % 2) && i > 1)
			i = (get_lst_data(stack_a).size - i) * 2;
		// END TODO
		set_member(stack_b, "mv_nbr",
				get_member(stack_b, "mv_nbr")  + i);
		set_member(stack_b, "cost",
				get_member(stack_b, "mv_nbr")
				+ (data->size - get_member(stack_b, "order")));
		if (stack_b->next != head)
			stack_b = stack_b->next;
		else
			stack_b = NULL;
	}
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(stack_a);
		ft_putendl_fd("stack_b :", 1);
		print_stack(head);
		usleep(USLEEP);
	}
}
