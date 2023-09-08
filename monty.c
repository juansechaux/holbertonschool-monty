#include "monty.h"
/**
 * main - Monty interpreter main function
 * @argc: Argument count
 * @argv: Argument values
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	char *opcode, *value, *line = NULL;
	size_t line_number = 0, len = 0;
	FILE *file;
	int i;

	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t$\n");
		if (opcode == NULL || opcode[0] == '#')
			continue;
		if (strcmp(opcode, "push") == 0)
		{
			value = strtok(NULL, " $\n");
			if (value == NULL)
			{
				fprintf(stderr, "L%lu: usage: push integer\n", line_number);
				fclose(file);
				free(line);
				exit(EXIT_FAILURE);
			}
			for (i = 0; value[i] != '\0'; i++)
			{
				if (value[i] != '-' && !isdigit(value[i]))
				{
					fprintf(stderr, "L%lu: usage: push integer\n", line_number);
					fclose(file);
					free(line);
					exit(EXIT_FAILURE);
				}
			}
			push(&stack, atoi(value));
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack, line_number);
		}
		else if (strcmp(opcode, "pint") == 0)
		{
			if (stack == NULL)
			{
				fprintf(stderr, "L%lu: can't pint, stack empty\n", line_number);
				fclose(file);
				exit(EXIT_FAILURE);
			}
			pint(&stack, line_number);
		}
		else if (strcmp(opcode, "pop") == 0)
		{
			if (stack == NULL)
			{
				fprintf(stderr, "L%lu: can't pop an empty stack\n", line_number);
				fclose(file);
				exit(EXIT_FAILURE);
			}

			 pop(&stack, line_number);
		}
		else if (strcmp(opcode, "swap") == 0)
		{
			if (stack == NULL || stack->next == NULL)
			{
				fprintf(stderr, "L%lu: can't swap, stack too short\n", line_number);
				fclose(file);
				free_dlistint(stack);
				free(line);
				exit(EXIT_FAILURE);
			}
			swap(&stack, line_number);
		}
		else if (strcmp(opcode, "add") == 0)
		{
			if (stack == NULL || stack->next == NULL)
			{
				fprintf(stderr, "L%lu: can't add, stack too short\n", line_number);
				fclose(file);
				free_dlistint(stack);
				free(line);
				exit(EXIT_FAILURE);
			}
			add(&stack, line_number);
		}
		else if (strcmp(opcode, "nop") == 0)
		{
			nop(&stack, line_number);
		}
		else
		{
			fprintf(stderr, "L%lu: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			free(line);
			free_dlistint(stack);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = NULL;
	}
	free_dlistint(stack);
	free(line);
	fclose(file);
	return (0);
}

/**
 * free_dlistint - function that frees a list
 * @head: pointer to the header of the nodes
 * Return: void
 */
void free_dlistint(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
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

/**
 * add - Adds the top two elements of the stack
 * @stack: Puntero a la pila
 * @line_number: Número de línea en el script
 */
void add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n += (*stack)->n; /* Suma los dos elementos superiores */
	pop(stack, line_number); /* Elimina el elemento superior */
}

/**
 * nop - Doesn't do anything
 * @stack: Puntero a la pila
 * @line_number: Número de línea en el script
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
