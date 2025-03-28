#include "push_swap.h"

t_dlst	*create_oplst();

int	main(int argc, char *argv[])
{
	t_dlst	*lst;

	if (argc == 1)
		return (EXIT_SUCCESS);
	if (argc != 2)
		return (EXIT_FAILURE);
	lst = add_arg(argv[1], &lst);
	if (lst == NULL)
		return (EXIT_FAILURE);
	if (find_duplicates(lst))
	{
		ft_putendl_fd("Error", 2);
		free_stack(&lst);
		return (EXIT_SUCCESS);
	}


