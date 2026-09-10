#include <stdio.h>
#include <stdlib.h>

/* A tiny growable array of ints. `data` is the malloc'd buffer,
   `count` is how many slots are actually used, and `capacity` is
   how many slots we've reserved so far. When count would exceed
   capacity we realloc() to make room or we boogie */
typedef struct
{
    int *data;
    int count;
    int capacity;
} DynArray;

/* Prompt until the user gives a valid integer. Returns the value.
   Same trick as Activity B: scanf returns the number of items read. */
int read_int(const char *label)
{
    int value;

    while (1)
    {
        printf("%s", label);

        if (scanf("%d", &value) != 1)
        {
            printf("That wasn't a whole number. Try again.\n");
            /* Flush the rest of the bad line so we don't loop forever. */
            while (getchar() != '\n')
                ;
            continue;
        }

        return value;
    }
}

/* Create the array with an initial capacity using malloc().
   Returns 1 on success, 0 if the allocation failed. */
int array_create(DynArray *arr, int initial_capacity)
{
    if (initial_capacity < 1)
        initial_capacity = 1;

    arr->data = malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    arr->count = 0;
    arr->capacity = initial_capacity;
    return 1;
}

/* Add one element to the end. If we're out of room, double the
   capacity with realloc() so adding stays cheap on average. */
int array_add(DynArray *arr, int value)
{
    if (arr->count == arr->capacity)
    {
        int new_capacity = arr->capacity * 2;
        int *resized = realloc(arr->data, new_capacity * sizeof(int));

        /* realloc can return NULL on failure; if we overwrote arr->data
           with NULL we'd leak the original buffer, so use a temp. */
        if (resized == NULL)
        {
            printf("Memory reallocation failed. Element not added.\n");
            return 0;
        }

        arr->data = resized;
        arr->capacity = new_capacity;
        printf("(grew capacity to %d)\n", arr->capacity);
    }

    arr->data[arr->count] = value;
    arr->count++;
    return 1;
}

/* Print every element along with its index. */
void array_display(const DynArray *arr)
{
    int i;

    if (arr->count == 0)
    {
        printf("The array is empty.\n");
        return;
    }

    printf("Array (%d element(s), capacity %d):\n", arr->count, arr->capacity);
    for (i = 0; i < arr->count; i++)
        printf("  [%d] = %d\n", i, arr->data[i]);
}

/* Overwrite the value at a user-chosen index. */
void array_modify(DynArray *arr)
{
    int index, value;

    if (arr->count == 0)
    {
        printf("Nothing to modify yet. Add some elements first.\n");
        return;
    }

    index = read_int("Enter the index to modify: ");
    if (index < 0 || index >= arr->count)
    {
        printf("Index out of range. Valid range is 0 to %d.\n", arr->count - 1);
        return;
    }

    value = read_int("Enter the new value: ");
    arr->data[index] = value;
    printf("Updated index %d to %d.\n", index, value);
}

/* Sort ascending with bubble sort, reused from Activity A. */
void array_sort(DynArray *arr)
{
    int i, j, temp;

    if (arr->count < 2)
    {
        printf("Not enough elements to sort.\n");
        return;
    }

    for (i = 0; i < arr->count - 1; i++)
    {
        for (j = 0; j < arr->count - 1 - i; j++)
        {
            if (arr->data[j] > arr->data[j + 1])
            {
                temp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = temp;
            }
        }
    }

    printf("Array sorted in ascending order.\n");
}

int main(void)
{
    DynArray arr;
    int choice;

    /* Start with a small capacity so we can watch realloc() kick in. */
    if (!array_create(&arr, 2))
        return 1;

    while (1)
    {
        printf("\n=== Dynamic Array ===\n");
        printf("1. Add element\n");
        printf("2. Display elements\n");
        printf("3. Modify element\n");
        printf("4. Sort (ascending)\n");
        printf("5. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number from the menu.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            array_add(&arr, read_int("Enter a value to add: "));
            break;
        case 2:
            array_display(&arr);
            break;
        case 3:
            array_modify(&arr);
            break;
        case 4:
            array_sort(&arr);
            break;
        case 5:
            /* Free the memory once we're done with it. */
            free(arr.data);
            arr.data = NULL;
            printf("Memory freed. Goodbye!\n");
            return 0;
        default:
            printf("Unknown option. Pick 1-5.\n");
            break;
        }
    }
}
