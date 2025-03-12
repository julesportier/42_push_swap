/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:00:52 by juportie          #+#    #+#             */
/*   Updated: 2025/03/12 13:42:33 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int str_array_len(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i] != NULL)
		i++;
	return (i);
}

// TODO
// free correctly the memory
char	**store_op(char *op, char **op_array)
{
	int	op_arr_len;
	char	**new_arr;
	int	op_len;
	char	*new_op;
	int	i;

	op_arr_len = str_array_len(op_array);
	new_arr = malloc(sizeof(char *) * (op_arr_len + 2));
	if (new_arr == NULL)
		return (NULL);
	op_len = ft_strlen(op);
	new_op = malloc(sizeof(char) * (op_len + 1));
	if (new_op == NULL)
	{
		free(new_arr);
		return (NULL);
	}
	i = 0;
	while (i < op_arr_len)
	{
		new_arr[i] = op_array[i];
		i++;
	}
	new_arr[i] = new_op;
	new_arr[i + 1] = NULL;
	free(op_array);
	return (new_arr);
}
