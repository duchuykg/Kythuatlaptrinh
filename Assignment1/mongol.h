//
// Created by Nhan Nguyen on 01/03/2021.
//
#ifndef MONGOL_H
#define MONGOL_H

// The library here is concretely set, students are not allowed to include any other libraries.

string readyForBattle(const string ID[], const int NID, const string input1[], const int N1);
int decode(const string A, const string B);
string findRoute(const string input3);
string decodeVfunction(const string A, const string B);
string findBetrayals(const string input5[], const int N5);
int attack(const string input6[]);
int calculateNoOfWaitingDays(const string input7Str, const string input7Matrix[], const int k);

////////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER HERE
////////////////////////////////////////////////////////////////////////////
int check(string ID){
    int s;
    s=ID.length();
    if (ID.substr(0,3)=="VUA") return 1;
    if (ID=="THD") return 2;
    for (int i=1;i<s-3;i++){
        if (ID.substr(i,3)=="THD") return 2;
    }
    return 0;
}
string BtoD(string input1){
    int s;
    string newi;
    s=input1.length();
    for (int i=0;i<s;i+=2){
        if (input1[i]=='0' && input1[i+1]=='0') newi+="0";
        else if (input1[i]=='0' && input1[i+1]=='1') newi+="1";
        else if (input1[i]=='1' && input1[i+1]=='0') newi+="2";
        else if (input1[i]=='1' && input1[i+1]=='1') newi+="3";
        else if (input1[i]==' ') {newi+=" ";i--;}
    }
    return newi;
}
string DtoC (string input1){
    int s,count0,count1,count2,count3,dem0,dem1,dem2,dem3,ibefore,d=0;
    string newi;
    s=input1.length();
    for (int i=0;i<s;i++){
        count0=count1=count2=count3=0;
        dem0=dem1=dem2=dem3=0;
        if (input1[i]==' ' || i==s-1){
            int j;
            for (j=d;j<=i;j++){
                if (input1[j]=='0') {count0++; if (count0>7) count0=1;}
                else if (input1[j]=='1') {count1++; if (count1>7) count1=1;}
                else if (input1[j]=='2') {count2++; if (count2>7) count2=1;}
                else if (input1[j]=='3') {count3++; if (count3>7) count3=1;}
            }
            for (j=d;j<=i;j++){
                if (input1[j]=='0' && dem0==0) {
                    if (count0==1) newi+="E";
                    else if (count0==2) newi+="F";
                    else if (count0==3) newi+="G";
                    else if (count0==4) newi+="H";
                    else if (count0==5) newi+="I";
                    else if (count0==6) newi+="J";
                    else if (count0==7) newi+="K";
                    dem0++;
                    }
                else if (input1[j]=='1' && dem1==0){
                    if (count1==1) newi+="L";
                    else if (count1==2) newi+="M";
                    else if (count1==3) newi+="N";
                    else if (count1==4) newi+="O";
                    else if (count1==5) newi+="P";
                    else if (count1==6) newi+="Q";
                    else if (count1==7) newi+="R";
                    dem1++;
                    }
                else if (input1[j]=='2' && dem2==0){
                    if (count2==1) newi+="#";
                    else if (count2==2) newi+="T";
                    else if (count2==3) newi+="U";
                    else if (count2==4) newi+="V";
                    else if (count2==5) newi+="W";
                    else if (count2==6) newi+="X";
                    else if (count2==7) newi+="Y";
                    dem2++;
                    }
                 else if (input1[j]=='3' && dem3==0){
                    if (count3==1) newi+="@";
                    else if (count3==2) newi+="A";
                    else if (count3==3) newi+="S";
                    else if (count3==4) newi+="Z";
                    else if (count3==5) newi+="B";
                    else if (count3==6) newi+="C";
                    else if (count3==7) newi+="D";
                    dem3++;
                    }
            }
            if (i==s-1) d=ibefore+1; else d=i+1;
            ibefore=i;
        }
    }
     return newi;
}
string change(string newi){
    string change,change1,change2;
    int l,dem=0,count=0;
    l=newi.length();
    for (int i=0;i<l;i++){
        if (newi[i]!='#' && newi[i]!='@') dem++;
        if (dem==l) return newi;
    }
    for (int i=0;i<l;i++){
        if (newi[i]=='#'){
            int k;
            ++count;
            for (k=i+1;k<l;k++){
                if (newi[k]<=90 && newi[k]>=65) change+=newi[k];
                else if (newi[k]=='#' || newi[k]=='@'){
                    if (newi[k-1]==90) {change+="A"; break;}
                    else {change+=newi[k-1]+1;break;}
                }
                if (newi[k+1]=='\0'){
                    if (newi[k]==90) change+="A";
                    else change+=newi[l-1]+1;
                }
            }
        }
        else if (newi[i]=='@'){
            int k;
            ++count;
            change2="";
            change1="";
            for (k=i+1;k<l;k++){
                int lc=change2.length();
                if (newi[k]<=90 && newi[k]>=65) change2+=newi[k];
                else if (newi[k]=='#' || newi[k]=='@'){
                    for (int m=lc-1;m>=0;m--){
                        change1+=change2[m];
                    }
                    break;
                }
                if (newi[k+1]=='\0') {
                    for (int m=lc;m>=0;m--){
                        change1+=change2[m];}
                }
            }
            change+=change1;
        }
        else if (newi[i]!='#' && newi[i]!='@' && count==0) change+=newi[i];
    }
    return change;
}
string changecheckID(string input1, string ID){
    int l,s;
    string newi="",newi1="",newi2="",newi3="";
    char temp;
    l=input1.length();
    if (check(ID)==1){
        if (l%2==1){
            for (int i=l-1;i>=0;i--) newi+=input1[i];
        }
        else {  for (int i=l-2;i>=0;i-=2) newi1+=input1[i];
                for (int i=l-1;i>=0;i-=2) newi2+=input1[i];
                for (int i=0;i<l/2;i++) {
                    newi+=newi1[i];
                    newi+=newi2[i];
                }
        }
        for (int i=0;i<l;i++){
            if (input1[i]>=newi[i]) newi3+=input1[i];
            else newi3+=newi[i];
        }
        newi=newi3;
    }
    else if (check(ID)==2){
        for (int i=0;i<l;i++){
            if (i%3!=0) newi1+=input1[i];
        }
        s=newi1.length();
        int j;
        for (int i=0;i<s;i++){
            for (j=i+1;j<s;j++){
                if (newi1[i]>newi1[j]){
                    temp=newi1[i];
                    newi1[i]=newi1[j];
                    newi1[j]=temp;
                }
            }
        }
        newi=newi1;
    }
    else return input1;
    return newi;
}
void KMP(const string B, int *F,int m){
    int i=1,j=0;
    F[0]=0;
    while (i<m){
        if (B[i]==B[j]){
            F[i]=j+1;
            i++;
            j++;
        }
        else if(j>0)j=F[j-1];
        else {
            F[i]=0;
            i++;
        }
    }
}
int N(string input3){
    int dem1=0;
    dem1=input3.find(" ");
    return stod(input3.substr(0,dem1));
}
int B(string input3){
    int dem1=0,dem2=0;
    dem1=input3.find(" ");
    dem2=input3.find(" ",1+input3.find(" "));
    return stod(input3.substr(dem1+1,dem2-dem1-1));
}
string S(string input3){
    int dem2=0,l;
    dem2=input3.find(" ",1+input3.find(" "));
    l=input3.length();
    return input3.substr(dem2+1,l-dem2-1);
}
string changefRB(string S,int B){
    int l;
    char a;
    l=S.length();
    if (B==0) return S;
    else if (B<0) {
        for (int i=0;i<-B;i++){
            a=S[0];
            for (int j=0;j<l-1;j++){
                S[j]=S[j+1];
                if (j==l-2) S[l-1]=a;
            }
        }
    return S;
    }
    else {
        for (int i=0;i<B;i++){
            a=S[l-1];
            for (int j=l-1  ;j>0;j--){
                S[j]=S[j-1];
                if (j==1) S[0]=a;
            }
        }
    return S;}
}
string changefRN(string S, int N){
    int l,dem;
    l=S.length();
    for (int i=0;i<l;i++){
        dem=abs(N-2*i);
        if (dem%4==0) S[i]=S[i];
        else if (dem%4==1) {
            if (S[i]=='U') S[i]='D';
            else if (S[i]=='D') S[i]='L';
            else if (S[i]=='L') S[i]='R';
            else S[i]='U';
        }
        else if (dem%4==2){
            if (S[i]=='U') S[i]='L';
            else if (S[i]=='D') S[i]='R';
            else if (S[i]=='L') S[i]='U';
            else S[i]='D';
        }
        else {
            if (S[i]=='U') S[i]='R';
            else if (S[i]=='D') S[i]='U';
            else if (S[i]=='L') S[i]='D';
            else S[i]='L';
        }
    }
    return S;
}
string move(string S){
    int l,x=0,y=0;
    string newi;
    l=S.length();
    for (int i=0;i<l;i++){
        if (S[i]=='U') y++;
        else if (S[i]=='D') y--;
        else if (S[i]=='L') x--;
        else x++;
    }
    newi="("+to_string(x)+","+to_string(y)+")";
    return newi;
}
int N7(string input7Str){
    int dem1=0;
    dem1=input7Str.find(" ");
    return stod(input7Str.substr(0,dem1));
}
long long int V(string input7Str){
    long long int dem1=0,dem2=0;
    dem1=input7Str.find(" ");
    dem2=input7Str.find(" ",1+input7Str.find(" "));
    return stod(input7Str.substr(dem1+1,dem2-dem1-1));
}
int iz(string input7Str){
    int dem2=0,dem3=0;
    dem2=input7Str.find(" ",1+input7Str.find(" "));
    dem3=input7Str.find(" ",1+input7Str.find(" ",1+input7Str.find(" ")));
    return stod(input7Str.substr(dem2+1,dem3-dem2-1));
}
int jz(string input7Str){
    int dem3=0,dem4=0;
    dem3=input7Str.find(" ",1+input7Str.find(" ",1+input7Str.find(" ")));
    dem4=input7Str.find(" ",1+input7Str.find(" ",1+input7Str.find(" ",1+input7Str.find(" "))));
    return stod(input7Str.substr(dem3+1,dem4-dem3-1));
}
void StoM(long long int ***matrix,const string input7Matrix[],int k, int N7){
    int l;
    for (int i=0;i<k;i++){
        l=input7Matrix[i].length();
        int dem=0,x=0,y=0;
        for (int j=0;j<l;j++){
            if (input7Matrix[i][j]==' ') {
                matrix[i][x][y]=stod(input7Matrix[i].substr(dem,j-dem));
                dem=j+1;
                y++;
                if (y==N7) {
                    x++;
                    y=0;
                }
            }
            else if (j==l-1){
                matrix[i][x][y]=stod(input7Matrix[i].substr(dem,l-dem));
                dem=0;
                x=0;
                y=0;
            }
        }
    }
}
void mmatrix(long long int **matrix1,long long int **matrix2,long long int **A,int N7){
    for (int i=0;i<N7;i++){
        for (int j=0;j<N7;j++){
            A[i][j]=0;
            for (int k=0;k<N7;k++){
                A[i][j]+=(matrix1[i][k]*matrix2[k][j]);
            }
        }
    }
}
void multiply(long long int ***matrix,long long int **matrix1,long long int **matrix2,long long int **matrix3, int N7, int k, int V){
    for (int i=0;i<k;i++){
        if(i==0){
            for (int j=0;j<N7;j++){
                for (int k=0;k<N7;k++){
                    matrix1[j][k]=matrix[i][j][k]%V;
                }
            }
        }
        else {
            for (int j=0;j<N7;j++){
                for (int m=0;m<N7;m++){
                    matrix3[j][m]=matrix1[j][m]%V;
                }
            }
            for (int j=0;j<N7;j++){
                for (int m=0;m<N7;m++){
                    matrix2[j][m]=matrix[i][j][m]%V;
                }
            }
            mmatrix(matrix3, matrix2, matrix1, N7);
        }
	}
}
string readyForBattle(const string ID[], const int NID, const string input1[], const int N1)
{
     string input;
     string IDe=ID[0];
     for (int i=0;i<NID;i++){
        if (check(ID[i])==1 || check(ID[i])==2){
            IDe=ID[i];
        }
     }
     for (int i = 0; i < N1; i++){
        if (i==0) input+=changecheckID(change(DtoC(BtoD(input1[i]))),IDe);
        else input+=" "+changecheckID(change(DtoC(BtoD(input1[i]))),IDe);
}
    return input;
}
int decode(const string A, const string B)
{
    int la,lb,count=0;
    la=A.length();
    lb=B.length();
    int *F = new int [lb];
    KMP(B,F,lb);
    int i=0,j=0;
    while(i<la){
        if(A[i]==B[j]){
            if(j==lb-1) {count++;i++;j++;}
            else{
                i++;
                j++;
            }
        }
        else if(j>0) j=F[j-1];
        else i++;
    }
    delete []F;
return count;
}
string findRoute(const string input3)
{
    return move(changefRN(changefRB(S(input3),B(input3)),N(input3)));
}
string decodeVfunction(const string A, const string B)
{
    int lA,lB,demA=0,demB=0;
    string newi;
    lA=A.length();
    lB=B.length();
    for (int i=0;i<lA;i++){
        if (A[i]=='V') demA++;
    }
    for (int i=0;i<lB;i++){
        if (B[i]=='V') demB++;
    }
    for (int i=0;i<demA*demB;i++){
        newi+="V(";
    }
    if (demA*demB!=0) newi+='0';
    else return "0";
    for (int i=0;i<demA*demB;i++){
        newi+=')';
    }
    return newi;
}
string findBetrayals(const string input5[], const int N5)
{
    char alphabet[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int dem[26],max1,max2,max3,rank1,rank2,rank3;
    string newi;
    for (int i=0;i<26;i++){
        dem[i]=0;
    }
    for (int i=0;i<26;i++){
        for (int j=0;j<N5;j++){
            for (int k=0;k<6;k++){
                if (alphabet[i]==input5[j][k]){
                    if (k==0) dem[i]+=6;
                    else if (k==1) dem[i]+=5;
                    else if (k==2) dem[i]+=4;
                    else if (k==3) dem[i]+=3;
                    else if (k==4) dem[i]+=2;
                    else if (k==5) dem[i]+=1;
                }
            }
        }
    }
    max1=max2=max3=-1;
    rank1=rank2=rank3=-1;
    for (int i=0;i<26;i++){
        if (dem[i]>max1) {
            max1=dem[i];
            rank1=i;
        }
    }
    for (int i=0;i<26;i++){
        if (rank1==i);
        else if (dem[i]>max2) {
            max2=dem[i];
            rank2=i;
        }
    }
    for (int i=0;i<26;i++){
        if (rank1==i || rank2==i);
        else if (dem[i]>max3) {
            max3=dem[i];
            rank3=i;
        }
    }
    newi+=alphabet[rank1];
    newi+=alphabet[rank2];
    newi+=alphabet[rank3];
    return newi;
}
int attack(const string input6[])
{
    int dem[10],max1,rank1;
    for (int i=0;i<10;i++) dem[i]=0;
    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++){
            if (input6[i][j]=='2') {
                dem[i]=0;
                break;
            }
            if (input6[i][j]=='0') dem[i]++;
        }
    }
    max1=0;
    rank1=0;
    for (int i=0;i<10;i++){
        if (dem[i]>=max1) {
            max1=dem[i];
            rank1=i;
        }
    }
    if (max1==0) return -1;
    else return rank1;
}
int calculateNoOfWaitingDays(const string input7Str, const string input7Matrix[], const int k)
{
    int N7s;
    N7s=N7(input7Str);
    long long int Vs;
    Vs=V(input7Str);
    int R;
    long long int ***matrix;
    matrix = new long long int**[k];
    for (int i=0; i<k; ++i)
        matrix[i] = new long long int*[N7s];
    for (int i=0; i<k; ++i)
        for (int j=0; j<N7s; ++j)
            matrix[i][j] = new long long int[N7s];
    long long int **matrix1 = new long long int*[N7s];
        for(int i = 0; i<N7s; i++)
            matrix1[i] = new long long int[N7s];
    long long int **matrix2 = new long long int*[N7s];
        for(int i = 0; i<N7s; i++)
            matrix2[i] = new long long int[N7s];
    long long int **matrix3 = new long long int*[N7s];
        for(int i = 0; i<N7s; i++)
            matrix3[i] = new long long int[N7s];
    StoM(matrix, input7Matrix, k, N7s);
    multiply(matrix,matrix1,matrix2,matrix3,N7s,k,Vs);
    R=matrix1[iz(input7Str)][jz(input7Str)]%Vs;
    if (R<0) R+=Vs;
	for (int i=0; i<k; ++i)
        for (int j=0; j<N7s; ++j)
            delete [] matrix[i][j];
    for (int i=0; i<k; ++i)
        delete [] matrix[i];
    delete [] matrix;
    for(int i = 0; i<N7s; i++)
        delete []matrix1[i];
    delete []matrix1;
    for(int i = 0; i<N7s; i++)
        delete []matrix2[i];
    delete []matrix2;
    for(int i = 0; i<N7s; i++)
        delete []matrix3[i];
    delete []matrix3;
    return R;
}
#endif /* MONGOL_H */
