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
    if (identifier == "string" || identifier == "number" || identifier == "true" || identifier == "false") return 0;
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

bool Check_func(string func)
{
    int l = func.length();
    int a, step = 1;
    if (l <= 4) return 0;
    if (func[0] != '(') return 0;
    a = 1;
    for (int i = 1; i < l; i++)
    {
        if (func[i] == ',')
        {
            if (a + 6 >= l) return 0;
            if (func.substr(a, 6) != "number" && func.substr(a, 6) != "string") return 0;
            a = i + 1;
        }
        else if (func[i] == ')')
        {
            if (i != l - 9) return 0;
            if (a + 6 >= l && a != i) return 0;
            if (a == i);
            else if (func.substr(a, 6) != "number" && func.substr(a, 6) != "string") return 0;
            a = i + 1;
            step = 2;
        }
        else if (func[i] == '>' && step == 2)
        {
            if (i != l - 7) return 0;
            if (a + 2 >= l) return 0;
            if (func.substr(a, 2) != "->") return 0;
            a = i + 1;
            step = 3;
        }
        else if (i == l - 1 && step == 3)
        {
            if (a + 6 > l) return 0;
            if (func.substr(a, 6) != "number" && func.substr(a, 6) != "string") return 0;
            step = 4;
        }
    }
    if (step == 4) return 1;
    return 0;
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

void SymbolTable::deleteSymbol(Node* &node)
{
    if (node == NULL) return;
    deleteSymbol(node->left);
    deleteSymbol(node->right);
    delete node;
    node = NULL;
}

Node* SymbolTable::newNode(string identifier, string type, string val, int level, bool static_insert)
{
    Node *node = new Node;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->level = level;
    node->identifier = identifier;
    node->type = type;
    node->val = val;
    node->static_insert = static_insert;
    return node;
}

void SymbolTable::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        this->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void SymbolTable::rightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        this->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void SymbolTable::splay(Node* x)
{
    if (x->parent != NULL) num_splay++;
    while (x->parent != NULL)
    {
        if (!x->parent->parent)
        {
            if (x == x->parent->left)
            {
                rightRotate(x->parent);
            }
            else
            {
                leftRotate(x->parent);
            }
        }
        else if (x == x->parent->left && x->parent == x->parent->parent->left)
        {
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->right)
        {
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->left)
        {
            leftRotate(x->parent);
            rightRotate(x->parent);
        }
        else
        {
            rightRotate(x->parent);
            leftRotate(x->parent);
        }
    }
}

void SymbolTable::insertNode(int level, string identifier, string type, bool static_insert, string val, string instruction)
{
    num_com = 0;
    num_splay = 0;
    Node* node = newNode(identifier, type, val, level, static_insert);
    Node* y = NULL;
    Node* x = this->root;

    while (x != NULL)
    {
        y = x;
        if (node->level < x->level || (node->level == x->level && (node->identifier).compare(x->identifier) < 0))
        {
            x = x->left;
            ++num_com;
        }
        else if (node->level > x->level || (node->level == x->level && (node->identifier).compare(x->identifier) > 0))
        {
            x = x->right;
            ++num_com;
        }
        else
        {
            delete node;
            node = NULL;
            throw Redeclared(instruction);
        }
    }
    node->parent = y;
    if (y == NULL)
    {
        root = node;
    }
    else if (node->level < y->level || (node->level == y->level && (node->identifier).compare(y->identifier) < 0))
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }
    splay(node);
}

Node* SymbolTable::searchTreeHelper(Node* node, int level, string identifier) //co dem so lan so sanh
{
    if (node == NULL || (level == node->level && identifier == node->identifier))
    {
        ++num_com;
        return node;
    }
    if (level < node->level)
    {
        ++num_com;
        return searchTreeHelper(node->left, level, identifier);
    }
    else if (level == node->level && identifier.compare(node->identifier) < 0)
    {
        ++num_com;
        return searchTreeHelper(node->left, level, identifier);
    }
    ++num_com;
    return searchTreeHelper(node->right, level, identifier);
}

Node* SymbolTable::searchTreeHelper1(Node* node, int level, string identifier) //khong dem so lan so sanh
{
    if (node == NULL || (level == node->level && identifier == node->identifier))
    {
        return node;
    }
    if (level < node->level)
    {
        return searchTreeHelper1(node->left, level, identifier);
    }
    else if (level == node->level && identifier.compare(node->identifier) < 0)
    {
        return searchTreeHelper1(node->left, level, identifier);
    }
    return searchTreeHelper1(node->right, level, identifier);
}

bool SymbolTable::searchTree(int level, string identifier) //co xoay cay
{
    Node* x = searchTreeHelper(this->root, level, identifier);
    if (x == NULL) return 0;
    splay(x);
    return 1;
}

bool SymbolTable::searchTree1(int level, string identifier) //khong xoay cay
{
    Node* x = searchTreeHelper1(this->root, level, identifier);
    if (x == NULL)
    {
        return 0;
    }
    return 1;
}

Node* SymbolTable::searchNode(int level, string identifier) //so sanh level -> identifier
{
    int lev = level;
    for (int j = lev; j >= 0; j--)
    {
        if (searchTree1(j, identifier) == 1)
        {
            return searchTreeHelper(this->root, j, identifier);
        }
        if (j == 0) return NULL;
    }
    return NULL;
}

void SymbolTable::Check_compare(int level, string func, string type, string instruction)
{
    int l_type = type.length();
    int l_func = func.length();
    int count_type = 0, count_func = 0, a = 1, b = 0;

    for (int i = 1; i < l_type; i++)
    {
        if (type[1] == ')'){
            count_type = 0;
            break;
        }
        if (type[i] == ',') count_type++;
        if (type[i] == ')') count_type++;
    }
    for (int i = 1; i < l_func; i++)
    {
        if (func[1] == ')'){
            count_func = 0;
            break;
        }
        if (func[i] == ',') count_func++;
        if (func[i] == ')') count_func++;
    }

    if (count_type != count_func) throw TypeMismatch(instruction);
    else if (count_type == 0) return;
    string ty[count_type];
    string fu[count_type];
    for (int i = 0; i < count_type; i++){
        ty[i] = "";
        fu[i] = "";
    }

    for (int i = 1; i < l_type; i++)
    {
        if (type[i] == ',')
        {
            ty[b] = type.substr(a, 6);
            b++;
            a = i + 1;
        }
        if (type[i] == ')')
        {
            ty[b] = type.substr(a, 6);
        }
    }
    a = 1;
    b = 0;
    for (int i = 1; i < l_func; i++)
    {
        if (func[i] == ',')
        {
            fu[b] = func.substr(a, i - a);
            b++;
            a = i + 1;
        }
        if (func[i] == ')')
        {
            fu[b] = func.substr(a, i - a);
        }
    }

    for (int i = 0; i < count_type; i++)
    {
        if (ty[i] == "string")
        {
            if (Check_identifier(fu[i]) == 1)
            {
                Node* node = searchNode(level, fu[i]);
                if (node == NULL) throw Undeclared(instruction);
                if (node->type != "string") throw TypeMismatch(instruction);
                splay(node);
            }
            else if (Check_number(fu[i]) == 1) throw TypeMismatch(instruction);
            else if (Check_string(fu[i]) == 1);
            else {
                throw InvalidInstruction(instruction);
            }
        }
        else if (ty[i] == "number"){
            if (Check_identifier(fu[i]) == 1)
            {
                Node* node = searchNode(level, fu[i]);
                if (node == NULL) throw Undeclared(instruction);
                if (node->type != "number") throw TypeMismatch(instruction);
                splay(node);
            }
            else if (Check_string(fu[i]) == 1) throw TypeMismatch(instruction);
            else if (Check_number(fu[i]) == 1);
            else throw InvalidInstruction(instruction);
        }
        else throw InvalidInstruction(instruction);
    }
}

void SymbolTable::assignNode(int level, string identifier, string val, string instruction)
{
    num_com = 0;
    num_splay = 0;
    string func_identifier = "";
    if (Check_number(val) == 1)
    {
        Node* node = searchNode(level, identifier);
        if (node == NULL) throw Undeclared(instruction);
        else if (node->type == "number") node->val = val;
        else throw TypeMismatch(instruction);
        splay(node);
        return;
    }
    else if (Check_string(val) == 1)
    {
        Node* node = searchNode(level, identifier);
        if (node == NULL) throw Undeclared(instruction);
        else if (node->type == "string") node->val = val;
        else throw TypeMismatch(instruction);
        splay(node);
        return;
    }
    else if (Check_identifier(val) == 1)
    {
        Node* x = searchNode(level, val);
        if (x == NULL) throw Undeclared(instruction);
        if (x->type != "string" && x->type != "number") throw TypeMismatch(instruction);
        splay(x);
        Node* node = searchNode(level, identifier);
        if (node == NULL) throw Undeclared(instruction);
        else if (x->type == node->type) node->val = x->val;
        else throw TypeMismatch(instruction);
        if (node->type != "string" && node->type != "number") throw TypeMismatch(instruction);
        splay(node);
        return;
    }
    else
    {
        int l = val.length();
        if (l <= 2) throw InvalidInstruction(instruction);
        if (val[l - 1] != ')') throw InvalidInstruction(instruction);
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
        if (Check_identifier(func_identifier) == 0) throw InvalidInstruction(instruction);
        Node* node = searchNode(level, func_identifier);
        if (node == NULL) throw Undeclared(instruction);
        if (Check_func(node->type) == 0) throw TypeMismatch(instruction);
        splay(node);
        Check_compare(level, fu, node->type, instruction);
        string type_return = "";
        int l1 = (node->type).length();
        for (int i = 0; i < l1; i++)
        {
            if ((node->type)[i] == '>')
            {
                type_return = (node->type).substr(i + 1, 6);
            }
        }
        Node* x = searchNode(level, identifier);
        if (x == NULL) throw Undeclared(instruction);
        else if (x->type == type_return) x->val = val;
        else throw TypeMismatch(instruction);
        splay(x);
        return;
    }
}

void SymbolTable::split(Node* &x, Node* &s, Node* &t)
{
    splay(x);
    if (x->right != NULL)
    {
		t = x->right;
		t->parent = NULL;
	}
	else
    {
		t = NULL;
	}
	s = x;
	s->right = NULL;
	x = NULL;
}

Node* SymbolTable::maximum(Node* node)
{
    while (node->right != NULL)
    {
		node = node->right;
	}
	return node;
}

Node* SymbolTable::join(Node* s, Node* t)
{
	if (!s)
    {
		return t;
	}
    if (!t)
    {
		return s;
	}
	Node* x = maximum(s);
	splay(x);
	x->right = t;
	t->parent = x;
	return x;
}

void SymbolTable::deleteNodeHelper(Node* node, int level, string identifier)
{
	Node* x = NULL;
	Node* t;
	Node* s;
	while (node != NULL)
    {
		if (node->level == level && node->identifier == identifier)
		{
			x = node;
			break;
		}
		if (node->level < level || (node->level == level && (node->identifier).compare(identifier) < 0))
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}
	if (x == NULL) return;
    split(x, s, t);
    if (s->left)
    {
        s->left->parent = NULL;
    }
    root = join(s->left, t);
    delete(s);
    s = NULL;
}

void SymbolTable::preOrder(Node* node)
{
    if (node != NULL)
    {
        if (node == root) cout << node->identifier << "//" << node->level;
        else cout << " " << node->identifier << "//" << node->level;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void SymbolTable::run(string filename)
{
    int level = 0;

    ifstream ifs(filename);
    int number_of_line = 0;
    string line;
    while (getline(ifs, line))
    {
        ++ number_of_line;
    }
    ifs.close();

    ifstream ifs0(filename);
    string instruction[number_of_line];
    for (int i = 0; i < number_of_line; i++)
    {
        getline(ifs0, instruction[i]);
    }
    ifs0.close();

    string codes[number_of_line];
    int check_code[number_of_line];
    string identifier_remove[number_of_line];
    for (int i = 0; i < number_of_line; i++)
    {
        codes[i] = "";
        check_code[i] = 0;
        identifier_remove[i] = "";
    }
    ifstream ifs1(filename);
    for (int i = 0; i < number_of_line; i++)
    {
        num_splay = 0;
        num_com = 0;
        string code;
        string identifier, type;
        string static_insert;
        string value;
        ifs1 >> code;
        codes[i] = code;
        if (code == "INSERT")
        {
            check_code[i] = 0;
            ifs1 >> identifier;
            ifs1 >> type;
            ifs1 >> static_insert;

            if (instruction[i] != code + " " + identifier + " " + type + " " + static_insert) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            if (Check_identifier(identifier) == 0) throw InvalidInstruction(instruction[i]); //Kiem tra identifier
            if (type != "string" && type != "number" && Check_func(type) == 0) throw InvalidInstruction(instruction[i]); //Kiem tra type
            if (static_insert == "false")
            {
                if (level > 0 && Check_func(type) == 1) throw InvalidDeclaration(instruction[i]);
                insertNode(level, identifier, type, 0, "", instruction[i]);
                if (level > 0)
                {
                    identifier_remove[i] = identifier;
                }
            }
            else if (static_insert == "true") insertNode(0 , identifier, type, 1, "", instruction[i]);
            else throw InvalidInstruction(instruction[i]); //Kiem tra static
            cout << num_com << " " << num_splay << endl;
        }
        else if (code == "ASSIGN")
        {
            check_code[i] = 0;
            ifs1 >> identifier;
            ifs1.ignore();
            getline(ifs1, value);
            if (instruction[i] != code + " " + identifier + " " + value) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            if (Check_identifier(identifier) == 0) throw InvalidInstruction(instruction[i]); //Kiem tra identifier
            if (Check_val(value) == 0) throw InvalidInstruction(instruction[i]); //Kiem tra value
            assignNode(level, identifier, value, instruction[i]);
            cout << num_com << " " << num_splay << endl;
        }
        else if (code == "BEGIN")
        {
            if (instruction[i] != code) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            check_code[i] = 1;
            level++;
        }
        else if (code == "END")
        {
            if (instruction[i] != code) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            if (level <= 0) throw UnknownBlock();
            int remove_i = 0;
            check_code[i] = -1;
            int number = -1;
            for (int j = i - 1; j >= 0; j--)
            {
                number += check_code[j];
                if (number == 0)
                {
                    remove_i = j;
                    break;
                }
            }
            for (int j = remove_i; j < i; j++)
            {
                if (codes[j] == "INSERT")
                {
                    if (identifier_remove[j] == "");
                    else deleteNodeHelper(root, level, identifier_remove[j]);
                }
            }
            level--;
        }
        else if (code == "LOOKUP")
        {
            ifs1 >> identifier;
            if (instruction[i] != code + " " + identifier) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            check_code[i] = 0;
            int lev = level;
            for (int j = lev; j >= 0; j--)
            {
                if (searchTree(j, identifier) == 1) break;
                if (j == 0) throw Undeclared(instruction[i]);
            }
            cout << root->level << endl;
        }
        else if (code == "PRINT")
        {
            if (instruction[i] != code) throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
            check_code[i] = 0;
            if (root == NULL);
            else
            {
                preOrder(root);
                cout << endl;
            }
        }
        else throw InvalidInstruction(instruction[i]); //Kiem tra dong lenh
    }
    if (level != 0) throw UnclosedBlock(level);
    ifs1.close();
}
