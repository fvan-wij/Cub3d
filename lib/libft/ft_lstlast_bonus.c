/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:10:38 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:25:36 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current == NULL)
		return (current);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

// int	main(void)
// {
// 	char s1[20] = "First";
// 	char s2[20] = "Last but not least";
// 	t_list *head;
// 	head = malloc(sizeof(t_list));
// 	if (!head)
// 		return (0);
// 	t_list *node;
// 	node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (0);
// 	head->content = s1;
// 	head->next = node;
// 	head->next->content = s2;
// 	head->next->next = NULL;
// 	t_list *current;
// 	current = ft_lstlast(head);
// 	printf("%s", current->content);
// }
