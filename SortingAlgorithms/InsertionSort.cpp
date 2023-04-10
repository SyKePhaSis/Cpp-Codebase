// ###############################
// Author: SykePhaSis
// Subject: InsertionSort
// Date:11/4/2023
// ###############################

void InsertionSort(int (&array)[], int array_length){
  int tmp;
  for(int i = 1; i < array_length; i++){
    int j = i - 1;
    tmp = array[i];
    while(j>=0 && array[j] > tmp){
      array[j+1] = array[j];
      j--;
    }
    array[j + 1] = tmp;
  }
}

// ##########################
// #         TESTS          #
// ##########################

#include<iostream>

void OutputArr(int (&array)[], int array_length){
  std::cout << "Array: [";
  for(int j = 0; j < array_length; j++){
    std::cout << array[j] << " ";
  }
  std::cout << "]" << std::endl;
}

void test(){
  int arr[] = {7,3,32,-1,77,0};
  int arr_length = sizeof(arr)/sizeof(arr[0]);
  std::cout << "Before: " << std::endl;
  OutputArr(arr, arr_length);
  InsertionSort(arr, arr_length);
  std::cout << "After: " << std::endl;
  OutputArr(arr, arr_length);
}

int main (int argc, char *argv[])
{
  test();
  return 0;
}
