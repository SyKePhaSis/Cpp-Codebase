// #####################################
// Author: SykePhaSis
// Subject: SelectionSort
// Date:10/4/2023
// #####################################

#include "../SelectionSort.h"

// ##########################
// #         TESTS          #
// ##########################

#include <iostream>

void OutputArr(int (&array)[], int array_length)
{
  std::cout << "Array: [";
  for (int j = 0; j < array_length; j++)
  {
    std::cout << array[j] << " ";
  }
  std::cout << "]" << std::endl;
}

void test()
{
  int arr[] = {7, 3, 32, -1, 77, 0};
  int arr_length = sizeof(arr) / sizeof(arr[0]);
  std::cout << "Before: " << std::endl;
  OutputArr(arr, arr_length);
  Sort(arr, arr_length);
  std::cout << "After: " << std::endl;
  OutputArr(arr, arr_length);
}

int main(int argc, char *argv[])
{
  test();
  return 0;
}
