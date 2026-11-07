/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: jeguiber <jeguiber@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/07 04:05:49 by jeguiber         #+#    #+#              */
/*   Updated: 2026/11/07 10:08:30 by jeguiber        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_no_newline(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), NULL);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (free(s1), res);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	printf("=== TEST FT_STRLEN ===\n");
// 	printf("ft_strlen(\"42\") = %zu (attendu: 2)\n", ft_strlen("42"));
// 	printf("ft_strlen(\"\") = %zu (attendu: 0)\n", ft_strlen(""));
// 	printf("ft_strlen(NULL) = %zu (attendu: 0)\n", ft_strlen(NULL));
// 	printf("\n=== TEST FT_NO_NEWLINE ===\n");
// 	printf("ft_no_newline(\"Hello\\nWorld\") = %d (attendu: 0)\n",
// 		ft_no_newline("Hello\nWorld"));
// 	printf("ft_no_newline(\"HelloWorld\") = %d (attendu: 1)\n",
// 		ft_no_newline("HelloWorld"));
// 	printf("ft_no_newline(NULL) = %d (attendu: 1)\n", ft_no_newline(NULL));
// 	printf("\n=== TEST FT_STRJOIN ===\n");
// 	char	*s1 = strdup("Bonjour ");
// 	char	*s2 = "le monde !";
// 	char	*res = ft_strjoin(s1, s2);

// 	printf("ft_strjoin(\"Bonjour \", \"le monde !\") = %s\n", res);
// 	free(res);
// 	char	*res_null = ft_strjoin(NULL, "Init depuis NULL");

// 	printf("ft_strjoin(NULL, \"Init depuis NULL\") = %s\n", res_null);
// 	free(res_null);
// 	return (0);
// }
