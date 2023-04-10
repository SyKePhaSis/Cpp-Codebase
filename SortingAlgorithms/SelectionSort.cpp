// #####################################
// Author: SykePhaSis
// Subject: SelectionSort
// Date:10/4/2022
// #####################################

void SelectionSort(int (&array)[], int array_length){
  int x, tmp;
  x = 0;
  for(int j = array_length; j > 0; j--){
    for(int i = (array_length - j ); i < array_length; i++){
      if(array[array_length - i] < array[x]){
        x = i;
      }
    }
    if(array[array_length - j] > array[array_length - x]){
      tmp = array[array_length - j];
      array[array_length- j] = array[array_length - x];
      array[array_length- x] = tmp;
    }
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
  SelectionSort(arr, arr_length);
  std::cout << "After: " << std::endl;
  OutputArr(arr, arr_length);
}

int main (int argc, char *argv[])
{
  test();
  return 0;
}
