#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <map>
#include <sstream>
#include <string>

using namespace std;

class Data
{
public:
    int value = -9999;
    bool is_bool = false;

    Data() {}

    Data(string s)
    {
        if (s == "true")
        {
            value = 1;
            is_bool = true;
        }
        else if (s == "false")
        {
            value = 0;
            is_bool = true;
        }
        else
        {
            value = stoi(s);
        }
    }

    Data(int i)
    {
        value = i;
    }

    Data(bool b)
    {
        if (b)
        {
            value = 1;
            is_bool = true;
        }
        else
        {
            value = 0;
            is_bool = true;
        }
    }

    void print()
    {
        cout << "DATA : " << value << "|" << is_bool << endl;
    }
};

class Stack
{
public:
    int size = 0;
    list<Data *> stack;

    void push(auto i)
    {
        Data *d = new Data(i);
        stack.push_back(d);
        size++;
    }

    void push_data(Data *d)
    {
        stack.push_back(d);
        size++;
    }

    Data *pop()
    {
        if (size == 0)
        {
            return new Data();
        }

        Data *ret = stack.back();
        stack.pop_back();
        size--;
        return ret;
    }
};

class Instruction
{
public:
    int id;
    string inst;
    list<string> args;
    string command;
    string l_arg;

    Instruction(int id, string line) : id(id), inst(line)
    {
        string s;
        istringstream iss(line);
        while (getline(iss, s, ' '))
        {
            args.push_back(s);
        }

        command = args.front();
        l_arg = args.back();
    };

    void print()
    {
        cout << "Arg id: " << id << endl;
        for (string a : args)
        {
            cout << '\t' << a << endl;
        }
    }

    string get_var_arg()
    {
        if (args.front() == "iload" || args.front() == "istore")
        {
            return args.back();
        }
        return "NULL";
    }
};

class Block
{
public:
    string block_name;
    list<Instruction *> instruction_list;

    Block(string name) : block_name(name.substr(1, name.size() - 2)){};

    void add_instrucion(Instruction *i)
    {
        instruction_list.push_back(i);
    }
    void print()
    {
        cout << "Block: " << block_name << endl;
        for (Instruction *i : instruction_list)
        {
            cout << "Inst: " << i->inst << endl;
        }
    }
};

class Method
{
public:
    string method_name;
    list<Instruction *> instruction_list;
    map<string, Block *> block_map;
    list<string> variable_list;
    string class_part, method_part;

    Method(){

    }

    Method(string name)
    {
        method_name = name.substr(0, name.size() - 1);
        size_t pos = method_name.find('.');
        class_part = method_name.substr(0, pos);
        method_part = method_name.substr(pos + 1);
    };

    void add_instrucion(Instruction *i)
    {
        instruction_list.push_back(i);
    }
    void add_block(Block *b)
    {
        block_map[b->block_name] = b;
    }
    void add_variable(string s)
    {
        if (s == "NULL")
        {
            return;
        }
        for (string var : variable_list)
        {
            if (var == s)
            {
                return;
            }
        }
        variable_list.push_back(s);
    }
    void print()
    {
        cout << "Method: " << class_part << " | " << method_part << endl;
        for (string v : variable_list)
        {
            cout << "VAR: " << v << endl;
        }

        for (Instruction *i : instruction_list)
        {
            cout << "Inst: " << i->inst << endl;
        }

        for (auto p : block_map)
        {
            p.second->print();
        }
    }
};

class Activation
{
public:
    int pc;
    map<string, Data *> local_var_map;
    Method *method;
    list<Instruction *> awaiting_instruction;

    Activation(int pc, Method *m) : pc(pc), method(m)
    {
        for (Instruction *i : method->instruction_list)
        {
            awaiting_instruction.push_back(i);
        }

        for (string v : method->variable_list)
        {
            local_var_map[v] = new Data();
        }
    }

    void goto_block(string block_name){
        awaiting_instruction.clear();
        for (Instruction *i : method->block_map[block_name]->instruction_list)
        {
            awaiting_instruction.push_back(i);
        }
    }

    Instruction *get_next_instruction()
    {
        Instruction *n = awaiting_instruction.front();
        awaiting_instruction.pop_front();
        return n;
    }

    void store_var(string var, Data *d)
    {
        local_var_map[var] = d;
    }
    Data *load_var(string var)
    {
        return local_var_map[var];
    }
};

class ActivationStack
{
public:
    int size = 0;
    list<Activation *> stack;

    void push(Activation *a)
    {
        stack.push_back(a);
        size++;
    }

    Activation *pop()
    {
        if (size == 0)
        {
            return NULL;
        }

        Activation *ret = stack.back();
        stack.pop_back();
        size--;
        return ret;
    }
};

class Program
{
public:
    map<string, Method *> method_map;

    Program(){};

    void add_method(Method *m)
    {
        method_map[m->method_name] = m;
        // cout << "ADDED SUCCESS" << endl;
    }

    void print()
    {
        for (auto p : method_map)
        {
            cout << "Method : " << p.first << endl;
            p.second->print();
        }
    }

    Method* get_method(string s){
        return method_map[s];
    }
};

class StackMachine
{
public:
    Program *program;
    Method *current_method;
    Block *current_block;
    int lineno = 1;
    Stack *data_stack;
    ActivationStack *activation_stack;
    Activation *current_activation;
    Method *main_method;

    StackMachine()
    {
        program = new Program();
    }

    void init(string filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Unable to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            if (!line.empty() && line[0] != '\t')
            {
                current_method = new Method(line);
                program->add_method(current_method);

                // Assign main method
                if (current_method->method_part == "main")
                {
                    main_method = current_method;
                }
            }
            else if (!line.empty() && line[0] == '\t' && line[1] != '\t')
            {
                if (line.back() != ':')
                {
                    // Add instruction to method
                    Instruction *new_instruction = new Instruction(lineno, line.substr(1));
                    current_method->add_instrucion(new_instruction);
                    // Add var to method
                    string var_arg = new_instruction->get_var_arg();
                    current_method->add_variable(var_arg);
                    // new_instruction->print();
                }
                else
                {
                    // Create new block in a method
                    current_block = new Block(line);
                    current_method->add_block(current_block);
                }
            }

            else if (!line.empty() && line[0] == '\t' && line[1] == '\t')
            {
                // Add intstuction to block
                Instruction *new_instruction = new Instruction(lineno, line.substr(2));
                current_block->add_instrucion(new_instruction);
                // Add var to method
                string var_arg = new_instruction->get_var_arg();
                current_method->add_variable(var_arg);
                // new_instruction->print();
            }
            lineno++;
        }
        file.close();

        // program->print();
    }

    void execute()
    {
        string cmd, arg;
        data_stack = new Stack();
        activation_stack = new ActivationStack();

        current_activation = new Activation(0, main_method);
        activation_stack->push(current_activation);

        while (true)
        {
            Instruction *current_instruction = current_activation->get_next_instruction();
            cmd = current_instruction->command;
            arg = current_instruction->l_arg;

            // cout << current_instruction->inst << endl;

            if (cmd == "stop")
            {
                cout << "Exiting..." << endl;
                break;
            }
            else if (cmd == "istore")
            {
                Data *d = data_stack->pop();
                current_activation->store_var(arg, d);
            }
            else if (cmd == "iload")
            {
                Data *d = current_activation->load_var(arg);
                data_stack->push_data(d);
            }
            else if (cmd == "iconst")
            {
                data_stack->push(arg);
            }
            else if (cmd == "iadd")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(d2 + d1);
            }
            else if (cmd == "isub")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(d2 - d1);
            }
            else if (cmd == "imul")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(d2 * d1);
            }
            else if (cmd == "idiv")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(d2 / d1);
            }
            else if (cmd == "ilt")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(bool(d2 < d1));
            }
            else if (cmd == "igt")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(bool(d2 > d1));
            }
            else if (cmd == "ieq")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(bool(d2 == d1));
            }
            else if (cmd == "iand")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(bool(!(d1 * d2 == 0)));
            }
            else if (cmd == "ior")
            {
                int d1 = data_stack->pop()->value;
                int d2 = data_stack->pop()->value;
                data_stack->push(bool(!(d1 + d2 == 0)));
            }
            else if (cmd == "inot")
            {
                int d = data_stack->pop()->value;
                data_stack->push(bool(d == 0));
            }
            else if (cmd == "print")
            {
                Data *d = data_stack->pop();

                if (d->is_bool)
                {
                    if (d->value == 1)
                    {
                        cout << ">>> true" << endl;
                    }
                    else if (d->value == 0)
                    {
                        cout << ">>> false" << endl;
                    }
                }
                else
                {
                    cout << ">>> " << d->value << endl;
                }
            }
            else if (cmd == "invokevirtual")
            {
                Method *m = program->get_method(arg);
                Activation *new_activation = new Activation(0, m);
                activation_stack->push(new_activation);

                current_activation = new_activation;
            }

            else if (cmd == "ireturn")
            {
                activation_stack->pop();
                current_activation = activation_stack->stack.back();
            }

            else if (cmd == "goto"){
                current_activation->goto_block(arg);
            }
            else if (cmd == "iffalse"){
                int d = data_stack->pop()->value;
                if (d == 0){
                    current_activation->goto_block(arg);
                }
            }
        }
    }
};