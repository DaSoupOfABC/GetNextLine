/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:55:34 by jenlee            #+#    #+#             */
/*   Updated: 2025/05/27 13:26:47 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"
#include <unistd.h>

char	*read_loop(int fd, char *stash, char *buffer)
{
	ssize_t	read_res;
	char	*tmp;

	read_res = 1;
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	while ((stash == NULL || !ft_strchr(stash, '\n')) && read_res > 0)
	{
		read_res = read(fd, buffer, BUFFER_SIZE);
		if (read_res == -1)
			return (free(stash), NULL);
		buffer[read_res] = '\0';
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	char	*result;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	result = read_loop(fd, stash, buffer);
	free(buffer);
	return (result);
}

char	*line_extraction(char *stash)
{
	int		i;
	char	*line;

	if (!stash[0] || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i);
	if (!new_stash)
		return (NULL);
	i++;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = line_extraction(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
