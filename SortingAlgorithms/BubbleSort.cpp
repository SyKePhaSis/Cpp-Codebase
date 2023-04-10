// ##################################
// Author: SykePhaSis
// Subject: BubbleSort
// Date: 4/10/2023
// ##################################

void BubbleSort(int (&array)[], int array_length){
  int tmp;
  bool changed = true;
  while(changed){
    changed = false;
    for(int i = 0; i < (array_length - 1); i++){
      if(array[i] > array[i+1]){
        tmp = array[i];
        array[i] = array[i+1];
        array[i+1] = tmp;
        changed = true;
      }
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
  BubbleSort(arr, arr_length);
  std::cout << "After: " << std::endl;
  OutputArr(arr, arr_length);
}


int main (int argc, char *argv[])
{
  test();
  return 0;
}
