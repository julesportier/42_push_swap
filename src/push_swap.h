/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 16:40:50 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/src/libft.h"

// macros for debug
# define DEBUG 1
# define USLEEP 10000
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define NORM "\x1B[0m"

// macros for operations_list
# define PUSH 0b100
# define SWAP 0b1000
# define ROT 0b10000
# define REVROT 0b100000
# define OPERATION 0b111100
# define A 0b1
# define B 0b10
# define BOTH 0b11
# define TARGET 0b11

// TODO
// Use mv_nbr in place of cost, and delete cost member
typedef struct s_elem
{
	int	value;
	int	rank;
	int	mv_nbr;
	int	cost;// THIS MEMBER IS NOT USED ANYMORE
	t_dlst	*op_lst;
}	t_elem;

typedef struct s_stack_data
{
	int	max;
	int	min;
	int	size;
}	t_stack_data;

typedef struct s_pos
{
	int	pos;
	t_dlst	*node;
}	t_pos;

// lst_utils.c
int		get_member(t_dlst *elem, char *member);
int		set_member(t_dlst *elem, char *member, int val);
void		print_stack(t_dlst *stack);
// free_exit.c
void		free_stack(t_dlst **stack);
void		free_stacks_exit(t_dlst **stack_a, t_dlst **stack_b, int status);
void		free_splits(char **splits);
// parsing.c
t_dlst	*parse_args(char **argv);
// data_collect.c
void		store_rank(t_dlst *stack, t_stack_data *data);
t_stack_data	get_stack_data(t_dlst *stack);
// THE TWO FUNCTIONS ABOVE ARE NOT USED ANYMORE
void		store_cost(t_dlst *stack, t_stack_data *data);
void		store_cost_insert_a(t_dlst *stack_a, t_dlst *stack_b, t_stack_data *data);
// END
// operations_list_utils.c
int		get_content(t_dlst *elem);
void		set_content(t_dlst *elem, int operation);
void		print_op_lst(t_dlst *op_lst);
// operations_list_alloc.c
t_dlst		*add_operation(t_dlst *op_lst, int operation_type, int target);
// operations_simplify.c
t_dlst		*simplify_operations(t_dlst *op_lst);
// operations_store.c
void		store_op_lists(t_dlst *stack_a, t_dlst *stack_b);
// stack_operations_utils.c
void		rot(t_dlst **stack);
void		rev_rot(t_dlst **stack);
void		swap(t_dlst **stack);
void		push(t_dlst **target, t_dlst **source);
void		push_push(t_dlst **stack_1, t_dlst **stack_2);
// stack_operations.c
void		s(char name, t_dlst **stack_a, t_dlst **stack_b);
void		p(char name, t_dlst **stack_a, t_dlst **stack_b);
void		r(char name, t_dlst **stack_a, t_dlst **stack_b);
void		rr(char name, t_dlst **stack_a, t_dlst **stack_b);

#endif
