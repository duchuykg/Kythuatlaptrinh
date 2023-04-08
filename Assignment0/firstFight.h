/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2021
    * Author: Nguyen Thanh Nhan
    * Date: 08.02.2021
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef firstFight_h
#define firstFight_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int getReady(int& HP, const int& ID, int& M, const int& E1){
    //Complete this function to gain point on task 1
    int h,J,x,a,b,c;
    h=(E1-100)%64;
    J=HP%100;
    x=E1%4+1;
    a=E1%10;
    c=HP%10;
    if (M>1000) M=1000; else if (M<0) M=0;
    if (HP>1000) HP=1000; else if (HP<0) HP=0;
    if (a==2 || a==3 || a==5 || a==7) b=2*a; else b=1;
    if (E1<100 || E1>500) return -999;
    if (E1>=100 && E1<=199){
            if (ID==0){
                if (HP>=500 && M%2==1 && J>h && M>=300)
                    {HP+=50;
                     if (HP>1000) HP=1000;
                     M-=300;
                     if (M<0) M=0;}
                else if (M%2==0 && J>h && M>=200)
                    {HP+=25;
                     if (HP>1000) HP=1000;
                     M-=200;
                     if (M<0) M=0;}}
            else if (ID==1) {HP=HP+50+25;if (HP>1000) HP=1000;}
            else if (ID==2) HP=HP; return HP+M;}
    else if (E1>=200 && E1<=299) {
            if (ID==0) {
                if (M%2==1&&x==1&&M>=190)
                    {HP+=5; if (HP>1000) HP=1000;
                     M-=190; if (M<0) M=0;}
                else if (M%2==1&&x==3&&M>=200)
                    {HP+=9; if (HP>1000) HP=1000;
                     M-=200; if (M<0) M=0;}
                else if (M%2==0&&x==2&&M>=195)
                    {HP+=7; if (HP>1000) HP=1000;
                     M-=195; if (M<0) M=0;}
                else if (M%2==0&&x==4&&M>=205)
                    {HP+=11; if (HP>1000) HP=1000;
                     M-=205; if (M<0) M=0;}}
            else if (ID==1||ID==2){
                if (x==1 && M>=190)
                    {HP+=5; if (HP>1000) HP=1000;
                     M-=190; if (M<0) M=0;}
                else if (x==3&&M>=200)
                    {HP+=9; if (HP>1000) HP=1000;
                     M-=200; if (M<0) M=0;}
                else if (x==2&&M>=195)
                    {HP+=7; if (HP>1000) HP=1000;
                     M-=195; if (M<0) M=0;}
                else if (x==4&&M>=205)
                    {HP+=11; if (HP>1000) HP=1000;
                     M-=205; if (M<0) M=0;}} return HP+M;}
    else if (E1>=300 && E1<=399) {
            if (ID==0 || ID==2){
                if (HP>=600 && (c==2||c==3||c==5||c==7) && M>=500)
                    {HP=ceil(HP+HP*b*0.02); if (HP>1000) HP=1000;
                     M-=500; if (M<0) M=0;}
                else if (HP>=600 && (c==0||c==1||c==4||c==6||c==8||c==9) && M>=300)
                    {HP=ceil(HP+HP*b*0.01); if (HP>1000) HP=1000;
                     M-=300; if (M<0) M=0;}}
            else if (ID==1) {
                if (HP>=600 && (c==2||c==3||c==5||c==7)&& M>=500)
                    {HP+=200; if (HP>1000) HP=1000;
                     M-=500; if (M<0) M=0;}
                else if (HP>=600 && (c==0||c==1||c==4||c==6||c==8||c==9) && M>=300)
                    {HP=ceil(HP+HP*b*0.01); if (HP>1000) HP=1000;
                     M-=300; if (M<0) M=0;}
            }return HP+M;}
     else if (E1>=400 && E1<=499) {
            if (E1%5==0) HP=ceil(HP-HP*0.1);
            else HP=HP; return HP+M;}
     else if (E1==500)
            {HP=ceil(HP*0.75);
             M=ceil(M*0.75); return HP+M;}
return -999;}
int firstBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E2){
    //Complete this function to gain point on task 2
    int u;
    if (E2<100 || E2>=500) return -999;
    if (E2>=100 && E2<=199){
            HP1=ceil(HP1+HP1*0.1);
            HP2=ceil(HP2+HP2*0.3); if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
        if(ID1==1 && ID2==2)  {HP1=ceil(HP1-HP1*0.2); return 0;}
        else if (ID1==1 && ID2==0) {HP2=0;  HP1=ceil(HP1-HP1*0.2); return 1;}
        else if (ID1==0 && ID2==2) {HP1=0; return -1;}
        else if (ID1==0 && ID2==0){
                u=ceil((2.0*HP1*HP2)/(HP1+HP2));
                const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);}
                }
    else if (E2>=200 && E2<=299){
            HP1=ceil(HP1+HP1*0.7);
            HP2=ceil(HP2+HP2*0.2); if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
        if(ID1==1 && ID2==2) { HP1=ceil(HP1-HP1*0.2); return 0;}
        else if (ID1==1 && ID2==0) {HP2=0;  HP1=ceil(HP1-HP1*0.2); return 1;}
        else if (ID1==0 && ID2==2) {HP1=0; return -1;}
        else if (ID1==0 && ID2==0){
                u=ceil((2.0*HP1*HP2)/(HP1+HP2));
                const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);
                }}
    else if (E2>=300 && E2<=399){
            if (E2<350){HP1=HP1+30;if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
        if(ID1==1 && ID2==2) { HP1=ceil(HP1-HP1*0.2);return 0;}
        else if (ID1==1 && ID2==0) {HP2=0; HP1=ceil(HP1-HP1*0.2); return 1;}
        else if (ID1==0 && ID2==2) {HP1=0; return -1;}
        else if (ID1==0 && ID2==0){
                 u=ceil((2.0*HP1*HP2)/(HP1+HP2));
                const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);
                }}
            else {  HP1=HP1+E2%100;if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
        if(ID1==1 && ID2==2) { HP1=ceil(HP1-HP1*0.2);return 0;}
        else if (ID1==1 && ID2==0) {HP2=0; HP1=ceil(HP1-HP1*0.2); return 1;}
        else if (ID1==0 && ID2==2) {HP1=0; return -1;}
        else if (ID1==0 && ID2==0){
                 u=ceil((2.0*HP1*HP2)/(HP1+HP2));
                const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);
                }}}
    else if (E2>=400 && E2<=499){
            HP1=ceil(HP1+HP1*0.3);
            HP2=ceil(HP2-HP2*0.2);if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
            HP1=ceil(HP1*0.5); if (HP1>1000) HP1=1000;
            if(ID1==1 && ID2==2) { HP1=ceil(HP1-HP1*0.2);return 0;}
        else if (ID1==1 && ID2==0) {HP2=0; HP1=ceil(HP1-HP1*0.2); return 1;}
        else if (ID1==0 && ID2==2) {HP1=0; return -1;}
        else if (ID1==0 && ID2==0){
                 u=ceil((2.0*HP1*HP2)/(HP1+HP2));
                const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);
                }}
    const int a=HP1;
    if (HP1<=0) HP1=0; else if (HP2<=0) HP2=0;
    HP1=ceil(HP1-HP1*0.2);
    if (a>HP2) return 1; else if (a==HP2) return 0; else return -1;
return -999;}
int secondBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E3){
    //Complete this function to gain point on task 3
    int u;
    if (E3<100 || E3>=300) return -999;
    HP1=ceil(HP1+HP1*0.4);
    HP2=ceil(HP2+HP2*0.6);
    if (HP1>1000) HP1=1000; if (HP2>1000) HP2=1000;
    if (E3>=100 && E3<=199){
        if(ID1==1 && ID2==2) {HP1*=2; if (HP1>1000) HP1=1000;return 0;}
        else if (ID1==1 && ID2==0) {HP1*=2; if (HP1>1000) HP1=1000; HP2=0; return 1;}
        else if (ID1==0 && ID2==2) return -1;
        else if(ID1==0 && ID2==0){
                HP2=ceil(HP2-HP2*0.05);
                u=ceil((2.0*HP1*HP2)/(HP1+HP2));
               const int t=HP1;
                HP1=HP1-abs(HP2-u);
                HP2=HP2-abs(t-u);
                if (HP1<=0) HP1=0; if (HP2<=0) HP2=0;
                if (HP1>HP2) return 1; else if (HP1==HP2) return 0; else {HP1=t;return -1;}
                }}
    else if (E3>=200 && E3<=299){
        if (ID1==1) {HP1*=2; if (HP1>1000) HP1=1000;}
        if (ID2==2) HP2=HP2; else
        HP2=ceil(HP2-HP2*0.05);
        return 0;
                }
return -999;}

int finalBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E4){
    //Complete this function to gain point on task 4
    if (E4<100 && E4>=300) return -999;
    if (E4>=100 && E4<=199){
            if (ID2==0) HP2=ceil(HP2*0.1);
            else if (ID2==2) HP2=ceil(HP2*0.3);
        return 0;
                }
    else if (E4>=200 && E4<=299){
            HP2=0;
        return 1;
                }
return -999;
}
////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* firstFight_h */
