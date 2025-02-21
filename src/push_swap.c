/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/02/19 13:58:11 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/src/libft.h"
#include <stdlib.h>

int	main(void)
{
	t_dlisti	*lst = NULL;

	t_dlisti	*new_node = ft_dlsti_new(1);
	ft_cdlsti_add_back(&lst, new_node);
	ft_print_dlsti(lst);
	t_dlisti	*new_node2 = ft_dlsti_new(2);
	ft_cdlsti_add_back(&lst, new_node2);
	ft_print_dlsti(lst);
	t_dlisti	*new_node3 = ft_dlsti_new(3);
	ft_cdlsti_add_back(&lst, new_node3);
	ft_print_dlsti(lst);
	return (0);
}
