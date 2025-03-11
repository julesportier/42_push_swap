/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/03/10 10:36:42 by juportie         ###   ########.fr       */
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

static int	get_cheaper_pos(t_dlstip *lst, t_stack_data *data)
{
	t_dlstip	*cheaper;
	int			i;
	int			pos;

	pos = 1;
	i = 1;
	cheaper = lst;
	while (i <= data->size)
	{
		if (lst->content[3] <= cheaper->content[3])
		{
			if (lst->content[3] == cheaper->content[3]
				&& lst->content[1] < cheaper->content[1]
				|| lst->content[3] != cheaper->content[3])
			{
				cheaper = lst;
				pos = i;
			}
		}
		lst = lst->next;
		i++;
	}
	return (pos);
}

static void	push_cheaper_b(t_dlstip **stack_a, t_dlstip **stack_b)
{
	t_stack_data data;
	int		pos;
	int		tmp;

	data = get_lst_data(*stack_a);
	store_cost(*stack_a, &data);
	pos = get_cheaper_pos(*stack_a, &data);
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(*stack_a);
		ft_putendl_fd("stack_b :", 1);
		print_stack(*stack_b);
		ft_printf("cheaper pos: %d\n", pos);
		usleep(300000);
	}
	if (pos == 1)
		p('b', stack_b, stack_a);
	else if (pos == 2)
	{
		s('a', stack_a, NULL);
		p('b', stack_b, stack_a);
	}
	else if (pos > 2 && pos <= (data.size / 2 + data.size % 2))
	{
		tmp = pos;
		while (tmp-- > 2)
			r('a', stack_a, NULL);
		s('a', stack_a, NULL);
		p('b', stack_b, stack_a);
		while (++tmp < pos)
			rr('a', stack_a, NULL);
	}
	else if (pos > 2 && pos > (data.size / 2 + data.size % 2))
	{
		tmp = data.size;
		while (tmp >= pos)
		{
			rr('a', stack_a, NULL);
			tmp--;
		}
		p('b', stack_b, stack_a);
		while (++tmp < data.size)
			r('a', stack_a, NULL);
	}
}

// TODO
// merge with get_cheaper_pos with function pointer is_superior/is_inferior
static int	get_cheaper_pos_pa(t_dlstip *lst)
{
	t_stack_data	data;
	t_dlstip	*cheaper;
	int			i;
	int			pos;

	pos = 1;
	i = 1;
	cheaper = lst;
	data = get_lst_data(lst);
	while (i <= data.size)
	{
		if (lst->content[3] <= cheaper->content[3])
		{
			if (lst->content[3] == cheaper->content[3]
				&& lst->content[1] > cheaper->content[1]
				|| lst->content[3] != cheaper->content[3])
			{
				cheaper = lst;
				pos = i;
			}
		}
		lst = lst->next;
		i++;
	}
	return (pos);
}

static void	insert_pa(t_dlstip **stack_a, t_dlstip **stack_b, t_stack_data *data)
{
	int	i;

	if (DEBUG)
		ft_putendl_fd("insert sort", 1);
	while (*stack_b != NULL)
	{
		i = 0;
		while ((*stack_a)->content[1] < (*stack_b)->content[1])
		{
			i++;
			r('a', stack_a, NULL);
		}
		p('a', stack_a, stack_b);
		while (i-- > 0)
			rr('a', stack_a, NULL);
		if (DEBUG)
		{
			ft_putendl_fd("stack_a :", 1);
			print_stack(*stack_a);
			ft_putendl_fd("stack_b :", 1);
			print_stack(*stack_b);
			usleep(300000);
		}
	}
}

static void	sort_stack(t_dlstip **lst, t_stack_data *data)
{
	t_dlstip	*stack_b;
	t_stack_data	data_a;
	//int			limit;

	stack_b = NULL;
	//limit = data->size / 2 + data->size % 2;
	store_order(*lst, data);
	data_a = get_lst_data(*lst);
	while (*lst && (get_lst_data(*lst).size > 3)
		&& !(is_sorted(*lst, is_superior) && is_sorted(stack_b, is_inferior)
			&& (get_lst_data(*lst).min < get_lst_data(stack_b).max))
	)
	{
		push_cheaper_b(lst, &stack_b);
	}
	data_a = get_lst_data(*lst);
	if (DEBUG)
		ft_printf("max == %d; min == %d; size == %d\n", data_a.max, data_a.min, data_a.size);
	sort_in_place(lst, &data_a);
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(*lst);
		ft_putendl_fd("stack_b :", 1);
		print_stack(stack_b);
	}
	insert_pa(lst, &stack_b, data);
}

int	main(int argc, char **argv)
{
	t_dlstip		*lst;
	t_dlstip		*stack;
	t_stack_data	data;

	if (argc < 2)
		exit(EXIT_FAILURE);
	stack = NULL;
	// TODO
	// add split on arguments to allow: (a b c), ("a b c") and (a "b c")...
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
// OBSOLETE
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

// OBSOLETE
static void	move_best(t_dlstip **stack_a, t_dlstip **stack_b, char best)
{
	if (best == 'n')
		s('a', stack_a, NULL);
	if (best == 't')
		rr('a', stack_a, NULL);
	p('b', stack_b, stack_a);
}

