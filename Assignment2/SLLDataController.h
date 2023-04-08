//
//  SLLDataControler.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//

// Students can remove the final initial return of the functions

#ifndef SLLDataController_h
#define SLLDataController_h

#include "dataStructure.h"
#include <vector>
#include <string>

//Functions used to manage Singly Linked List
void print(SLinkedList& list){
    if (!list.size) {
        std::cout << "List is empty" << endl;
        return;
    }
    SoldierNode* head = list.head;
    while (head){
        std::cout << head->data.ID << "->";
        head = head->next;
    }
    std::cout << "NULL"<<endl;
}

bool insertAt (SLinkedList& list, Soldier element, int pos){
    //Insert element into a pos in the SLL
    //Return true if insert successfully, false otherwise
    //TODO
    if (pos==0){
        SoldierNode* ele=new SoldierNode(element,NULL);
        if (list.head == NULL){
            list.head = ele;
            list.size++;
            return 1;
        }
        else{
            ele->next = list.head;
            list.head = ele;
            list.size++;
            return 1;
        }
    }
    else if(pos>0 && pos<list.size){
        SoldierNode* ele=new SoldierNode(element,NULL);
        SoldierNode* head = list.head;
        for (int i=0;i<pos-1;i++){
            head=head->next;
        }
        ele->next=head->next;
        head->next=ele;
        list.size++;
        return 1;
    }
    else if (pos==list.size){
        SoldierNode* ele=new SoldierNode(element,NULL);
        SoldierNode* head = list.head;
        for (int i=0;i<pos-1;i++){
            head=head->next;
        }
        head->next = ele;
        head = ele;
        list.size++;
        return 1;
    }
    else return 0;
    return false;
}

bool removeAt (SLinkedList& list, int idx){
    //Remove element at index idx in the SLL
    //Return true if remove successfully, false otherwise
    //TODO
    if (list.head==NULL) return 0;
    if (idx==0){
        SoldierNode* head = list.head;
        list.head = head->next;
        delete head;
        list.size--;
        return 1;
    }
    else if (idx>0 && idx<=list.size-1){
        SoldierNode* head = list.head;
        for (int i=0;i<idx-1;i++){
            head=head->next;
        }
        SoldierNode* head1 = head->next;
        head->next = head1->next;
        delete head1;
        head1=NULL;
        list.size--;
        return 1;
    }
    else return 0;
    return false;
}

bool removeFirstItemWithHP (SLinkedList& list, int HP){
    //Remove the first element with HP equals to HP
    //Return true if remove successfully, false otherwise
    //TODO
    if (list.head==NULL) return 0;
    int idx=0;
    SoldierNode* head = list.head;
    while (head->data.HP!=HP){
        head=head->next;
        idx++;
        if (idx==list.size) return 0;
    }
    return removeAt(list,idx);
    return false;
}

int indexOf(SLinkedList& list, Soldier soldier){
    //Find index of soldier (start from 0)
    //Return -1 if the soldier does not exist
    //TODO
    if (list.head==NULL) return -1;
    int index=0;
    SoldierNode* head = list.head;
    for (int i=0;i<list.size;i++){
        if (head->data.HP==soldier.HP && head->data.isSpecial==soldier.isSpecial && head->data.ID==soldier.ID){
            return index;
        }
        index++;
        head=head->next;
    }
    return -1;
}

int size(SLinkedList& list){
    //Return size of the list
    //TODO
    return list.size;
}

bool empty(SLinkedList& list){
    //Check whether the list is empty
    //TODO
    if (list.head==NULL) return 1;
    return false;
}

void clear(SLinkedList& list){
    //Delete all of the elements in list
    //TODO
    while (list.head!=NULL){
        SoldierNode* head = list.head;
        list.head=list.head->next;
        delete head;
        list.size--;
        if (list.size==0) return;
    }
}

string getIDAt(SLinkedList& list, int pos){
    //Get ID of the Soldier at pos
    //TODO
    if (list.head==NULL) return "-1";
    SoldierNode* head = list.head;
    if (pos>=0 && pos<list.size){
        for (int i=0;i<pos;i++){
            head=head->next;
        }
        return head->data.ID;
    }
    else return "-1";
    return "-1";
}

int getHPAt(SLinkedList& list, int pos){
    //Get HP of the Soldier at pos
    //TODO
    if (list.head==NULL) return -1;
    SoldierNode* head = list.head;
    if (pos>=0 && pos<list.size){
        for (int i=0;i<pos;i++){
            head=head->next;
        }
        return head->data.HP;
    }
    else return -1;
    return -1;
}

bool setHPAt(SLinkedList& list, int HP, int pos){
    //Set value of HP at pos
    //TODO
    //Return true if set successfully, false otherwise
    if (list.head==0) return 0;
    SoldierNode* head = list.head;
    if (pos>=0 && pos<list.size){
        for (int i=0;i<pos;i++){
            head=head->next;
        }
        head->data.HP=HP;
        return 1;
    }
    else return 0;
}

bool contains (SLinkedList& list, Soldier soldier){
    //Check if array contains soldier
    //TODO
    if (indexOf(list,soldier)==-1) return 0;
    else return 1;
}

//You can write your own functions here

//End your own functions

#endif /* SLLDataControler_h */
