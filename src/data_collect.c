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
void	store_cost_pb(t_dlstip *lst, t_stack_data *data)
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
