/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jeguiber <jeguiber@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/07 04:03:43 by jeguiber         #+#    #+#              */
/*   Updated: 2026/11/07 10:25:27 by jeguiber        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_stash_all(int fd, char *stash)
{
	char	*tmp;
	int		bread;

	bread = 1;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (ft_no_newline(stash) && bread)
	{
		bread = read(fd, tmp, BUFFER_SIZE);
		if (bread == -1)
		{
			return (free(tmp), NULL);
		}
		tmp[bread] = '\0';
		stash = ft_strjoin(stash, tmp);
	}
	return (free(tmp), stash);
}

static char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc((i + 1 + (stash[i] == '\n')) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_free_all(char *stash)
{
	int		i;
	int		j;
	char	*sstash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	sstash = malloc((ft_strlen(stash) - i) * sizeof(char));
	if (!sstash)
		return (free(stash), NULL);
	i++;
	j = 0;
	while (stash[i])
		sstash[j++] = stash[i++];
	sstash[j] = '\0';
	return (free(stash), sstash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_stash_all(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_free_all(stash);
	return (line);
}
