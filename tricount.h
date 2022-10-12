/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricount.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:43:08 by msharifi          #+#    #+#             */
/*   Updated: 2022/09/29 19:19:43 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_guy
{
	int			index;
	int			paid;
	int			debt;
	struct s_guy	*next;
}				t_guy;

typedef struct s_data
{
	int		total;
	int		part;
	t_guy	*guy;
}				t_data;