/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                               :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:20:22 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:38:44 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// void	*del(void *lst)
// {
// 	t_list *temp_node;
// 	temp_node = lst;

// 	temp_node->content = NULL;
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	current = *lst;
	if (del != NULL)
	{
		while (current != NULL)
		{
			current = *lst;
			del(current->content);
			current = current->next;
			free(*lst);
			*lst = current;
		}
	}
}

// int	main(void)
// {
// 	t_list *head;
// 	t_list *node;
// 	t_list *temp;
// 	t_list *temp2;
// 	char s[] = "DELETE ME!!";
// 	char s2[] = "AND DELETE ME!";
// 	head = malloc(sizeof(t_list));
// 	node = malloc (sizeof(t_list));
// 	if (!head || !node)
// 		return (0);
// 	head->content = &s;
// 	head->next = node;
// 	head->next->content = &s2;
// 	head->next->next = NULL;
// 	temp = head;
// 	while (temp != NULL)
// 	{
// 		printf("%s\n", temp->content);
// 		temp = temp->next;
// 	}
// 	ft_lstclear(&head, del);
// 	temp2 = head; 
// 	printf("JO");
// 	while (temp2 != NULL)
// 	{
// 		printf("%s\n", temp2->content);
// 		temp2 = temp2->next;
// 	}
// }
