/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/03/24 11:29:24 by juportie         ###   ########.fr       */
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

//static int	is_inferior(int a, int b)
//{
//	if (a < b)
//		return (1);
//	return (0);
//}

static int	is_sorted(t_dlst *stack, int check(int a, int b))
{
	t_dlst	*last;
	t_dlst	*prev_node;

	last = stack->prev;
	while (stack != last)
	{
		prev_node = stack;
		stack = stack->next;
		if (check(get_member(prev_node, "value"), get_member(stack, "value")))
			return (0);
	}
	return (1);
}

// already checked if given sorted, size == 1 or 2
static void	sort_in_place(t_dlst **stack, t_stack_data *data)
{
	if (data->size == 2)
	{
		r('a', stack, NULL);
		return ;
	}
	else if (data->size == 3)
	{
		while (!is_sorted(*stack, is_superior))
		{
			if (get_member(*stack, "rank") == data->max)
				r('a', stack, NULL);
			else if (get_member((*stack)->prev, "rank") == data->min)
				rr('a', stack, NULL);
			else if (get_member(*stack, "rank") == data->min)
			{
				rr('a', stack, NULL);
				s('a', stack, NULL);
			}
			else if (get_member((*stack)->next, "rank") == data->min)
				s('a', stack, NULL);
		}
	}
}

// is_inferior() for stack_a to b and is_superior() for stack_b to a
//static int	get_cheaper_pos(
//	t_dlst *lst, t_stack_data *data, int check(int a, int b))
//{
//	t_dlst	*cheaper;
//	int			i;
//	int			pos;
//
//	pos = 1;
//	i = 1;
//	cheaper = lst;
//	while (i <= data->size)
//	{
//		if (get_member(lst, "cost") <= cheaper->content[3])
//		{
//			if ((get_member(lst, "cost") == cheaper->content[3]
//				&& check(get_member(lst, "rank"), cheaper->content[1]))
//				|| get_member(lst, "cost") != cheaper->content[3])
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
//static t_pos	get_cheaper_pos_pa(t_dlst *stack_b)
//{
//	t_stack_data	data;
//	int			i;
//	t_pos			pos;
//
//	pos.pos = 1;
//	i = 1;
//	pos.node = stack_b;
//	data = get_stack_data(stack_b);
//	while (i <= data.size)
//	{
//		if (get_member(stack_b, "cost") <= get_member(pos.node, "cost"))
//		{
//			if ((get_member(stack_b, "cost") == get_member(pos.node, "cost")
//				&& get_member(stack_b, "rank") > get_member(pos.node, "rank"))
//				|| get_member(stack_b, "cost") != get_member(pos.node, "cost"))
//			{
//				pos.node = stack_b;
//				pos.pos = i;
//			}
//		}
//		stack_b = stack_b->next;
//		i++;
//	}
//	return (pos);
//}

// needs up to date costs
// names contains [source stack name, target stack name]
//static void	push_cheaper(char *names, t_dlst **source, t_dlst **target, int cheaper_pos)
//{
//	t_stack_data data;
//	int		tmp;
//
//	data = get_stack_data(*source);
//	if (DEBUG)
//	{
//		ft_putendl_fd("source :", 1);
//		print_stack(*source);
//		ft_putendl_fd("target :", 1);
//		print_stack(*target);
//		ft_printf("cheaper pos: %d\n", cheaper_pos);
//		usleep(USLEEP);
//	}
//	if (cheaper_pos == 1)
//		p(names[1], target, source);
//	else if (cheaper_pos == 2)
//	{
//		s(names[0], source, NULL);
//		p(names[1], target, source);
//	}
//	else if (cheaper_pos > 2 && cheaper_pos <= (data.size / 2 + data.size % 2))
//	{
//		tmp = cheaper_pos;
//		while (tmp-- > 2)
//			r(names[0], source, NULL);
//		s(names[0], source, NULL);
//		p(names[1], target, source);
//		while (++tmp < cheaper_pos)
//			rr(names[0], source, NULL);
//	}
//	else if (cheaper_pos > 2 && cheaper_pos > (data.size / 2 + data.size % 2))
//	{
//		tmp = data.size;
//		while (tmp >= cheaper_pos)
//		{
//			rr(names[0], source, NULL);
//			tmp--;
//		}
//		p(names[1], target, source);
//		while (++tmp < data.size)
//			r(names[0], source, NULL);
//	}
//}

// start with 1 for top
//static int	get_insert_pos(t_dlst *stack_a, t_dlst *node)
//{
//	int	i;
//
//	i = 0;
//	while (get_member(stack_a, "rank") < get_member(node, "rank")
//		&& i != get_stack_data(stack_a).size)
//	{
//		i++;
//		stack_a = stack_a->next;
//	}
//	return (i + 1);
//}

//static void	insert_pa(t_dlst **stack_a, t_dlst **stack_b, t_stack_data *data)
//{
//	int	insert_pos;
//	int	i;
//	t_pos	pos;
//	//t_stack_data	data_b;
//	t_stack_data	data_a;
//
//	store_cost_insert_a(*stack_a, *stack_b, data);
//	pos = get_cheaper_pos_pa(*stack_b);
//	//data_b = get_lst_data(*stack_b);
//	data_a = get_stack_data(*stack_a);
//	//if (DEBUG)
//	//{
//	//	ft_putendl_fd("insert sort", 1);
//	//	ft_printf("cheaper pos == %d\n", pos.pos);
//	//}
//	//if (DEBUG)
//	//{
//	//	ft_putendl_fd("stack_a :", 1);
//	//	print_stack(*stack_a);
//	//	ft_putendl_fd("stack_b :", 1);
//	//	print_stack(*stack_b);
//	//	usleep(300000);
//	//}
//	insert_pos = get_insert_pos(*stack_a, pos.node);
//	i = insert_pos;
//	if (DEBUG)
//		ft_printf("target == %d\n", insert_pos);
//	if (insert_pos <= (data_a.size / 2 + data_a.size % 2) && insert_pos != 2)
//	{
//		while (--i > 1)
//			r('a', stack_a, NULL);
//	}
//	else if (insert_pos > (data_a.size / 2 + data_a.size % 2) && insert_pos != 2)
//	{
//		while (i++ <= data_a.size)
//			rr('a', stack_a, NULL);
//	}
//	push_cheaper("ba", stack_b, stack_a, pos.pos);
//	if (insert_pos == 2)
//		s('a', stack_a, NULL);
//	else if (insert_pos <= (data_a.size / 2 + data_a.size % 2) && insert_pos > 2)
//	{
//		s('a', stack_a, NULL);
//		while (--insert_pos > 1)
//			rr('a', stack_a, NULL);
//	}
//	else if (insert_pos > (data_a.size / 2 + data_a.size % 2) && insert_pos > 2)
//		while (insert_pos++ <= data_a.size + 1)
//			r('a', stack_a, NULL);
//}

static void	sort_stack(t_dlst **lst, t_stack_data *data)
{
	t_dlst	*stack_b;
	t_stack_data	data_a;
	t_stack_data	data_b;
	int	chunk_size;

	stack_b = NULL;
	//limit = data->size / 2 + data->size % 2;
	store_rank(*lst, data);
	
	// need to fine tune 3 and 5
	// 500 numbers:
	// chunks size 33: w5310 a4745 b4391 (iter500)
	// chunks size 34: w5239 a4707 b4375 (iter500)
	// chunks size 35: w5218 a4675 b4289 (iter500)
	// chunks size 36: w5127 a4644 b4261 (iter500)
	// chunks size 37: w5221 a4616 b4210 (iter500)
	// chunks size 38: w5050 a4585 b4196 (iter500)
	// chunks size 88: w4806 a4296 b3852 (iter500)
	// chunks size 82: w4759 a4295 b3944 (iter500)
	// chunks size 80: w4786 a4287 b3823 (iter500)
	// chunks size 68: w4775 a4276 b3946 (iter500)
	// chunks size 73: w4750 a4275 b3925 (iter500)
	// chunks size 75: w4748 a4273 b3933 (iter500)
	// chunks size 79: w4769 a4269 b3896 (iter500*4)
	// chunks size 78: w4768(4826) A_MEAN|4266.5|(4269, 4262, 4267, 4271, 4263) b3800 (iter500*5)
	// chunks size 77: w4821 A_MEAN|4265.8|(4259, 4266, 4262, 4269, 4273) b3781 (iter500*5)
	// chunks size 76: w4718 A_MEAN|4262.67|(4268, 4258, 4260, 4261, 4268, 4261) b3806 (iter500*6)
	// chunks size 75: w4830 A_MEAN|4267|(4261, 4281, 4264, 4258, 4271) b3820 (iter500*5)
	// chunks size 74: w4745 A_MEAN|4271|(4273, 4271, 4272, 4277, 4262) b3838 (iter500*5)
	// best chunk size for 500 numbers is 76
	// 100 numbers:
	// chunks size 13: W$751 a631 b559 (iter2000)
	// chunks size 53: W$739 a602 b504 (iter2000)
	// chunks size 48: W$715 a598 b514 (iter2000)
	// chunks size 43: W$674 a584 b505 (iter2000)
	// chunks size 41: W$706 a580 b498 (iter2000)
	// chunks size 40: W$696 a579 b494 (iter2000)
	// chunks size 39: W$691 a578 b495 (iter2000)
	// chunks size 38: W$695(1x715) a579 b500 (iter2000*10)
	// chunks size 37: W$693 a577 b486 (iter2000*10)
	// chunks size 36: W$696 a577 b506 (iter2000*6)
	// chunks size 35: W$692 a578 b502 (iter2000*3)
	// chunks size 34: W$710 a578 b504 (iter2000*3)
	// chunks size 33: W$701 a581 b501 (iter2000*3)
	// chunks size 23: W$689 a584 b506 (iter2000)
	// best chunk size for 100 numbers is 37
	// function to get chunk size is f(x) = sqrt(x*10) + 6 (100 -> 37.62; 500 -> 76.71)
	chunk_size = ft_sqrt_floor(data->size * 10) + 6;
	if (DEBUG)
		ft_printf("chunk_size == %d\n", chunk_size);
	presort(lst, &stack_b, chunk_size);
	data_a = get_stack_data(*lst);
	if (!is_sorted(*lst, is_superior))
		sort_in_place(lst, &data_a);
	t_dlst	*main_oplst = NULL;
	while (ft_cdlstsize(stack_b) > 0)
	{
		data_a = get_stack_data(*lst);
		data_b = get_stack_data(stack_b);
		store_op_lists(*lst, stack_b, data_a.size, data_b.size);
		t_dlst	*cheapest = get_cheapest(stack_b);
		free_priciers(stack_b, cheapest);
		apply_operations_list(get_member_oplst(cheapest), lst, &stack_b);
		//main_oplst = join_cheapest_oplst(main_oplst, cheapest);
		ft_dlstclear(get_member_oplst(cheapest));
		set_member_oplst(cheapest, NULL);
	}
	t_dlst	*op_lst = get_final_rotations(*lst);
	apply_final_rotations(op_lst, lst, &stack_b);
	ft_dlstclear(op_lst);
	ft_dlstclear(main_oplst);



		//insert_pa(lst, &stack_b, data);
}

int	main(int argc, char **argv)
{
	t_dlst		*lst;
	t_dlst		*stack;
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
	data = get_stack_data(lst);
	if (DEBUG)
		ft_printf("max == %d\nmin == %d\nsize == %d\n", data.max, data.min, data.size);
	//if (DEBUG)
	//{
	//	t_dlst	*op_lst = add_operation(NULL, PUSH, A);
	//	add_operation(op_lst, PUSH, B);
	//	add_operation(op_lst, SWAP, A);
	//	add_operation(op_lst, SWAP, A);
	//	add_operation(op_lst, SWAP, B);
	//	add_operation(op_lst, SWAP, A);
	//	add_operation(op_lst, ROT, A);
	//	add_operation(op_lst, ROT, A);
	//	add_operation(op_lst, ROT, A);
	//	add_operation(op_lst, ROT, B);
	//	add_operation(op_lst, SWAP, A);
	//	add_operation(op_lst, REVROT, B);
	//	add_operation(op_lst, REVROT, B);
	//	add_operation(op_lst, REVROT, A);
	//	add_operation(op_lst, REVROT, B);
	//	add_operation(op_lst, REVROT, A);
	//	add_operation(op_lst, ROT, A);
	//	add_operation(op_lst, REVROT, A);
	//	add_operation(op_lst, ROT, A);
	//	add_operation(op_lst, REVROT, A);
	//	add_operation(op_lst, ROT, A);
	//	print_op_lst(op_lst);
	//	ft_printf("simplified:\n");
	//	simplify_operations(op_lst);
	//	print_op_lst(op_lst);
	//}
	sort_stack(&lst, &data);
	if (DEBUG)
	{
		ft_putendl_fd("sorted stack: ", 1);
		print_stack(lst);
	}
	ft_cdlstclear(&lst);
	ft_cdlstclear(&stack);
	exit(EXIT_SUCCESS);
}
//
// OBSOLETE
//static char	get_best_pos(t_dlst *stack_a)
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
//static void	move_best(t_dlst **stack_a, t_dlst **stack_b, char best)
//{
//	if (best == 'n')
//		s('a', stack_a, NULL);
//	if (best == 't')
//		rr('a', stack_a, NULL);
//	p('b', stack_b, stack_a);
//}
//
