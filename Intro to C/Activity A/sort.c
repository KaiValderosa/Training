#include <stdio.h>

int main(void)
{
    int arr[5];
    int size = 5;
    int i, j;

    /* Read the array elements. Lets go wid da basic terminal input like we are 5 yrs old */
    printf("Enter %d integers:\n", size);
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    /* Bubble sort using a combination of operators.
       - relational (<, >) and logical (&&) drive the comparisons
       - arithmetic (+, -) computes indices/bounds
       - bitwise XOR swaps the two elements in place without a temp var */
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j = j + 1)
        {
            /* Swap only when out of order (relational) and the values
               actually differ (logical &&) so the XOR swap is safe. */
            if ((arr[j] > arr[j + 1]) && (arr[j] != arr[j + 1]))
            {
                /* XOR swap: exchange without a temporary variable */
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
            }
        }
    }

    /* Output */
    printf("Sorted array (ascending):\n");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
