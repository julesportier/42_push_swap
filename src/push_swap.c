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
	else if (data->size == 3)
	{
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

// TODO
// merge with get_cheaper_pos with function pointer is_superior/is_inferior
static t_pos	get_cheaper_pos_pa(t_dlstip *lst)
{
	t_stack_data	data;
	int			i;
	t_pos			pos;

	pos.pos = 1;
	i = 1;
	pos.node = lst;
	data = get_lst_data(lst);
	while (i <= data.size)
	{
		if (lst->content[3] <= pos.node->content[3])
		{
			if (lst->content[3] == pos.node->content[3]
				&& lst->content[1] > pos.node->content[1]
				|| lst->content[3] != pos.node->content[3])
			{
				pos.node = lst;
				pos.pos = i;
			}
		}
		lst = lst->next;
		i++;
	}
	return (pos);
}

// needs up to date costs
// names contains [source stack name, target stack name]
static void	push_cheaper(char *names, t_dlstip **source, t_dlstip **target)
{
	t_stack_data data;
	int		pos;
	int		tmp;

	data = get_lst_data(*source);
	if (names[0] == 'a')
		pos = get_cheaper_pos(*source, &data);
	else if (names[0] == 'b')
		pos = get_cheaper_pos_pa(*source).pos;
	if (DEBUG)
	{
		ft_putendl_fd("source :", 1);
		print_stack(*source);
		ft_putendl_fd("target :", 1);
		print_stack(*target);
		ft_printf("cheaper pos: %d\n", pos);
		usleep(300000);
	}
	if (pos == 1)
		p(names[1], target, source);
	else if (pos == 2)
	{
		s(names[0], source, NULL);
		p(names[1], target, source);
	}
	else if (pos > 2 && pos <= (data.size / 2 + data.size % 2))
	{
		tmp = pos;
		while (tmp-- > 2)
			r(names[0], source, NULL);
		s(names[0], source, NULL);
		p(names[1], target, source);
		while (++tmp < pos)
			rr(names[0], source, NULL);
	}
	else if (pos > 2 && pos > (data.size / 2 + data.size % 2))
	{
		tmp = data.size;
		while (tmp >= pos)
		{
			rr(names[0], source, NULL);
			tmp--;
		}
		p(names[1], target, source);
		while (++tmp < data.size)
			r(names[0], source, NULL);
	}
}
static void	insert_pa(t_dlstip **stack_a, t_dlstip **stack_b, t_stack_data *data)
{
	int	i;
	int	tmp;
	t_pos	pos;
	t_stack_data	data_b;

	store_cost_insert_a(*stack_a, *stack_b, data);
	pos = get_cheaper_pos_pa(*stack_b);
	data_b = get_lst_data(*stack_b);
	if (DEBUG)
	{
		ft_putendl_fd("insert sort", 1);
		ft_printf("cheaper pos == %d\n", pos.pos);
	}
	if (DEBUG)
	{
		ft_putendl_fd("stack_a :", 1);
		print_stack(*stack_a);
		ft_putendl_fd("stack_b :", 1);
		print_stack(*stack_b);
		usleep(300000);
	}
	i = 0;
	while ((*stack_a)->content[1] < pos.node->content[1])
	{
		i++;
		r('a', stack_a, NULL);
		if (i == get_lst_data(*stack_a).size)
			break ;
	}
	store_cost_insert_a(*stack_a, *stack_b, data);
	push_cheaper("ba", stack_b, stack_a);
	while (i-- > 0)
		rr('a', stack_a, NULL);
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
		data_a = get_lst_data(*lst);
		store_cost(*lst, &data_a);
		push_cheaper("ab", lst, &stack_b);
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
	while (stack_b != NULL)
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

