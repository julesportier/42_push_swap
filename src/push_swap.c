/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 16:30:16 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include "../libft/src/ft_printf.h"
#include <stdlib.h>

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
	if (is_sorted(lst))
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
	sort_stacks(&lst, &data);
	if (DEBUG)
	{
		ft_putendl_fd("sorted stack: ", 1);
		print_stack(lst);
	}
	ft_cdlstclear(&lst);
	ft_cdlstclear(&stack);
	exit(EXIT_SUCCESS);
}
