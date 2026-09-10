#include <stdio.h>

/* Each arithmetic operation is its own function returning a numerical value.
   Division returns a double so we don't silently truncate the result. */
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

double divide(int a, int b)
{
    return (double)a / b;
}

/* Prompt until the user gives an integer in the range 0-100.
   Returns the validated value. */
int read_operand(const char *label)
{
    int value;

    while (1)
    {
        printf("Enter %s (0-100): ", label);

        /* scanf returns the number of items read; anything other than 1
           means the input wasn't a valid integer. */
        if (scanf("%d", &value) != 1)
        {
            printf("That wasn't a whole number. Try again.\n");
            /* Flush the rest of the bad line so we don't loop forever. */
            while (getchar() != '\n')
                ;
            continue;
        }

        if (value < 0 || value > 100)
        {
            printf("Out of range. Only 0 to 100 is allowed.\n");
            continue;
        }

        return value;
    }
}

int main(void)
{
    int choice;
    int a, b;

    /* Loop until the user picks Exit. */
    while (1)
    {
        printf("\n=== Calculator ===\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");
        printf("Choose an operation: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number from the menu.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice == 5)
        {
            printf("Goodbye!\n");
            break;
        }

        if (choice < 1 || choice > 5)
        {
            printf("Unknown option. Pick 1-5.\n");
            continue;
        }

        /* All operations need two operands. */
        a = read_operand("the first number");
        b = read_operand("the second number");

        switch (choice)
        {
            case 1:
                printf("Result: %d\n", add(a, b));
                break;
            case 2:
                printf("Result: %d\n", subtract(a, b));
                break;
            case 3:
                printf("Result: %d\n", multiply(a, b));
                break;
            case 4:
                /* Guard against division by zero. */
                if (b == 0)
                    printf("Cannot divide by zero.\n");
                else
                    printf("Result: %.2f\n", divide(a, b));
                break;
        }
    }

    return 0;
}
