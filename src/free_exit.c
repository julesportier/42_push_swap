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
#include <stdlib.h>

void	free_exit(t_dlst **lst, int status)
{
	ft_cdlstclear(lst);
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
