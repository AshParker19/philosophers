/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/21 18:42:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, char **av)
{
	table->ac = ac;
	table->av = av;
	table->sage_word = false;
	table->start_time = get_current_time();
	table->first_thought = NULL;
	table->last_thought = NULL;
}

void	*thinking_process(void *arg)
{
	t_table		*table;
	t_thinker	*current;

	table = (t_table *)arg;
	while (1)
	{
		current = table->first_thought;
		while (current)
		{
			pthread_mutex_lock(&current->lock);
			if (current && current->next)
				table->sage_word = !current->free_fork && !current->next->free_fork;
			if (table && table->sage_word)
			{
				current->free_fork = true;
				if (current->next)
					current->next->free_fork = true;
				printf ("%lu is eating\n", current->idea);
				sleep(2);
				current->free_fork = false;
				if (current->next)
					current->next->free_fork = false;
				printf ("%lu is thinking\n", current->idea);
				sleep(2);
			}	
			pthread_mutex_unlock(&current->lock);
			current = current->next;
		}
		sleep(1);
	}
	return (NULL);
}

// if (current_time - last_meal_time >= time_to_die)
// 	die();

t_thinker *ft_add_back(t_table *table)
{
	t_thinker	*new_idea;
	
	new_idea = malloc(1 * sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	new_idea->free_fork = false;
	pthread_mutex_init(&new_idea->lock, NULL);
	pthread_create(&new_idea->idea, NULL, thinking_process, table);
	if (!table->first_thought)
	{
		table->first_thought = new_idea;
		table->last_thought = new_idea;
		return (new_idea);
	}
	else
	{
		table->last_thought->next = new_idea;
		table->last_thought = new_idea;
		return (table->first_thought);
	}
}

void*	sage_supervision(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	// while (!table->sage_word)
	// {

	// }
	(void)arg;
	printf ("HELLO FROM SAGE\n");
	return (NULL);
}

void	join_thinkers(t_table *table)
{
	t_thinker	*current;

	current = table->first_thought;
	while (current)
	{
		pthread_join(current->idea, NULL);
		current = current->next;
	}
}

void	destroy_and_free(t_table *table)
{
	t_thinker	*current;

	current = table->first_thought;
	while (current)
	{
		pthread_mutex_destroy(&current->lock);
		current = current->next;
	}
}

void	organize_table(t_table *table)
{
	static int	i;

	while (i++ < ft_atoi(table->av[1]))
		table->first_thought = ft_add_back(table);
	pthread_create(&table->sage, NULL, sage_supervision, (void *)table);
	join_thinkers(table);
	pthread_join(table->sage, NULL);
	destroy_and_free(table);
}

int main(int ac, char *av[])
{
	t_table table;

	if (!parser(ac, av))
		return (1);
	table_init(&table, ac, av);
	organize_table(&table);
}

