static int		find_j(const char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

static int		find_i(const char *str)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] < '0' || str[i + 1] > '9')
			return (-1);
	}
	else if (str[i] < '0' || str[i] > '9')
		return (-1);
	return (i);
}

static int		ft_limit(int i, const char *str)
{
	if (str[i] == '-')
		return (0);
	return (-1);
}

static int		check_flag(const char *str, int i)
{
	if (str[i] == '-')
		return (-1);
	return (1);
}

int				ft_atoi(const char *nptr)
{
	int				i;
	int				j;
	long long 		ret;
	long long		n;
	int				flag;

	n = 1;
	ret = 0;
	if ((i = find_i(nptr)) == -1)
		return (0);
	j = find_j(nptr, i + 1);
	flag = check_flag(nptr, i);
	while (--j >= i && nptr[j] != '+' && nptr[j] != '-')
	{
		if (((ret + flag * (nptr[j] - '0') * n) < ret && ret > 0) ||
				((ret + flag * (nptr[j] - '0') * n) > ret && ret < 0) ||
					((ret + flag * n) < ret && ret > 0) ||
						((ret + flag * n) > ret && ret < 0))
							return (ft_limit(i, nptr));
		ret += flag * (nptr[j] - '0') * n;
		n *= 10;
	}
	return ((int)ret);
}