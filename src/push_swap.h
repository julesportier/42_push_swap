/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:44:40 by juportie          #+#    #+#             */
/*   Updated: 2025/02/24 14:26:54 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/src/libft.h"

// error.c
void	exit_error(char *error);
void	exit_error_free(char *error, t_dlisti **lst);

// parsing.c
t_dlisti	*parse_args(char **argv);

typedef struct s_stack_data
{
	int	max;
	int	min;
	int	size;
}	t_stack_data;
