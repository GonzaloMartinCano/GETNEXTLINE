/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:09:12 by gmartin-          #+#    #+#             */
/*   Updated: 2019/12/10 11:23:15 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t x;

	x = 0;
	while (s[x] != '\0')
	{
		x++;
	}
	return (x);
}

char	*ft_strchr(char *s, int c)
{
	char	*str;
	int		x;

	x = 0;
	str = (char*)s;
	while (str[x])
	{
		if (str[x] == c)
			return (&str[x]);
		x++;
	}
	if (str[x] == '\0' && c == '\0')
		return (&str[x]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	dst = malloc(sizeof(*dst) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[x])
	{
		dst[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		dst[x] = s2[y];
		x++;
		y++;
	}
	free(s1);
	dst[x] = '\0';
	return (dst);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (NULL);
	while (i > 0)
	{
		dst[j] = s1[j];
		i--;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;
	size_t	slen;

	i = 0;
	if (!s)
		return (0);
	dst = malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
	{
		dst[i] = '\0';
		return (dst);
	}
	while (len > 0 && s[start] != '\0')
	{
		dst[i] = s[start];
		i++;
		start++;
		len--;
	}
	dst[i] = '\0';
	return (dst);
}
