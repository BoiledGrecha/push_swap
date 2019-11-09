#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_info
{
	char *ret;
	int length;
	int *stack1;
	int *stack2;
}		t_info;

int				ft_atoi(const char *nptr);

#endif