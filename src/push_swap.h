/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/02/26 12:33:51 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"

// error.c
void	exit_error(char *error);
void	exit_error_free(char *error, t_dlstip **lst);
// parsing.c
t_dlstip	*parse_args(char **argv);
// list_operations.c
void	rot(t_dlstip **stack);
void	rev_rot(t_dlstip **stack);
void	swap(t_dlstip **stack);
void	push(t_dlstip **target, t_dlstip **source);
void	push_push(t_dlstip **lst_a, t_dlstip **lst_b);
// stack_operations.c
void	s(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void	p(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void	r(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void	rr(char name, t_dlstip **stack_a, t_dlstip **stack_b);
void	print_stack(t_dlstip *stack);

typedef struct s_stack_data
{
	int	max;
	int	min;
	int	size;
}	t_stack_data;
