#ifndef SelectionSort
#define SelectionSort

void Sort(int (&array)[], int array_length)
{
    int x, tmp;
    x = 0;
    for (int j = array_length; j > 0; j--)
    {
        for (int i = (array_length - j); i < array_length; i++)
        {
            if (array[array_length - i] < array[x])
            {
                x = i;
            }
        }
        if (array[array_length - j] > array[array_length - x])
        {
            tmp = array[array_length - j];
            array[array_length - j] = array[array_length - x];
            array[array_length - x] = tmp;
        }
    }
}

#endif