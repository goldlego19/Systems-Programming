#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stack.h"

/// @brief Prints a formatted string to the console.
/// @param format The format string.
/// @param ... The values to format into the string.
void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

/// @brief Reads an integer value from the user.
/// @param prompt The prompt message to display.
/// @param value A pointer to the integer variable to store the input value.
/// @return true if the input was successfully read; false otherwise.
_Bool readInt(const char *prompt, int *value)
{
    print("%s", prompt);
    int check = scanf("%d", value);
    if (check != 1)
    {
        print("Invalid input. Please enter a valid integer.");
        clearInputBuffer();
        return 0;
    }
    return 1;
}

/// @brief Clears the input buffer to remove any leftover characters.
void clearInputBuffer()
{
    while (getchar() != '\n')
        ; // clear input buffer
}

/// @brief Creates an empty stack.
/// @return A null pointer representing an empty stack.
nodePtr createStack()
{
    return NULL;
}

/// @brief Creates a new node with the given integer value.
/// @param n The integer value to store in the new node.
/// @param ptr The address of a pointer that will point to the newly created node.
/// @return true if the node was created successfully; false otherwise, and the pointer of the new node is returned via the ptr parameter.
_Bool createNode(int n, nodePtr *ptr)
{
    *ptr = (nodePtr)malloc(sizeof(node));
    if (*ptr != NULL)
    {
        (*ptr)->item = n; // Instead of (*ptr).item = n;
        (*ptr)->next = NULL;
        return 1;
    }
    return 0;
}

/// @brief Displays the value of a node if the pointer is not null.
/// @param p Pointer to the node to display.
void showNode(nodePtr p)
{
    if (p != NULL)
    {
        print("Node item: %d\n", p->item);
    }
    else
    {
        print("Null pointer\n");
    }
}

/// @brief Pushes a new node with the given value onto the stack.
/// @param n The integer value to store in the new node.
/// @param t A pointer to the top node of the stack.
/// @return true if the node was successfully created and inserted; false otherwise. The top pointer is updated via the t parameter.
_Bool push(int n, nodePtr *t)
{
    nodePtr p = NULL;
    if (createNode(n, &p))
    {
        p->next = *t;
        *t = p;
        return 1;
    }
    return 0;
}

/// @brief Pops the top node from the stack.
/// @param t A pointer to the top node of the stack.
/// @return true if the node was successfully popped; false otherwise. The top pointer is updated via the t parameter.
_Bool pop(nodePtr *t)
{
    if (*t != NULL)
    {
        nodePtr p = *t;
        *t = (*t)->next;
        free(p);
        return 1;
    }
    return 0;
}

/// @brief Checks whether the stack is empty.
/// @param t A pointer to the top node of the stack.
/// @return true if the stack is empty (t is NULL); otherwise, false.
_Bool isEmptyStack(nodePtr t)
{
    return t == NULL;
}

/// @brief Displays the elements in the stack from top to bottom.
/// @param t A pointer to the top node of the stack.
void showStack(nodePtr t)
{
    nodePtr p = t;
    if (isEmptyStack(t))
    {
        print("Stack is empty\n");
        return;
    }
    print("Stack elements:\n");
    while (p != NULL)
    {
        print("%d ", p->item);
        p = p->next;
    }
    print("\n");
}

/// @brief Returns the number of elements in a stack represented by a linked list.
/// @param t A pointer to the top node of the stack.
/// @return The number of elements in the stack, or -1 if the stack is empty.
int stackSize(nodePtr t)
{
    if (isEmptyStack(t))
    {
        return -1;
    }

    int count = 0;
    nodePtr current = t;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/// @brief Loads a stack from a file.
/// @param fileName The name of the file to load the stack from.
/// @return A pointer to the top node of the stack, or NULL if the stack could not be loaded.
nodePtr loadStackFromFile(const char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "r");
    if (!fp)
    { // fp is null report error
        print("Error opening file");
        return NULL;
    }
    else
    { // file opened without errors
        int index = 0, size = 4, value;
        int *array = (int *)malloc(size * sizeof(int));
        while (fscanf(fp, "%d", &value) == 1)
        {
            if (index >= size)
            {
                size *= 2;
                int *temp = (int *)realloc(array, size * sizeof(int));
                if (!temp)
                {
                    print("Memory allocation failed\n");
                    free(array);
                    fclose(fp);
                    return NULL;
                }
                array = temp;
            }

            if (value)
            {
                array[index++] = value;
            }
        }
        fclose(fp);

        nodePtr stack = createStack();
        for (int i = index - 1; i >= 0; i--)
        {
            if (!push(array[i], &stack))
            {
                print("Failed to push %d onto stack\n", array[i]);
                while (!isEmptyStack(stack))
                    pop(&stack);
                free(array);
                return NULL;
            }
        }

        free(array);
        print("Stack loaded from file with %d items.\n", index);
        return stack;
    }
}