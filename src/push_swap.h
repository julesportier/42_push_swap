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
void	exit_error_free(char *error, t_dlsti **lst);
// parsing.c
t_dlsti	*parse_args(char **argv);
// list_operations.c
void	rot(t_dlsti **stack);
void	rev_rot(t_dlsti **stack);
void	swap(t_dlsti **stack);
void	push(t_dlsti **target, t_dlsti **source);
void	push_push(t_dlsti **lst_a, t_dlsti **lst_b);
// stack_operations.c
void	s(char name, t_dlsti **stack_a, t_dlsti **stack_b);
void	p(char name, t_dlsti **stack_a, t_dlsti **stack_b);
void	r(char name, t_dlsti **stack_a, t_dlsti **stack_b);
void	rr(char name, t_dlsti **stack_a, t_dlsti **stack_b);

typedef struct s_stack_data
{
	int	max;
	int	min;
	int	size;
}	t_stack_data;
