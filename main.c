/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:31 by msharifi          #+#    #+#             */
/*   Updated: 2022/10/06 16:34:22 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tricount.h"

long	ft_atoi(const char *str)
{
	int			i;
	long	result;
	int			sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

t_guy	*ft_lstlast(t_guy *guy)
{
	t_guy	*tmp;

	tmp = guy;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_guy	*ft_lstnew(int index, int paid, int part)
{
	t_guy	*new;

	new = malloc(sizeof(t_guy));
	if (!new)
		return (0);
	new->index = index;
	new->paid = paid;
	new->debt = paid - part;
	if (new->debt > 0)
		new->debt = 0;
	new->next = NULL;
	return (new);
}

int	add_last(t_data *data, char **av, int i)
{
	t_guy	*last;
	t_guy	*tmp;

	tmp = data->guy;
	last = ft_lstnew(i - 1, ft_atoi(av[i]), data->part);
	if (!last)
		return (0);
	if (!data->guy)
	{
		data->guy = last;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
	last->next = NULL;
	return (1);
}

t_data	*init_data(t_data *data, int ac, char **av)
{
	int	i;

	i = 2;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->part = ft_atoi(av[1]) / (ac - 2);
	while (i < ac)
	{
		if (!add_last(data, av, i))
			return (0);
		i++;
	}
	return (data);
}

void	print_guys(t_data *data)
{
	t_guy	*tmp;

	tmp = data->guy;
	while (tmp)
	{
		printf("\nGuy number : [%d]\n", tmp->index);
		printf("Paid : [%d]\n", tmp->paid);
		printf("Debt : [%d]\n\n", tmp->debt);
		tmp = tmp->next;
	}
}

int	parsing(int ac, char **av)
{
	int	total;
	int	add;
	int	i;

	total = ft_atoi(av[1]);
	add = 0;
	i = 2;
	while (i < ac)
	{
		add += ft_atoi(av[i]);
		i++;
	}
	if (add != total)
	{
		printf("The total input isn't equal to the addition of the user paid input\n");
		return (0);
	}
	return (1);
}

t_guy	*find_biggest_debt(t_guy *guy)
{
	t_guy	*tmp;
	t_guy	*save;
	
	save = guy;
	tmp = guy;
	while (tmp)
	{
		if (tmp->debt < save->debt)
			save = tmp;
		tmp = tmp->next;
	}
	return (save);
}

t_guy	*find_biggest_paid(t_guy *guy)
{
	t_guy	*tmp;
	t_guy	*save;
	
	save = guy;
	tmp = guy;
	while (tmp)
	{
		if (tmp->paid > save->paid)
			save = tmp;
		tmp = tmp->next;
	}
	return (save);
}

int	is_end(t_data *data)
{
	t_guy	*tmp;

	tmp = data->guy;
	while (tmp)
	{
		if (tmp->debt != 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	exchange(t_data *data, t_guy *big_paid, t_guy *big_debt)
{
	int	to_give;

	to_give = big_debt->debt;
	if (to_give < 0)
		to_give *= -1;
	if (to_give > big_paid->paid - data->part)
		to_give = big_paid->paid - data->part;
	big_paid->paid -= to_give;
	big_debt->paid += to_give;
	big_debt->debt += to_give;
	printf("Guy number [%d] gave [%d] to guy number [%d]\n", big_debt->index, to_give, big_paid->index);
}

void	algo(t_data *data)
{
	t_guy	*big_paid;
	t_guy	*big_debt;

	while (!is_end(data))
	{
		big_paid = find_biggest_paid(data->guy);
		big_debt = find_biggest_debt(data->guy);
		exchange(data, big_paid, big_debt);
	}
}

void	ft_free(void *addr)
{
	free(addr);
	addr = NULL;
}

void	free_data(t_data *data)
{
	t_guy	*tmp;

	tmp = data->guy;
	while (data->guy)
	{
		data->guy = data->guy->next;
		ft_free(tmp);
		tmp = data->guy;
	}
	ft_free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 4)
		return (1);
	if (!parsing(ac, av))
		return (2);
	data = init_data(data, ac, av);
	if (!data)
		return (3);
	print_guys(data);
	algo(data);
	print_guys(data);
	free_data(data);
	return (0);
}
