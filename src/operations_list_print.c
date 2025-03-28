/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:30:30 by juportie          #+#    #+#             */
/*   Updated: 2025/03/21 13:31:05 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_op_lst(t_dlst *lst)
{
	char	*operation;
	while (lst)
	{
		operation = "\0";
		operation = operation_to_str(lst);
		if (operation == NULL)
		{
			ft_putendl_fd("print_op_lst: alloc error", 2);
			return ;
		}
		ft_putendl_fd(operation, 1);
		free(operation);
		lst = lst->next;
	}
}
