/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:49:29 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 14:49:31 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*split_atoi(t_fdf *data, char *line)
{
	int		*row;
	char	**temp;
	int		i;

	temp = ft_split(line, ' ');
	row = malloc(sizeof(int) * data->columns);
	i = 0;
	while (temp[i])
	{
		row[i] = ft_atoi(temp[i]);
		i++;
	}
	free(temp);
	return (row);
}
