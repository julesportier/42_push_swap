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

t_stack_data	get_lst_data(t_dlstip *lst)
{
	t_dlstip		*head;
	t_stack_data	data;

	if (lst)
	{
		data = (t_stack_data){
			.max = lst->content[0], .min = lst->content[0], .size = 0};
		head = lst;
	}
	else
		data = (t_stack_data){0, 0, 0};
	while (lst)
	{
		if (lst->content[0] > data.max)
			data.max = lst->content[0];
		else if (lst->content[0] < data.min)
			data.min = lst->content[0];
		data.size++;
		lst = lst->next;
		if (lst == head)
			break ;
	}
	return (data);
}

void	store_order(t_dlstip *lst, t_stack_data *data)
{
	t_dlstip	*head;
	t_dlstip	*min;
	int			i;

	head = lst;
	min = lst;
	i = 1;
	while (i <= data->size)
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

// needs data updated to the current state of the stack
void	store_cost(t_dlstip *lst, t_stack_data *data)
{
	t_dlstip	*head;
	int			i;

	head = lst;
	lst->content[2] = 1;
	lst->content[3] = lst->content[1] + lst->content[2];
	i = 0;
	while (++i < (data->size / 2 + data->size % 2))
	{
		lst = lst->next;
		lst->content[2] = 2 * i;
		lst->content[3] = lst->content[1] + lst->content[2];
	}
	i = 0;
	lst = head->prev;
	while (++i < (data->size / 2 + 1))
	{
		lst->content[2] = 2 * i;
		lst->content[3] = lst->content[1] + lst->content[2];
		lst = lst->prev;
	}
}

void	store_cost_insert_a(t_dlstip *stack_a, t_dlstip *stack_b, t_stack_data *data)
{
	int	i;
	t_dlstip	*tmp_node;
	t_dlstip	*head;
	t_stack_data	data_b;

	data_b = get_lst_data(stack_b);
	store_cost(stack_b, &data_b);
	head = stack_b;
	while (stack_b)
	{
		i = 0;
		tmp_node = stack_a;
		while (tmp_node->content[1] < stack_b->content[1])
		{
			i++;
			tmp_node = tmp_node->next;
			if (tmp_node == stack_a)
				break ;
		}
		if (DEBUG)
			ft_printf("i == %d\n", i);
		if (i < (data->size / 2 + data->size % 2) && i > 1)
			i = i * 2;
		else if (i >= (data->size / 2 + data->size % 2) && i > 1)
			i = (get_lst_data(stack_a).size - i) * 2;
		stack_b->content[2] += i;
		stack_b->content[3] = stack_b->content[2] + (data->size - stack_b->content[1]);
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
