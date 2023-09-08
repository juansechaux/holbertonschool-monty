#include "monty.h"
/**
 * push - Pushes an element onto the stack
 * @stack: Pointer to the stack
 * @value: Value to be pushed onto the stack
 */
void push(stack_t **stack, int value)
{
	stack_t *new_node;

	new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pall - Prints all values on the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the script
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number; /*Parametro no utilizado*/
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - Prints the first values on the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the script
 */
void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number; /*Parametro no utilizado*/

	printf("%d\n", current->n);
}

/**
 * pop - removes the first values on the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the script
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *node_to_delete = *stack;
	(void)line_number;/*Parametro no Utilizado*/

	*stack = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = NULL;
	free(node_to_delete);
}

/**
 * swap - Swaps the top two elements of the stack
 * @stack: Puntero a la pila
 * @line_number: Número de línea en el script
 */
void swap(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	int tmp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = tmp;
}
