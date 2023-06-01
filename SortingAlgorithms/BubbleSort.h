#ifndef BubbleSort
#define BubbleSort

void Sort(int (&array)[], int array_length)
{
    int tmp;
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < (array_length - 1); i++)
        {
            if (array[i] > array[i + 1])
            {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                changed = true;
            }
        }
    }
}

#endif
