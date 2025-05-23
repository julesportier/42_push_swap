/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 17:06:12 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/src/libft.h"

# define CALC_DEPTH 25
// operations_list flags and masks
# define PUSH 0b100
# define SWAP 0b1000
# define ROT 0b10000
# define REVROT 0b100000
# define TYPE 0b111100
# define A 0b1
# define B 0b10
# define BOTH 0b11
# define TARGET 0b11

typedef struct s_elem
{
	int		value;
	int		rank;
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
	int		pos;
	t_dlst	*node;
}	t_pos;

/********
* UTILS *
********/
// stack_utils.c
int				get_member(t_dlst *elem, char *member);
t_dlst			*get_member_oplst(t_dlst *node);
int				set_member(t_dlst *elem, char *member, int val);
void			set_member_oplst(t_dlst *node, t_dlst *op_lst);
// free_exit.c
void			free_stacks_exit(
					t_dlst **stack_a, t_dlst **stack_b, int status);
void			free_splits(char **splits);
void			free_oplsts(t_dlst *stack);

/*************************
* PARSING & DATA COLLECT *
*************************/
// parsing.c
t_dlst			*parse_args(char **argv);
// data_collect.c
void			store_rank(t_dlst *stack, int stack_size);
t_stack_data	get_stack_data(t_dlst *stack);
int				get_rank_pos(t_dlst *stack, int value);

/*******************
* OPERATIONS LISTS *
*******************/
// operations_list_utils.c
int				get_operation(t_dlst *node);
void			set_operation(t_dlst *node, int operation);
char			*optype_to_str(t_dlst *node);
char			*optarget_to_str(t_dlst *node);
// operations_list_alloc.c
t_dlst			*add_operation(t_dlst *op_lst, int operation_type, int target);
// operations_simplify_utils.c
int				is_merge_pair(int op_a, int op_b);
int				is_del_pair(int op_a, int op_b);
int				is_pair(int op_a, int op_b);
// operations_simplify.c
t_dlst			*simplify_operations(t_dlst *op_lst);
// operations_store.c
t_dlst			*get_oplst_totop(int pos, int stack_size, int source_macro);
void			store_op_lists(
					t_dlst *stack_a, t_dlst *stack_b, int size_a, int size_b);
// operations_apply.c
void			apply_operations_list(
					t_dlst *op_lst, t_dlst **stack_a, t_dlst **stack_b);

/********************
* SORTING ALGORITHM *
********************/
// presort.c
void			presort(
					t_dlst **stack_a,
					t_dlst **stack_b,
					int stack_size_a,
					int chunk_size);
// final_rotations.c
t_dlst			*get_final_rotations(t_dlst *stack_a);
// sort_stacks.c
int				is_sorted(t_dlst *stack);
void			sort_stacks(t_dlst **lst);

/*************************
* OPERATIONS APPLICATION *
*************************/
// stack_operations_utils.c
void			rot(t_dlst **stack);
void			rev_rot(t_dlst **stack);
void			swap(t_dlst **stack);
void			push(t_dlst **target, t_dlst **source);
void			push_push(t_dlst **stack_1, t_dlst **stack_2);
// stack_operations.c
void			s(char name, t_dlst **stack_a, t_dlst **stack_b);
void			p(char name, t_dlst **stack_a, t_dlst **stack_b);
void			r(char name, t_dlst **stack_a, t_dlst **stack_b);
void			rr(char name, t_dlst **stack_a, t_dlst **stack_b);

#endif
