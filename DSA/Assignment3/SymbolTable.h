#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

class Node
{
public:
    string identifier;
    string value;
    bool func;
    int type;
    int level;
    int num_of_parameter;
    int* type_func;
    long long key;
    Node(): identifier(""), value(""), func(0), type(0), level(0), num_of_parameter(0), type_func(NULL), key(0) {};
    long long create()
    {
        string keys = "";
        int l = identifier.length();
        keys += to_string(level);
        for (int i = 0; i < l; i++)
        {
            keys += to_string(identifier[i]-48);
        }
        return stod(keys);
    }
    Node (string identifier, int level)
    {
        this->identifier = identifier;
        this->value = "";
        this->level = level;
        this->func = 0;
        this->type = 0;
        this->num_of_parameter = 0;
        this->type_func = NULL;
        this->key = create();
    }
    Node(string identifier, int level, int num_of_parameter, bool func, int type)
    {
        this->identifier = identifier;
        this->value = "";
        this->level = level;
        this->num_of_parameter = num_of_parameter;
        this->func = func;
        this->type = type;
        this->key = create();
        if (func == 1 && num_of_parameter > 0)
        {
            type_func = new int [num_of_parameter];
            for (int i = 0; i < this->num_of_parameter; i++)
            {
                type_func[i] = 0;
            }
        }
        else type_func = NULL;
    }
};

class SymbolTable
{
private:
    int (*hp)(long long, int, int, int, int);
    bool* status;
    Node* data;
    int size;
    int c1;
    int c2;
    int num;
public:
    SymbolTable(): status(NULL), data(NULL), size(0), c1(0), c2(0), num(0) {};
    ~SymbolTable()
    {
        for (int i = 0; i < size; i++)
        {
            if (data[i].func == 1)
            {
                delete[] data[i].type_func;
                data[i].type_func = NULL;
            }
        }
        delete[] status;
        delete[] data;
    }
    void createHash(int size, int c1, int c2, int (*hp)(long long, int, int, int, int))
    {
        this->hp = hp;
        this->size = size;
        this->c1 = c1;
        this->c2 = c2;
        if (size > 0)
        {
            this->data = new Node [size];
            this->status = new bool [size];
        }
        for (int i = 0; i < size; i++) {
            this->status[i] = 0;
        }
    }

    int insert(Node head)
    {
        num = 0;
        for (int i = 0; i < size; i++)
        {
            int slot = hp(head.key, size, i, c1, c2);
            if (status[slot] == 0)
            {
                data[slot] = head;
                status[slot] = 1;
                return i;
            }
            num++;
        }
        return -1;
    }

    void deleteNode(int level)
    {
        for (int i = 0; i < size; i++)
        {
            if (status[i] == 1 && data[i].level == level)
            {
                data[i].identifier = "";
                data[i].value = "";
                if (data[i].func == 1)
                {
                    delete[] data[i].type_func;
                    data[i].type_func = NULL;
                    data[i].func = 0;
                }
                data[i].type = 0;
                data[i].num_of_parameter = 0;
                data[i].key = 0;
                data[i].level = 0;
                status[i] = 0;
            }
        }
    }

    int search(Node head)
    {
        for (int i = 0; i < size; i++)
        {
            int slot = hp(head.key, size, i, c1, c2);
            if (status[slot] == 1 && data[slot].key == head.key && data[slot].identifier == head.identifier) return slot;
            num++;
        }
        return -1;
    }

    void Check_compare(Node head, int level, string fu, string instruction);

    void print()
    {
        int print_max = -1;
        for (int i = size - 1; i >= 0; i--)
        {
            if (status[i] == 1)
            {
                print_max = i;
                break;
            }
        }
        int start = 0;
        for (int i = 0; i < size; i++)
        {
            if (status[i] == 1)
            {
                if (start == 0)
                {
                    cout << i << " " << data[i].identifier << "//" << data[i].level;
                    start++;
                }
                else cout << ";" << i << " " << data[i].identifier << "//" << data[i].level;
            }
            if (i == print_max)
            {
                cout << endl;
                break;
            }
        }
    }

    void run(string filename);
};
#endif
