/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:18:31 by fsarbout          #+#    #+#             */
/*   Updated: 2021/01/15 19:52:47 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != (char)c)
// 	{
// 		if (!*s)
// 		{
// 			return (NULL);
// 		}
// 		s++;
// 	}
// 	return (char *)s;
// }



int	ft_strchr(const char *s, int c)
{
	int i;
	i = 0;
	
	while (*s)
	{
		if (*s == c)
			i++;
	}
	return (i)
}
