#include "stack.h"

int main()
{
    int choice = 0;
    nodePtr stack = createStack();

    while (1)
    {
        print("\nMain Menu for Stack\n");
        print("1. Load Stack\n");
        print("2. Push\n");
        print("3. Pop\n");
        print("4. Show Stack\n");
        print("5. How many items on stack?\n");
        print("6. Exit\n");

        if (readInt("Enter your choice: ", &choice))
        {
            switch (choice)
            {
            case 1:
                // Load Stack
                stack = loadStackFromFile("data.txt");
                break;
            case 2:
            {
                // Push
                int valueToPush;
                if (readInt("Enter value to push: ", &valueToPush))
                    push(valueToPush, &stack) ? print("Pushed %d onto stack.\n", valueToPush) : print("Failed to push %d onto stack.\n", valueToPush);
            }
            break;

            case 3:
                // Pop
                if (isEmptyStack(stack))
                    print("Stack is empty. Cannot pop.\n");
                else
                {
                    int itemToPop = stack->item;
                    pop(&stack) ? print("Popped top item from stack: %d\n", itemToPop) : print("Failed to pop item from stack.\n");
                }
                break;

            case 4:
                // Show Stack
                isEmptyStack(stack) ? print("Stack is empty.\n") : showStack(stack);
                break;
            case 5:
            {
                // How many items on stack?
                int size = stackSize(stack);
                print(size == -1 ? "Stack is empty.\n" : "Stack size: %d\n", size);
                break;
            }
            case 6:
                // Exit
                print("Exiting program.\n");
                while (!isEmptyStack(stack))
                    pop(&stack);
                stack = 0;
                return 0;
            default:
                print("Invalid choice. Please select a valid option.\n");
            }
        }
    }
}