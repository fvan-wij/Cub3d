/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                 :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:20:48 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:38:12 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = (t_list *) malloc(sizeof(t_list));
	if (head == NULL)
		return (0);
	head->content = content;
	head->next = NULL;
	return (head);
}

// int	main(void)
// {
// 	//struct s_list contains void *content (data) which stores data
// 	// and a struct s_list *next (link) which stores the memory 
// 	// address of the next node.
// 	int	a = 52;
// 	// char a[] = "DOODODODOD";
// 	t_list *head;
// 	head = ft_lstnew((void *)a);
// 	printf("%d\n", head->content);
// }
