/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
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

void	exit_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	exit_error_free(char *error, t_dlstip **lst)
{
	ft_dlstip_clear(lst);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}
