/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:11:44 by juportie          #+#    #+#             */
/*   Updated: 2025/02/22 13:06:13 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"

void	free_stack(t_dlst **stack)
{
	t_dlst	*node;
	t_dlst	*last;

	if (stack == NULL || *stack == NULL)
		return ;
	last = (*stack)->prev;
	while (*stack)
	{
		node = *stack;
		ft_dlstclear(get_member_oplst(*stack));
		if (*stack != last)
			*stack = node->next;
		else
			*stack = NULL;
		free(node->content);
		node->content = NULL;
		free(node);
		node = NULL;
	}
}

void	free_stacks_exit(t_dlst **stack_a, t_dlst **stack_b, int status)
{
	free_stack(stack_a);
	free_stack(stack_b);
	exit(status);
}

void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		splits[i] = NULL;
		i++;
	}
	free(splits);
	splits = NULL;
}
