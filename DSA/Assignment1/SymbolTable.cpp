#include "SymbolTable.h"

int Count_line(string filename){
    ifstream ifs(filename);
    int number_of_lines=0;
    string line;
    while (getline(ifs,line))
    {
        ++number_of_lines;
    }
    ifs.close();
    return number_of_lines;
}

void Instructions(string filename, string *instruction, int number_of_lines){
    ifstream ifs(filename);
    for (int i=0;i<number_of_lines;i++){
        getline(ifs,instruction[i]);
    }
    ifs.close();
}

void Codes(string *instruction, string *code, int i){
    code[i]=instruction[i].substr(0,instruction[i].find(" ",0));
}

bool Check_identifier_name(string identifier){
    int l=identifier.length();
    if (l<=0) return 0;
    if (identifier[0]<'a'||identifier[0]>'z') return 0;
    for (int i=1;i<l-1;i++){
        if ((identifier[i]>='0' && identifier[i]<='9')||identifier[i]=='_'||(identifier[i]>='A' && identifier[i]<='Z')||(identifier[i]>='a'&&identifier[i]<='z'));
        else return 0;
    }
    return 1;
}

bool Check_type(string type){
    if (type=="number" || type=="string") return 1;
    return 0;
}

void Identifier_names(string *instruction, int number_of_lines, string **identifier_name_insert, int i, int level){
    int space1=instruction[i].find(" ",0);
    int space2=instruction[i].find(" ",space1+1);
    identifier_name_insert[level][i]=instruction[i].substr(space1+1,space2-space1-1);
}

void Types_Values(string *instruction, int number_of_lines, string **type, int i, int level){
    int space2=instruction[i].find(" ",instruction[i].find(" ",0)+1);
    type[level][i]=instruction[i].substr(space2+1);
}

void Check_Redeclared(string **identifier_name, int *checkI, int number, int level, int *save_level){
    if (number==0){
        checkI[number]=1;
    }
    int save=save_level[level];
    for (int i=save;i<number;i++){
        if (identifier_name[level][number]==identifier_name[level][i]){
            checkI[number]=0;
            break;
        }
        else if (i==number-1) checkI[number]=1;
    }
}

void Check_Undeclared(string **identifier_name_assign, string **identifier_name_insert,int number_of_lines, int *checkU, int level, int number, int *save_level){
    checkU[number]=0;
    for (int a=0;a<=level;a++){
        int save=save_level[a];
        for (int i=save;i<number;i++){
            if (identifier_name_assign[level][number]==identifier_name_insert[a][i]){
                checkU[number]=1;
                break;
            }
        }
    }
}

int Check_value(string value, string **identifier_name_insert, string **type, int level, int number, int a, int b, int *save_level){
    for (int i=level;i>=0;i--){
        int save=save_level[i];
        for (int j=save;j<number;j++){
            if (value==identifier_name_insert[i][j]){
                if (type[i][j]==type[a][b]) return 1;
                else return -1;
            }
        }
    }
    return 0;
}

bool Check_number(string number){
    int l=number.length();
    for (int i=0;i<l;i++){
        if (number[i]>='0' && number[i]<='9') return 1;
        else return 0;
    }
    return 0;
}

bool Check_string(string stringh){
    int l=stringh.length();
    if (l<=1) return 0;
    if (stringh[0]!=39 || stringh[l-1]!=39) return 0;
    for (int i=1;i<l-1;i++){
        if ((stringh[i]>='0' && stringh[i]<='9')||stringh[i]==' '||(stringh[i]>='A' && stringh[i]<='Z')||(stringh[i]>='a'&&stringh[i]<='z'));
        else return 0;
    }
    return 1;
}

bool Check_value(string value){
    if (Check_number(value)==0&& Check_string(value)==0&&Check_identifier_name(value)==0) return 0;
    else return 1;
}

void Print_RPrint(int number_of_lines, string **identifier_name_insert, string *identifier_name_print, int *level_print, int level, string x, int *save_level){
    int j=0, minb=-1;
    for (int a=0; a<=level; ++a){
        int save=save_level[a];
        for (int b=save;b<number_of_lines;b++){
            if (identifier_name_insert[a][b]!=""){
                identifier_name_print[j]=identifier_name_insert[a][b];
                level_print[j]=a;
                ++j;
            }
        }
    }
    for (int b=0;b<j;b++){
        for (int c=b+1;c<j;c++){
            if (identifier_name_print[b]==identifier_name_print[c]){
                identifier_name_print[b]="";
                level_print[b]=-1;
            }
        }
    }
    for (int b=0; b<j;b++){
        if (level_print[b]!=-1){
            minb=b;
            break;
        }
    }
    if (x=="RPRINT"){
        for (int b=j-1;b>=0;b--){
            if (level_print[b]!=-1 && b!=minb) cout<<identifier_name_print[b]<<"//"<<level_print[b]<<" ";
            else if (level_print[b]!=-1 && b==minb) cout<<identifier_name_print[b]<<"//"<<level_print[b]<<endl;
        }
    }
    else if (x=="PRINT"){
        for (int b=0;b<j;b++){
            if (level_print[b]!=-1 && b!=j-1) cout<<identifier_name_print[b]<<"//"<<level_print[b]<<" ";
            else if (level_print[b]!=-1 && b==j-1) cout<<identifier_name_print[b]<<"//"<<level_print[b]<<endl;
        }
    }
}

void SymbolTable::run(string filename)
{
    int number_of_lines, level=0, start=0, finish=0, *save_level;
    number_of_lines=Count_line(filename);

    string *instruction, *code, *identifier_name_lookup, *identifier_name_print, instruction_fail;
    int *level_print, fail=-1;

    instruction=new string [number_of_lines];
    code=new string [number_of_lines];
    identifier_name_lookup=new string [number_of_lines];
    identifier_name_print=new string [number_of_lines*number_of_lines];
    level_print=new int [number_of_lines*number_of_lines];
    save_level=new int [number_of_lines];
    for (int i=0;i<number_of_lines;i++){
        save_level[i]=0;
    }

    Instructions(filename, instruction, number_of_lines);

    string **identifier_name_insert = new string*[number_of_lines];
    for(int i = 0; i<number_of_lines; i++)
        identifier_name_insert[i] = new string [number_of_lines];

    string **identifier_name_assign = new string*[number_of_lines];
    for(int i = 0; i<number_of_lines; i++)
        identifier_name_assign[i] = new string [number_of_lines];

    string **type = new string*[number_of_lines];
    for(int i = 0; i<number_of_lines; i++)
        type[i] = new string [number_of_lines];

    string **value = new string*[number_of_lines];
    for(int i = 0; i<number_of_lines; i++)
        value[i] = new string [number_of_lines];

    for (int i=0;i<number_of_lines;i++){
        Codes(instruction, code, i);
        if (code[i]=="INSERT"){
            Identifier_names(instruction, number_of_lines, identifier_name_insert, i, level);
            Types_Values(instruction, number_of_lines, type, i, level);
            if (Check_identifier_name(identifier_name_insert[level][i])==0 || Check_type(type[level][i])==0 ){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            int *checkI;
            checkI=new int [number_of_lines];
            for (int a=0;a<number_of_lines;a++){
                checkI[a]=0;
            }
            Check_Redeclared(identifier_name_insert, checkI, i, level, save_level);

            if (checkI[i]==1){
                cout<<"success"<<endl;
            }
            else{
                delete[] checkI;
                fail=1;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            delete[] checkI;
        }
        else if (code[i]=="ASSIGN"){
            Identifier_names(instruction, number_of_lines, identifier_name_assign, i, level);
            Types_Values(instruction, number_of_lines, value, i, level);
            if (Check_identifier_name(identifier_name_assign[level][i])==0 || Check_value(value[level][i])==0 ){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            int *checkU;
            checkU=new int [number_of_lines];
            for (int a=0;a<number_of_lines;a++){
                checkU[a]=-1;
            }
            Check_Undeclared(identifier_name_assign, identifier_name_insert, number_of_lines, checkU, level, i, save_level);
            if (checkU[i]==1){
                for (int x=level;x>=0;x--){
                    int save=save_level[x];
                    for (int y=save;y<i;y++){
                        if (identifier_name_assign[level][i]==identifier_name_insert[x][y]){
                            if (Check_number(value[level][i])==0 && Check_string(value[level][i])==0){
                                if (Check_value(value[level][i], identifier_name_insert, type, level, i, x, y, save_level)==1){
                                    cout<<"success"<<endl;
                                    x=0;
                                    break;
                                }
                                else if (Check_value(value[level][i], identifier_name_insert, type, level, i, x, y, save_level)==0){
                                    delete[] checkU;
                                    fail=2;
                                    instruction_fail=instruction[i];
                                    goto Check_all;
                                }
                                else{
                                    delete[] checkU;
                                    fail=3;
                                    instruction_fail=instruction[i];
                                    goto Check_all;
                                }
                            }
                            if (type[x][y]=="number"){
                                if (Check_number(value[level][i])==1){
                                    cout<<"success"<<endl;
                                    x=0;
                                    break;
                                }
                                else{
                                    delete[] checkU;
                                    fail=3;
                                    instruction_fail=instruction[i];
                                    goto Check_all;
                                }
                            }
                            else if (type[x][y]=="string"){
                                if (Check_string(value[level][i])==1){
                                    cout<<"success"<<endl;
                                    x=0;
                                    break;
                                }
                                else{
                                    delete[] checkU;
                                    fail=3;
                                    instruction_fail=instruction[i];
                                    goto Check_all;
                                }
                            }
                            else{
                                delete[] checkU;
                                fail=2;
                                instruction_fail=instruction[i];
                                goto Check_all;
                            }
                        }
                    }
                }
            }
            else{
                delete[] checkU;
                fail=2;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            delete[] checkU;
        }
        else if (code[i]=="BEGIN"){
            if (code[i]!=instruction[i]){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            ++level;
            start++;
        }
        else if (code[i]=="END"){
            if (code[i]!=instruction[i]){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            save_level[level]=i;
            --level;
            finish++;
            if (level<0){
                fail=4;
                instruction_fail=instruction[i];
                goto Check_all;
            }
        }
        else if (code[i]=="LOOKUP"){
            int space1=instruction[i].find(" ",0);
            int space2=instruction[i].find(" ",space1+1);
            identifier_name_lookup[i]=instruction[i].substr(space1+1,space2-space1-1);
            if (Check_identifier_name(identifier_name_lookup[i])==0 || instruction[i]!=code[i]+" "+identifier_name_lookup[i]){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            for (int a=level;a>=0;a--){
                int save=save_level[a];
                for (int b=save;b<number_of_lines;b++){
                    if (identifier_name_lookup[i]==identifier_name_insert[a][b]){
                        cout<<a<<endl;
                        a=-1;
                        break;
                    }
                }
                if (a==0){
                    fail=2;
                    instruction_fail=instruction[i];
                    goto Check_all;
                }
            }
        }
        else if (code[i]=="PRINT"){
            if (code[i]!=instruction[i]){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            Print_RPrint(number_of_lines, identifier_name_insert, identifier_name_print, level_print, level, "PRINT", save_level);
        }
        else if (code[i]=="RPRINT"){
            if (code[i]!=instruction[i]){
                fail=5;
                instruction_fail=instruction[i];
                goto Check_all;
            }
            Print_RPrint(number_of_lines, identifier_name_insert, identifier_name_print, level_print, level, "RPRINT", save_level);
        }
        else{
            fail=5;
            instruction_fail=instruction[i];
            goto Check_all;
        }
    }
    Check_all:
    for(int i = 0; i<number_of_lines; i++)
        delete []identifier_name_insert[i];
    delete []identifier_name_insert;

    for(int i = 0; i<number_of_lines; i++)
        delete []identifier_name_assign[i];
    delete []identifier_name_assign;

    for(int i = 0; i<number_of_lines; i++)
        delete []type[i];
    delete []type;

    for(int i = 0; i<number_of_lines; i++)
        delete []value[i];
    delete []value;

    delete[] instruction;
    delete[] code;
    delete[] identifier_name_lookup;
    delete[] identifier_name_print;
    delete[] level_print;
    delete[] save_level;

    if (fail==1) throw Redeclared(instruction_fail);
    else if (fail==2) throw Undeclared(instruction_fail);
    else if (fail==3) throw TypeMismatch(instruction_fail);
    else if (fail==4) throw UnknownBlock();
    else if (fail==5) throw InvalidInstruction(instruction_fail);

    if (start!=finish){
        throw UnclosedBlock(level);
    }
}
