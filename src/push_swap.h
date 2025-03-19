/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/03/19 10:25:13 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/src/libft.h"

# define DEBUG 1
# define USLEEP 10000

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

typedef struct s_elem
{
	int	value;
	int	rank;
	int	mv_nbr;
	int	cost;
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
int		get_member(t_dlst *node, char *member);
int		set_member(t_dlst *node, char *member, int val);
void		print_stack(t_dlst *lst);
// error.c
void		free_exit(t_dlst **lst, int status);
void		free_splits(char **splits);
// parsing.c
t_dlst	*parse_args(char **argv);
// data_collect.c
void		store_rank(t_dlst *lst, t_stack_data *data);
t_stack_data	get_lst_data(t_dlst *lst);
void		store_cost(t_dlst *lst, t_stack_data *data);
void		store_cost_insert_a(t_dlst *stack_a, t_dlst *stack_b, t_stack_data *data);
// operations_list.c
t_dlst		*add_operation(t_dlst *op_lst, int operation_type, int target);
void		print_op_lst(t_dlst *lst);
// operations_simplify_utils.c
int		is_merge_pair(int op_a, int op_b);
int		is_del_pair(int op_a, int op_b);
int		is_pair(int op_a, int op_b);
// list_operations.c
void		rot(t_dlst **stack);
void		rev_rot(t_dlst **stack);
void		swap(t_dlst **stack);
void		push(t_dlst **target, t_dlst **source);
void		push_push(t_dlst **lst_a, t_dlst **lst_b);
// stack_operations.c
void		s(char name, t_dlst **stack_a, t_dlst **stack_b);
void		p(char name, t_dlst **stack_a, t_dlst **stack_b);
void		r(char name, t_dlst **stack_a, t_dlst **stack_b);
void		rr(char name, t_dlst **stack_a, t_dlst **stack_b);

#endif
