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
#include "../libft/src/ft_printf.h"
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
	t_dlstip	*last;
	t_dlstip	*prev_node;

	last = lst->prev;
	while (lst != last)
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
		r('a', lst, NULL);
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

// is_inferior() for stack_a to b and is_superior() for stack_b to a
//static int	get_cheaper_pos(
//	t_dlstip *lst, t_stack_data *data, int check(int a, int b))
//{
//	t_dlstip	*cheaper;
//	int			i;
//	int			pos;
//
//	pos = 1;
//	i = 1;
//	cheaper = lst;
//	while (i <= data->size)
//	{
//		if (lst->content[3] <= cheaper->content[3])
//		{
//			if ((lst->content[3] == cheaper->content[3]
//				&& check(lst->content[1], cheaper->content[1]))
//				|| lst->content[3] != cheaper->content[3])
//			{
//				cheaper = lst;
//				pos = i;
//			}
//		}
//		lst = lst->next;
//		i++;
//	}
//	return (pos);
//}

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
			if ((lst->content[3] == pos.node->content[3]
				&& lst->content[1] > pos.node->content[1])
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
static void	push_cheaper(char *names, t_dlstip **source, t_dlstip **target, int cheaper_pos)
{
	t_stack_data data;
	int		tmp;

	data = get_lst_data(*source);
	if (DEBUG)
	{
		ft_putendl_fd("source :", 1);
		print_stack(*source);
		ft_putendl_fd("target :", 1);
		print_stack(*target);
		ft_printf("cheaper pos: %d\n", cheaper_pos);
		usleep(USLEEP);
	}
	if (cheaper_pos == 1)
		p(names[1], target, source);
	else if (cheaper_pos == 2)
	{
		s(names[0], source, NULL);
		p(names[1], target, source);
	}
	else if (cheaper_pos > 2 && cheaper_pos <= (data.size / 2 + data.size % 2))
	{
		tmp = cheaper_pos;
		while (tmp-- > 2)
			r(names[0], source, NULL);
		s(names[0], source, NULL);
		p(names[1], target, source);
		while (++tmp < cheaper_pos)
			rr(names[0], source, NULL);
	}
	else if (cheaper_pos > 2 && cheaper_pos > (data.size / 2 + data.size % 2))
	{
		tmp = data.size;
		while (tmp >= cheaper_pos)
		{
			rr(names[0], source, NULL);
			tmp--;
		}
		p(names[1], target, source);
		while (++tmp < data.size)
			r(names[0], source, NULL);
	}
}

// start with 1 for top
static int	get_insert_pos(t_dlstip *stack_a, t_dlstip *node)
{
	int	i;

	i = 0;
	while (stack_a->content[1] < node->content[1]
		&& i != get_lst_data(stack_a).size)
	{
		i++;
		stack_a = stack_a->next;
	}
	return (i + 1);
}

static void	insert_pa(t_dlstip **stack_a, t_dlstip **stack_b, t_stack_data *data)
{
	int	insert_pos;
	int	i;
	t_pos	pos;
	//t_stack_data	data_b;
	t_stack_data	data_a;

	store_cost_insert_a(*stack_a, *stack_b, data);
	pos = get_cheaper_pos_pa(*stack_b);
	//data_b = get_lst_data(*stack_b);
	data_a = get_lst_data(*stack_a);
	//if (DEBUG)
	//{
	//	ft_putendl_fd("insert sort", 1);
	//	ft_printf("cheaper pos == %d\n", pos.pos);
	//}
	//if (DEBUG)
	//{
	//	ft_putendl_fd("stack_a :", 1);
	//	print_stack(*stack_a);
	//	ft_putendl_fd("stack_b :", 1);
	//	print_stack(*stack_b);
	//	usleep(300000);
	//}
	insert_pos = get_insert_pos(*stack_a, pos.node);
	i = insert_pos;
	if (DEBUG)
		ft_printf("target == %d\n", insert_pos);
	if (insert_pos <= (data_a.size / 2 + data_a.size % 2) && insert_pos != 2)
	{
		while (--i > 1)
			r('a', stack_a, NULL);
	}
	else if (insert_pos > (data_a.size / 2 + data_a.size % 2) && insert_pos != 2)
	{
		while (i++ <= data_a.size)
			rr('a', stack_a, NULL);
	}
	push_cheaper("ba", stack_b, stack_a, pos.pos);
	if (insert_pos == 2)
		s('a', stack_a, NULL);
	else if (insert_pos <= (data_a.size / 2 + data_a.size % 2) && insert_pos > 2)
	{
		s('a', stack_a, NULL);
		while (--insert_pos > 1)
			rr('a', stack_a, NULL);
	}
	else if (insert_pos > (data_a.size / 2 + data_a.size % 2) && insert_pos > 2)
		while (insert_pos++ <= data_a.size + 1)
			r('a', stack_a, NULL);
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
		//push_cheaper("ab", lst, &stack_b, get_cheaper_pos(*lst, &data_a, is_inferior));
		// it's cheaper to just push to b directly...
		p('b', &stack_b, lst);
		// More cheaper, just for exemple :
		//if ((*lst)->content[1] < data->size / 2)
		//{
		//	p('b', &stack_b, lst);
		//	r('b', &stack_b, NULL);
		//}
		//else
		//	p('b', &stack_b, lst);
	}
	data_a = get_lst_data(*lst);
	if (DEBUG)
		ft_printf("max == %d; min == %d; size == %d\n", data_a.max, data_a.min, data_a.size);
	if (!is_sorted(*lst, is_superior))
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
	if (DEBUG)
	{
		ft_putendl_fd("sorted stack: ", 1);
		print_stack(lst);
	}
	//int	i = 3;
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
//	t_dlstip	*last;
//	int			size;
//
//	if (lst)
//		last = lst->prev;
//	size = 0;
//	while (lst)
//	{
//		size++;
//		if (lst == last)
//			lst = NULL;
//		else
//			lst = lst->next;
//	}
//	return (size);
//}
//
// OBSOLETE
//static char	get_best_pos(t_dlstip *stack_a)
//{
//	int	tmp;
//	char	pos;
//
//	tmp = stack_a->content[1];
//	pos = 'h';
//	if (stack_a->next->content[1] < tmp)
//	{
//		tmp = stack_a->next->content[1];
//		pos = 'n';
//	}
//	if (stack_a->prev->content[1] < tmp)
//	{
//		tmp = stack_a->prev->content[1];
//		pos = 't';
//	}
//	return (pos);
//}
//
//// OBSOLETE
//static void	move_best(t_dlstip **stack_a, t_dlstip **stack_b, char best)
//{
//	if (best == 'n')
//		s('a', stack_a, NULL);
//	if (best == 't')
//		rr('a', stack_a, NULL);
//	p('b', stack_b, stack_a);
//}
//
