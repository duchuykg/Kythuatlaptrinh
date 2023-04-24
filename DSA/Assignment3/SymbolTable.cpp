#include "SymbolTable.h"

bool Check_identifier(string identifier)
{
    int l = identifier.length();
    if (l <= 0) return 0;
    if (identifier[0] < 'a' || identifier[0] > 'z') return 0;
    for (int i = 1; i < l; i++)
    {
        if ((identifier[i] >= '0' && identifier[i] <= '9') || identifier[i] == '_' || (identifier[i]>='A' && identifier[i] <= 'Z') || (identifier[i] >= 'a' && identifier[i] <= 'z'));
        else return 0;
    }
    if (identifier == "string" || identifier == "number" || identifier == "void") return 0;
    return 1;
}

bool Check_string(string stringh)
{
    int l = stringh.length();
    if (l <= 1) return 0;
    if (stringh[0] != (char)39 || stringh[l-1] != (char)39) return 0;
    for (int i = 1; i < l - 1; i++)
    {
        if ((stringh[i] >= '0' && stringh[i] <= '9') || stringh[i] == ' ' || (stringh[i] >= 'A' && stringh[i] <= 'Z') || (stringh[i] >= 'a' && stringh[i] <= 'z'));
        else return 0;
    }
    return 1;
}

bool Check_number(string number)
{
    int l = number.length();
    if (l <= 0) return 0;
    for (int i = 0; i < l; i++)
    {
        if (number[i] >= '0' && number[i] <= '9');
        else return 0;
    }
    return 1;
}

bool Check_func(string identifier_num, string &identifier, int &num_of_parameters)
{
    int l = identifier_num.length();
    bool func = 0;
    for (int i = 0; i < l; i++)
    {
        if (identifier_num[i] == ' ')
        {
            func = 1;
            identifier = identifier_num.substr(0, i);
            string num_of_p;
            num_of_p = identifier_num.substr(i + 1, l - i - 1);
            if (Check_identifier(identifier) == 0) return 0;
            if (Check_number(num_of_p) == 0) return 0;
            num_of_parameters = stod(num_of_p);
        }
    }
    if (func == 0) return 0;
    return 1;
}

bool Check_val(string val)
{
    if (Check_string(val) == 1 || Check_number(val) == 1 || Check_identifier(val) == 1) return 1;
    else
    {
        int l = val.length();
        if (l <= 2) return 0;
        if (val[l - 1] != ')') return 0;
        string func_identifier = "";
        string fu = "";
        for (int i = 0; i < l; i++)
        {
            if (val[i] == '(')
            {
                func_identifier = val.substr(0, i);
                fu = val.substr(i, l - i);
                break;
            }
        }
        if (Check_identifier(func_identifier) == 0) return 0;
        if (fu == "()") return 1;
        int h = fu.length();
        int a = 1;
        for (int i = 1; i < h; i++)
        {
            if (fu[i] == ',')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
                a = i + 1;
            }
            if (fu[i] == ')')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
            }
        }
    }
    return 1;
}

bool Check_call(string val)
{
        int l = val.length();
        if (l <= 2) return 0;
        if (val[l - 1] != ')') return 0;
        string func_identifier = "";
        string fu = "";
        for (int i = 0; i < l; i++)
        {
            if (val[i] == '(')
            {
                func_identifier = val.substr(0, i);
                fu = val.substr(i, l - i);
                break;
            }
        }
        if (Check_identifier(func_identifier) == 0) return 0;
        if (fu == "()") return 1;
        int h = fu.length();
        int a = 1;
        for (int i = 1; i < h; i++)
        {
            if (fu[i] == ',')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
                a = i + 1;
            }
            if (fu[i] == ')')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
            }
        }
        return 1;
}

bool Check_val_func(string val, string &func_identifier, string &fu)
{
        int l = val.length();
        if (l <= 2) return 0;
        if (val[l - 1] != ')') return 0;
        for (int i = 0; i < l; i++)
        {
            if (val[i] == '(')
            {
                func_identifier = val.substr(0, i);
                fu = val.substr(i, l - i);
                break;
            }
        }
        if (Check_identifier(func_identifier) == 0) return 0;
        if (fu == "()") return 1;
        int h = fu.length();
        int a = 1;
        for (int i = 1; i < h; i++)
        {
            if (fu[i] == ',')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
                a = i + 1;
            }
            if (fu[i] == ')')
            {
                if(Check_string(fu.substr(a, i - a)) == 1 || Check_identifier(fu.substr(a, i - a)) == 1 || Check_number(fu.substr(a, i - a)) == 1);
                else return 0;
            }
        }
        return 1;
}

int linearProbing(long long key, int size, int i, int c1, int c2)
{
    int h = key % size;
    return (h + c1 * i) % size;
}

int quadraticProbing(long long key, int size, int i, int c1, int c2)
{
    int h = key % size;
    return (h + c1 * i + c2 * i * i) % size;
}

int doubleHashing(long long key, int size, int i, int c1, int c2)
{
    int h1 = key % size;
    int h2 = 1 + (key % (size - 2));
    return (h1 + c1 * i * h2) % size;
}

void SymbolTable::Check_compare(Node head, int level, string fu, string instruction)
{
    int l_fu = fu.length();
    int count_func = 0, a = 1, b = 0;

    for (int i = 1; i < l_fu; i++)
    {
        if (fu[1] == ')'){
            count_func = 0;
            break;
        }
        if (fu[i] == ',') count_func++;
        if (fu[i] == ')') count_func++;
    }
    if (head.num_of_parameter != count_func) throw TypeMismatch(instruction);
    else if (count_func == 0) return;
    string func[count_func];
    for (int i = 0; i < count_func; i++)
    {
        func[i] = "";
    }
    for (int i = 1; i < l_fu; i++)
    {
        if (fu[i] == ',')
        {
            func[b] = fu.substr(a, i - a);
            b++;
            a = i + 1;
        }
        if (fu[i] == ')')
        {
            func[b] = fu.substr(a, i - a);
        }
    }

    for (int i = 0; i < count_func; i++)
    {
        int numb = num;
        if (head.type_func[i] == 0)
        {
            if (Check_number(func[i]) == 1) head.type_func[i] = 1;
            else if (Check_string(func[i]) == 1) head.type_func[i] = 2;
            else if (Check_identifier(func[i]) == 1)
            {
                bool check = 0;
                for (int j = level; j >= 0; j--)
                {
                    num = numb;
                    Node pNew(func[i], j);
                    int x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw TypeMismatch(instruction);
                        check = 1;
                        head.type_func[i] = data[x].type;
                        if (head.type_func[i] == 0) throw TypeCannotBeInferred(instruction);
                        break;
                    }
                }
                numb = num;
                if (check == 0) throw Undeclared(func[i]);
            }
        }
        else if (head.type_func[i] == 1)
        {
            if (Check_number(func[i]) == 1);
            else if (Check_string(func[i]) == 1) throw TypeMismatch(instruction);
            else if (Check_identifier(func[i]) == 1)
            {
                bool check = 0;
                for (int j = level; j >= 0; j--)
                {
                    num = numb;
                    Node pNew(func[i], j);
                    int x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw TypeMismatch(instruction);
                        check = 1;
                        if (data[x].type == 0) data[x].type = 1;
                        else if (data[x].type == 1);
                        else if (data[x].type == 2) throw TypeMismatch(instruction);
                        break;
                    }
                }
                numb = num;
                if (check == 0) throw Undeclared(func[i]);
            }
        }
        else if (head.type_func[i] == 2)
        {
            if (Check_string(func[i]) == 1);
            else if (Check_number(func[i]) == 1) throw TypeMismatch(instruction);
            else if (Check_identifier(func[i]) == 1)
            {
                bool check = 0;
                for (int j = level; j >= 0; j--)
                {
                    num = numb;
                    Node pNew(func[i], j);
                    int x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw TypeMismatch(instruction);
                        check = 1;
                        if (data[x].type == 0) data[x].type = 2;
                        else if (data[x].type == 1) throw TypeMismatch(instruction);
                        else if (data[x].type == 2);
                        break;
                    }
                }
                if (check == 0) throw Undeclared(func[i]);
            }
        }
    }
}

void SymbolTable::run(string filename)
{
    ifstream ifs(filename);
    int number_of_line = 0;
    string line;
    while (getline(ifs, line))
    {
        ++ number_of_line;
    }
    ifs.close();

    if (number_of_line == 0) throw InvalidInstruction("");

    ifstream ifs0(filename);
    string instruction[number_of_line];
    for (int i = 0; i < number_of_line; i++)
    {
        getline(ifs0, instruction[i]);
    }
    ifs0.close();

    ifstream ifs1(filename);
    string code = "";
    ifs1 >> code;

    if (code == "LINEAR")
    {
        string size0 = "", c0 = "";
        ifs1 >> size0 >> c0;
        int ls = size0.length(), lc0 = c0.length();

        if (ls > 6 || lc0 > 6) throw InvalidInstruction(instruction[0]);
        if (instruction[0] != code + " " + size0 + " " + c0) throw InvalidInstruction(instruction[0]);
        if (Check_number(size0) == 0 || Check_number(c0) == 0) throw InvalidInstruction(instruction[0]);
        else
        {
            size = stoi(size0);
            c1 = stoi(c0);
            c2 = 0;
            hp = linearProbing;
        }
    }
    else if (code == "QUADRATIC")
    {
        string size0 ="", c01 = "", c02 = "";
        ifs1 >> size0 >> c01 >> c02;
        int ls = size0.length(), lc01 = c01.length(), lc02 = c02.length();

        if (ls > 6 || lc01 > 6 || lc02 > 6) throw InvalidInstruction(instruction[0]);
        if (instruction[0] != code + " " + size0 + " " + c01 + " " + c02) throw InvalidInstruction(instruction[0]);
        if (Check_number(size0) == 0 || Check_number(c01) == 0 || Check_number(c02) == 0) throw InvalidInstruction(instruction[0]);
        else
        {
            size = stoi(size0);
            c1 = stoi(c01);
            c2 = stoi(c02);
            hp = quadraticProbing;
        }
    }
    else if (code == "DOUBLE")
    {
        string size0 = "", c0 = "";
        ifs1 >> size0 >> c0;
        int ls = size0.length(), lc0 = c0.length();

        if (ls > 6 || lc0 > 6) throw InvalidInstruction(instruction[0]);
        if (instruction[0] != code + " " + size0 + " " + c0) throw InvalidInstruction(instruction[0]);
        if (Check_number(size0) == 0 || Check_number(c0) == 0) throw InvalidInstruction(instruction[0]);
        else
        {
            size = stoi(size0);
            c1 = stoi(c0);
            c2 = 0;
            hp = doubleHashing;
        }
    }
    else throw InvalidInstruction(instruction[0]);

    createHash(size, c1, c2, hp);
    int level = 0;
    for (int i = 1; i < number_of_line; i++)
    {
        num = 0;
        string code = "", identifier_num = "";
        ifs1 >> code;

        if (code == "INSERT")
        {
            ifs1.ignore();
            getline(ifs1, identifier_num);
            if (instruction[i] != code + " " + identifier_num) throw InvalidInstruction(instruction[i]);
            if (Check_identifier(identifier_num) == 1)
            {
                Node pNew(identifier_num, level, 0, 0, 0);
                int x = search(pNew);
                if (x == -1)
                {
                    int y = insert(pNew);
                    if (y == -1) throw Overflow(instruction[i]);
                    cout << num << endl;
                }
                else throw Redeclared(identifier_num);
            }
            else
            {
                string identifier = "";
                int num_of_parameters = 0;
                bool func = Check_func(identifier_num, identifier, num_of_parameters);

                if (func == 0) throw InvalidInstruction(instruction[i]);
                if (level != 0) throw InvalidDeclaration(identifier);

                Node pNew(identifier, level, num_of_parameters, 1, 0);
                int x = search(pNew);
                if (x == -1)
                {
                    int y = insert(pNew);
                    if (y == -1) throw Overflow(instruction[i]);
                }
                else throw Redeclared(identifier);
                cout << num << endl;
            }
        }
        else if (code == "ASSIGN")
        {
            string identifier = "";
            string value = "";
            ifs1 >> identifier;
            ifs1.ignore();
            getline(ifs1, value);

            if (instruction[i] != code + " " + identifier + " " + value) throw InvalidInstruction(instruction[i]);
            if (Check_identifier(identifier) == 0 || Check_val(value) == 0) throw InvalidInstruction(instruction[i]);

            bool check = 0;
            int numb = num;
            if (Check_number(value) == 1)
            {
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(identifier, j);
                    int x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw TypeMismatch(instruction[i]);
                        if (data[x].type == 0 || data[x].type == 1)
                        {
                            data[x].type = 1;
                            data[x].value = value;
                            check = 1;
                            cout << num << endl;
                        }
                        else throw TypeMismatch(instruction[i]);
                    }
                }
                if (check == 0) throw Undeclared(identifier);
            }
            else if (Check_string(value) == 1)
            {
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(identifier, j);
                    int x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw TypeMismatch(instruction[i]);
                        if (data[x].type == 0 || data[x].type == 2)
                        {
                            data[x].type = 2;
                            data[x].value = value;
                            check = 1;
                            cout << num << endl;
                        }
                        else throw TypeMismatch(instruction[i]);
                    }
                }
                if (check == 0) throw Undeclared(identifier);
            }
            else if (Check_identifier(value) == 1)
            {
                int x = 0;
                int y = 0;
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(value, j);
                    x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 1) throw InvalidInstruction(instruction[i]);
                        check = 1;
                        break;
                    }
                }
                numb = num;
                if (check == 0) throw Undeclared(value);
                check = 0;
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew1(identifier, j);
                    y = search(pNew1);
                    if (y != -1)
                    {
                        if (data[y].func == 1) throw TypeMismatch(instruction[i]);
                        check = 1;
                        if (data[x].type == 0 && data[y].type == 0) throw TypeCannotBeInferred(instruction[i]);
                        else if (data[x].type == 0)
                        {
                            data[x].type = data[y].type;
                            data[x].value = data[y].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else if (data[y].type == 0)
                        {
                            data[y].type = data[x].type;
                            data[y].value = data[x].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else if (data[x].type == data[y].type)
                        {
                            data[y].value = data[x].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else throw TypeMismatch(instruction[i]);
                        break;
                    }
                }
                if (check == 0) throw Undeclared(identifier);
            }
            else
            {
                string func_identifier = "";
                string fu = "";
                Check_val_func(value, func_identifier, fu);
                bool check = 0;
                int x = 0;
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(func_identifier, j);
                    x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 0) throw TypeMismatch(instruction[i]);
                        check = 1;
                        break;
                    }
                }
                numb = num;
                if (check == 0) throw Undeclared(func_identifier);
                Check_compare(data[x], level, fu, instruction[i]);
                numb = num;
                if (data[x].type == 3) throw TypeMismatch(instruction[i]);
                check = 0;
                int y = 0;
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(identifier, j);
                    y = search(pNew);
                    if (y != -1)
                    {
                        if (data[y].func == 1) throw TypeMismatch(instruction[i]);
                        check = 1;
                        if (data[x].type == 0 && data[y].type == 0) throw TypeCannotBeInferred(instruction[i]);
                        else if (data[x].type == 0)
                        {
                            data[x].type = data[y].type;
                            data[x].value = data[y].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else if (data[y].type == 0 && data[x].type != 3)
                        {
                            data[y].type = data[x].type;
                            data[y].value = data[x].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else if (data[x].type == data[y].type && data[x].type != 3)
                        {
                            data[y].value = data[x].value;
                            check = 1;
                            cout << num << endl;
                        }
                        else throw TypeMismatch(instruction[i]);
                        check = 1;
                        break;
                    }
                }
                if (check == 0) throw Undeclared(identifier);
            }
        }
        else if (code == "CALL")
        {
            string call_exp = "";
            ifs1.ignore();
            getline(ifs1, call_exp);

            if (instruction[i] != code + " " + call_exp) throw InvalidInstruction(instruction[i]);
            if (Check_call(call_exp) == 0) throw InvalidInstruction(instruction[i]);

                string func_identifier = "";
                string fu = "";

                Check_val_func(call_exp, func_identifier, fu);
                bool check = 0;
                int x = 0;
                int numb = num;
                for (int j = level; j >=0; j--)
                {
                    num = numb;
                    Node pNew(func_identifier, j);
                    x = search(pNew);
                    if (x != -1)
                    {
                        if (data[x].func == 0) throw TypeMismatch(instruction[i]);
                        check = 1;
                        data[x].type = 3;
                        break;
                    }
                }
                if (check == 0) throw Undeclared(func_identifier);
                Check_compare(data[x], level, fu, instruction[i]);
                cout << num << endl;
        }
        else if (code == "BEGIN")
        {
            if (instruction[i] != code) throw InvalidInstruction(instruction[i]);
            level++;
        }
        else if (code == "END")
        {
            if (instruction[i] != code) throw InvalidInstruction(instruction[i]);
            if (level <= 0) throw UnknownBlock();
            deleteNode(level);
            level--;
        }
        else if (code == "LOOKUP")
        {
            string identifier = "";
            ifs1 >> identifier;
            if (instruction[i] != code + " " + identifier) throw InvalidInstruction(instruction[i]);
            if (Check_identifier(identifier) == 0) throw InvalidInstruction(instruction[i]);
            bool check = 0;
            for (int j = level; j >= 0; j--)
            {
                Node pNew(identifier, j);
                int x = search(pNew);
                if (x != -1)
                {
                    cout << x << endl;
                    check = 1;
                    break;
                }
            }
            if (check == 0) throw Undeclared(identifier);
        }
        else if (code == "PRINT")
        {
            print();
        }
        else throw InvalidInstruction(instruction[i]);
    }

    if (level != 0) throw UnclosedBlock(level);
    ifs1.close();
}
