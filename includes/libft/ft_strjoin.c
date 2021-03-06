/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:40:58 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/09 15:50:20 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*ans;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1);
	size += ft_strlen(s2);
	ans = (char *)malloc(sizeof(char) * (size + 1));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ans[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		ans[i++] = s2[j++];
	ans[i] = '\0';
	return (ans);
}
