#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // get initial user input and allocate memory
    int n;
    printf("Enter value of N [1-10]: ");
    scanf("%d", &n);
    int *nums = (int *) malloc(n * sizeof(int));
    if (nums == NULL) return -1;

    // get numbers
    printf("Enter %d integer number(s)\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter #%d: ", i + 1);
        scanf("%d", &nums[i]);
    }

    // add them up and free memory
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
    }
    printf("Sum: %d\n", sum);
    free(nums);

    return 0;
}