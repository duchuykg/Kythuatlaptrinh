//
//  thirdBattle.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//
// Students can remove the final initial return of the functions

#ifndef thirdBattle_h
#define thirdBattle_h

#include "SLLDataController.h"
#include "ArrayDataController.h"
#include <vector>
#include <string>

//////////////////////////////////////////////////////
/// TASK 1
//////////////////////////////////////////////////////

bool push(Array& array, Soldier soldier){
    //Return true if push successfully, false otherwise
    //TODO
    if (array.arr==NULL) initArray(array,10);
    if (array.capacity==array.size){
        ensureCapacity(array,array.capacity*3/2+1);
    }
    return insertAt(array,soldier,0);
}

bool pop(Array& array){
    //Return true if pop successfully, false otherwise
    //TODO
    return removeAt(array,0);
}

Soldier top(Array& array){
    //TODO
    if (array.arr!=NULL) return array.arr[0];
    else
    return Soldier();//return this if cannot get top

}

//////////////////////////////////////////////////////
/// TASK 2
//////////////////////////////////////////////////////

bool enqueue(SLinkedList& list, Soldier soldier){
    //Return true if enqueue successfully, false otherwise
    //TODO
    return insertAt(list,soldier,0);
}

bool dequeue(SLinkedList& list){
    //Return true if dequeue successfully, false otherwise
    //TODO
    return removeAt(list,list.size-1);
}

Soldier front(SLinkedList& list){
    //TODO
    if (list.size!=0){
        SoldierNode* head = list.head;
        for (int i=0;i<list.size-1;i++){
            head=head->next;
        }
        return head->data;
    }
    else
    return Soldier();//Return this if cannot get front
}

//////////////////////////////////////////////////////
/// TASK 3
//////////////////////////////////////////////////////

void reverse(SLinkedList& list){
    //TODO
    SoldierNode* head=list.head;
    for (int i=0;i<list.size;i++){
        insertAt(list,head->data,list.size-i);
        removeAt(list,0);
        head=head->next;
    }
}

//////////////////////////////////////////////////////
/// TASK 4
//////////////////////////////////////////////////////

SLinkedList merge(SLinkedList& list1, SLinkedList& list2){
    //TODO
    SoldierNode* head=list1.head;
    if (list1.head!=NULL){
        while (head->next!=NULL){
            head=head->next;
        }
        head->next=list2.head;
    }
    else{
        list1=list2;
    }
    list1.size+=list2.size;
    for(SoldierNode *head1=list1.head;head1!=NULL;head1=head1->next){
        for(SoldierNode *head2=head1->next;head2!=NULL;head2=head2->next){
            if(head1->data.HP>head2->data.HP){
                Soldier head3=head1->data;
                head1->data=head2->data;
                head2->data=head3;
            }
            else if (head1->data.HP==head2->data.HP && head1->data.isSpecial>head2->data.isSpecial){
                Soldier head3=head1->data;
                head1->data=head2->data;
                head2->data=head3;
            }
            else if (head1->data.HP==head2->data.HP && head1->data.isSpecial==head2->data.isSpecial && head1->data.ID>head2->data.ID){
                Soldier head3=head1->data;
                head1->data=head2->data;
                head2->data=head3;
            }
        }
    }
    return list1;
}

//You can write your own functions here

//End your own functions

#endif /* thirdBattle_h */
