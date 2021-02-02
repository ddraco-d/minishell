/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:12:51 by ddraco            #+#    #+#             */
/*   Updated: 2021/02/03 00:04:33 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_amount_line(char **lines)
{
	int	i;

	i = 0;
	if (!lines || !(*lines))
		return (0);
	while (lines[i])
		i++;
	return (i);
}

void	take_out_spaces(char **parsed_by_semicolon, int commands_amount)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < commands_amount)
	{
		tmp = parsed_by_semicolon[i];
		parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
		free(tmp);
		i++;
	}
}
