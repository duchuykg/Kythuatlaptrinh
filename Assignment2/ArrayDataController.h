//
//  ArrayDataController.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//

// Students can remove the final initial return of the functions

#ifndef ArrayDataController_h
#define ArrayDataController_h

#include "dataStructure.h"
#include <vector>
#include <string>

//Functions used to manage Array
void print(Array& array){
    if (!array.size) {
        std::cout << "Array is empty" << endl;
        return;
    }
    std::cout <<"[";
    for(int i=0;i<array.size;i++){
        std::cout << array.arr[i].ID << " ";
    }
    std::cout <<"]" << endl;
}
void ensureCapacity(Array& array, int newCap);
void initArray (Array& array, int cap){
    //Init a new array with capacity equals to cap
    //TODO
    array.capacity = cap;
    array.arr = new Soldier[cap];
}

bool insertAt(Array& array, Soldier element, int pos){
    //Insert element into a pos in the array
    //Return true if insert successfully, false otherwise
    //TODO
    if (array.arr==NULL) return 0;
    if (array.capacity==array.size){
        ensureCapacity(array,array.capacity*3/2+1);
    }
    if (pos>=0 && pos<=array.size){
        array.size++;
        for (int i=array.size-1;i>pos;i--)
        {
            array.arr[i] = array.arr[i - 1];
        }
        array.arr[pos] = element;
        return 1;
    }
    else return 0;
    return false;
}

bool removeAt (Array& array, int idx){
    //Remove element at index idx in the array
    //Return true if remove successfully, false otherwise
    //TODO
    if (array.size==0) return 0;
    if (idx>=0 && idx<array.size){
        for (int i=idx;i<array.size;i++){
            array.arr[i]=array.arr[i+1];
        }
        array.size--;
        return 1;
    }
    return false;
}

bool removeFirstItemWithHP (Array& array, int HP){
    //Remove the first element with HP equals to HP
    //Return true if remove successfully, false otherwise
    //TODO
    if (array.size==0) return 0;
    int index=0;
    for (int i=0;i<array.size;i++){
        if (array.arr[i].HP==HP){
            return removeAt(array,index);
        }
        index++;
    }
    return false;
}

void ensureCapacity(Array& array, int newCap){
    //Extend the capacity of the array
    //TODO
    array.capacity = newCap;
    Soldier* newCapacity = new Soldier [newCap];
    for (int i=0;i<array.size;i++){
        newCapacity[i]=array.arr[i];
    }
    array.arr = newCapacity;
}

int indexOf(Array& array, Soldier soldier){
    //Find index of soldier (start from 0)
    //Return -1 if the soldier does not exist
    //TODO
    if (array.size==0) return -1;
    int index=0;
    for (int i=0;i<array.size;i++){
        if (array.arr[i].HP==soldier.HP && array.arr[i].isSpecial==soldier.isSpecial && array.arr[i].ID==soldier.ID){
            return index;
        }
        index++;
    }
    return -1;
}

int size(Array& array){
    //Return size of the array
    //TODO
    return array.size;
}

bool empty(Array& array){
    //Check whether the array is empty
    //TODO
    if (array.size==0) return 1;
    else
    return false;
}

string getIDAt(Array& array, int pos){
    //Get ID of the Soldier at pos
    //TODO
    if (array.size==0) return "-1";
    if (pos>=0 && pos<array.size) return array.arr[pos].ID;
    return "-1";
}

int getHPAt(Array& array, int pos){
    //Get HP of the Soldier at pos
    //TODO
    if (array.size==0) return -1;
    if (pos>=0 && pos<array.size) return array.arr[pos].HP;
    return -1;
}

bool setHPAt(Array& array, int HP, int pos){
    //Set value of HP at pos
    //TODO
    //Return true if set successfully, false otherwise
    if (array.size==0) return 0;
    if (pos>=0 && pos<array.size){
        array.arr[pos].HP=HP;
        return 1;
    }
    return false;
}

void clear(Array& array){
    //Delete all of the elements in array
    //TODO
    array.size=0;
    delete[] array.arr;
    array.arr=NULL;
    array.capacity=0;
}

bool contains (Array& array, Soldier soldier){
    //Check if array contains soldier
    //TODO
    if (indexOf(array,soldier)==-1) return 0;
    else return 1;
}

//You can write your own functions here

//End your own functions

#endif /* ArrayDataController_h */
