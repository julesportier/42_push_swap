/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:42:27 by juportie          #+#    #+#             */
/*   Updated: 2025/03/27 16:30:16 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_dlst			*lst;
	t_stack_data	data;

	if (argc < 2)
		return (EXIT_FAILURE);
	lst = parse_args(argv);
	data = get_stack_data(lst);
	if (!is_sorted(lst))
		sort_stacks(&lst, &data);
	ft_cdlstclear(&lst);
	return (EXIT_SUCCESS);
}
