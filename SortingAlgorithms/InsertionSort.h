

#ifndef InsertionSort
#define InsertionSort

void Sort(int (&array)[], int array_length)
{
    int tmp;
    for (int i = 1; i < array_length; i++)
    {
        int j = i - 1;
        tmp = array[i];
        while (j >= 0 && array[j] > tmp)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = tmp;
    }
}

#endif