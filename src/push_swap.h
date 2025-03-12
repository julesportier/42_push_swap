/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/03/10 09:21:57 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"

#define DEBUG 0
#define USLEEP 10000

typedef struct s_stack_data
{
	int	max;
	int	min;
	int	size;
}	t_stack_data;

typedef struct s_pos
{
	int	pos;
	t_dlstip	*node;
}	t_pos;

// error.c
void		exit_error(char *error);
void		exit_error_free(char *error, t_dlstip **lst);
// parsing.c
t_dlstip	*parse_args(char **argv);
// data_collect.c
void		store_order(t_dlstip *lst, t_stack_data *data);
t_stack_data	get_lst_data(t_dlstip *lst);
void		store_cost(t_dlstip *lst, t_stack_data *data);
void		store_cost_insert_a(t_dlstip *stack_a, t_dlstip *stack_b, t_stack_data *data);
// list_operations.c
void		rot(t_dlstip **stack);
void		rev_rot(t_dlstip **stack);
void		swap(t_dlstip **stack);
void		push(t_dlstip **target, t_dlstip **source);
void		push_push(t_dlstip **lst_a, t_dlstip **lst_b);
// stack_operations.c
void		s(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void		p(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void		r(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void		rr(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void		print_stack(t_dlstip *stack);
