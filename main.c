#include "push_swap.h"

void error_function()
{
    write(1, "Error\n", 6);
    exit(1);
}

void check_string(char *str)
{
    int i;
    i = -1;
    while(str[++i])
    {
        if (str[i] > '0' && str[i] < '9')
            continue;
        if (i == 0 && (str[i] == '-' || str[i] == '+'))
            continue;
        error_function();
    }
}

void append_struct(t_info *structure, char *str)
{

}

void memory_allocate(t_info *structure, int length)
{
    structure->stack1 = malloc(sizeof(int) * (length - 1));
    structure->stack2 = malloc(sizeof(int) * (length - 1));
    structure->length = length - 1;
}

int main(int argc, char **argv)
{
    int i;
    t_info *structure;
    if (argc < 2)
        error_function();
    i = 0;
    while (++i < argc)
        check_string(argv[i]);
    structure = malloc(sizeof(t_info));
    i = 0;
    memory_allocate(structure, argc);
    append_struct(structure, argv[i]);
    go_sort(structure);
}