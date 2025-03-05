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

static void	store_order(t_dlstip *lst, t_stack_data *data)
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

static t_stack_data	get_lst_data(t_dlstip *lst)
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

static char	get_best_pos(t_dlstip *stack_a)
{
	int	tmp;
	char	pos;

	tmp = stack_a->content[1];
	pos = 'h';
	if (stack_a->next->content[1] < tmp)
	{
		tmp = stack_a->next->content[1];
		pos = 'n';
	}
	if (stack_a->prev->content[1] < tmp)
	{
		tmp = stack_a->prev->content[1];
		pos = 't';
	}
	return (pos);
}

static void	move_best(t_dlstip **stack_a, t_dlstip **stack_b, char best)
{
	if (best == 'n')
		s('a', stack_a, NULL);
	if (best == 't')
		rr('a', stack_a, NULL);
	p('b', stack_b, stack_a);
}

static void	sort_b_in_place(t_dlstip **stack_b)
{
	int	value;
	t_dlstip *tmp;
	t_stack_data data;

	data = get_lst_data(*stack_b);
	tmp = *stack_b;
	if (!is_sorted(*stack_b, is_inferior))
	{
		if ((*stack_b)->next->content[0] == data.min)
			s('b', stack_b, NULL);
		if ((*stack_b)->content[0] == data.min)
			r('b', stack_b, NULL);
		if ((*stack_b)->next->content[0] == data.max)
			s('b', stack_b, NULL);
		if ((*stack_b)->content[0] < (*stack_b)->next->content[0])
			s('b', stack_b, NULL);
	}
}

static void	sort_stack(t_dlstip **lst, t_stack_data *data)
{
	t_dlstip		*stack_b;
	//int			limit;

	stack_b = NULL;
	//limit = data->size / 2 + data->size % 2;
	store_order(*lst, data);
	if (DEBUG)
	{
		ft_putendl_fd("lst :", 1);
		print_stack(*lst);
	}
	while (
		*lst
		&& (get_lst_data(*lst).size > 3
			|| (get_lst_data(*lst).min < get_lst_data(stack_b).max))
		&& (!is_sorted(*lst, is_superior) || !is_sorted(stack_b, is_inferior))
	)
	{
		move_best(lst, &stack_b, get_best_pos(*lst));
		if (DEBUG)
		{
			ft_putendl_fd("stack_a :", 1);
			print_stack(*lst);
			ft_putendl_fd("stack_b :", 1);
			print_stack(stack_b);
			usleep(300000);
		}
		sort_b_in_place(&stack_b);
		if (DEBUG)
		{
			ft_putendl_fd("stack_b after in place sort :", 1);
			print_stack(stack_b);
			usleep(300000);
		}
	}
	*data = get_lst_data(*lst);
	if (DEBUG)
		ft_printf("max == %d; min == %d; size == %d\n", data->max, data->min, data->size);
	sort_in_place(lst, data);
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(*lst);
		ft_putendl_fd("stack_b :", 1);
		print_stack(stack_b);
	}
	while (get_lst_data(stack_b).size > 0)
	{
		p('b', lst, &stack_b);
		if (DEBUG)
		{
			ft_putendl_fd("stack_a :", 1);
			print_stack(*lst);
			ft_putendl_fd("stack_b :", 1);
			print_stack(stack_b);
		}
	}
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
	if (DEBUG)
		print_stack(lst);
	if (is_sorted(lst, is_superior))
	{
		if (DEBUG)
			ft_putendl_fd("ascending sort", 1);
		exit(EXIT_SUCCESS);
	}
	data = get_lst_data(lst);
	if (DEBUG)
		ft_printf("max == %d\nmin == %d\nsize == %d\n", data.max, data.min, data.size);
	sort_stack(&lst, &data);
	//print_stack(lst);
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
//static int	get_lst_size(t_dlstip *lst)
//{
//	t_dlstip	*tail;
//	int			size;
//
//	if (lst)
//		tail = lst->prev;
//	size = 0;
//	while (lst)
//	{
//		size++;
//		if (lst == tail)
//			lst = NULL;
//		else
//			lst = lst->next;
//	}
//	return (size);
//}
//
