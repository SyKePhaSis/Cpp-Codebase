// ############################
// Writen by: SykePhaSis
// Subject: HashTable
// Initial Date: 4/10/23
// ############################

#include<iostream>
#include<list>

class HashTable{
  std::list<int> *table;
  int storageLength;
  
  public:
    HashTable(int length);
    void InsertItem(int key);
    void DeleteItem(int key);
    void DisplayHashTable(void);

    int HashMechanism(int key){
      int hash = ((key << 3)^0xFA)%(0x5A^key)%storageLength;
      // std::cout << "Key:" << key << " Value:" << hash << "\n";
      return hash;
    }
};

HashTable::HashTable(int length){
  this->storageLength = length;
  table = new std::list<int>[length];
}

void HashTable::InsertItem(int key){
  int index = HashMechanism(key);
  table[index].push_back(key);
}

void HashTable::DeleteItem(int key){
  int index = HashMechanism(key);
  
  std::list<int>::iterator i;
  for(i = table[index].begin(); i != table[index].end(); i++){
    if(*i == key){
      break;
    }
  }
  if(i != table[index].end()){
    table[index].erase(i);
  }
}

void HashTable::DisplayHashTable(void){
  for(int i = 0; i < storageLength; i++){
    std::cout << i;
    for(auto j:table[i]){
      std::cout << " ==> " << j;
    }
    std::cout << std::endl;
  }
}

// #############################
// #           TESTS           #
// #############################


// int main (int argc, char *argv[])
// {
//   int arr[] = {20, 34, 56, 54, 76, 87}; 
//   int n = sizeof(arr)/sizeof(arr[0]);
//   HashTable Table(n);
//   for(int i = 0; i < n; i++){
//     Table.InsertItem(arr[i]);
//   }
//   std::cout << "This is the Hash Table" << std::endl;
//   Table.DisplayHashTable();
//   Table.DeleteItem(76);
//   Table.DisplayHashTable();
//   return 0;
// }
