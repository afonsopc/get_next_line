/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:28:23 by afpachec          #+#    #+#             */
/*   Updated: 2024/11/11 23:48:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str, char term)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter] && str[counter] != term)
		counter++;
	if (str[counter] == '\n')
		counter++;
	return (counter);
}

char	*str_join_buff(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1, 0);
	s2_len = ft_strlen(s2, '\n');
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (free(s1), NULL);
	str[s1_len + s2_len] = '\0';
	i = -1;
	while (++i < s1_len)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		str[s1_len + i] = s2[i];
	free(s1);
	i = -1;
	while (s2[s2_len + ++i])
		s2[i] = s2[s2_len + i];
	s2[i] = '\0';
	return (str);
}
