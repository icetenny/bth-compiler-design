#ifndef IR_H
#define IR_H
#include "Node.h"

#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <map>

using namespace std;

class TAC
{
public:
    string op, lhs, rhs, result;

    TAC(string res, string lhs, string op, string rhs) : result(res), lhs(lhs), rhs(rhs), op(op)
    {
    }

    void print_tac()
    {
        cout << get_text() << endl;
    }

    string get_text()
    {

        if (lhs == "" && rhs == "")
        {
            return op + " " + result;
        }
        if (op == "=")
        {
            return result + " " + op + " " + rhs;
        }
        if (op == "new")
        {
            return result + " := " + op + " " + lhs + " " + rhs;
        }
        if (op == "IFFALSE")
        {
            return op + " " + result + " GOTO " + rhs;
        }
        if (op == "GOTO")
        {
            return op + " " + rhs;
        }

        return result + " := " + lhs + " " + op + " " + rhs;
    }

    list<string> get_bytecode()
    {
        if (op == "+")
        {
            return {load_var(lhs), load_var(rhs), "iadd", store_var(result)};
        }
        else if (op == "-")
        {
            return {load_var(lhs), load_var(rhs), "isub", store_var(result)};
        }
        else if (op == "*")
        {
            return {load_var(lhs), load_var(rhs), "imul", store_var(result)};
        }
        else if (op == "/")
        {
            return {load_var(lhs), load_var(rhs), "idiv", store_var(result)};
        }
        else if (op == "<")
        {
            return {load_var(lhs), load_var(rhs), "ilt", store_var(result)};
        }
        else if (op == ">")
        {
            return {load_var(lhs), load_var(rhs), "igt", store_var(result)};
        }
        else if (op == "==")
        {
            return {load_var(lhs), load_var(rhs), "ieq", store_var(result)};
        }
        else if (op == "AND")
        {
            return {load_var(lhs), load_var(rhs), "iand", store_var(result)};
        }
        else if (op == "OR")
        {
            return {load_var(lhs), load_var(rhs), "ior", store_var(result)};
        }
        else if (op == "NOT")
        {
            return {load_var(rhs), "inot", store_var(result)};
        }
        else if (op == "=")
        {
            return {load_var(rhs), store_var(result)};
        }
        else if (op == "GOTO"){
            return {"goto " + rhs};
        }
        else if (op == "IFFALSE"){
            return {load_var(result), "iffalse goto " + rhs};
        }
        return {};
    }

    string load_var(string var)
    {
        if (var[0] == '$')
        {
            return "iconst " + var.substr(1);
        }
        return "iload " + var;
    }

    string store_var(string var)
    {
        return "istore " + var;
    }
};

class BasicBlock
{
public:
    int id;
    string name;
    string method_name;
    BasicBlock *true_exit = NULL;
    BasicBlock *false_exit = NULL;
    TAC *condition;
    list<TAC *> tac_instruction;
    

    BasicBlock(int block_id) : id(block_id), name("block_" + to_string(block_id)) {}
    BasicBlock(int block_id, string m_name) : id(block_id), name("block_" + to_string(block_id)), method_name(m_name) {}
};

class IR
{
public:
    int bbid = 0;
    int temp_var_id = 0;
    int lineno;
    list<BasicBlock *> list_blocks;
    BasicBlock *current_block;
    list<BasicBlock *> list_entry_blocks;
    string current_class, current_method;
    std::ofstream outStream;
    list<string> checked_bblock;

    IR() {}

    void test_print()
    {
        cout << "IR Start" << endl;
    }

    void init(Node *root_node)
    {
        cout << root_node->type << endl;
        execute(root_node);
    }

    void execute(Node *n)
    {
        string type = n->type;
        string value = n->value;
        // int id = n->id;
        list<Node *> children = n->children;

        lineno = n->lineno;

        if ((type == "CLASS_DECLARATION") || (type == "MAIN_CLASS_DECLARATION"))
        {
            // Get class name
            auto child_iter = children.begin();
            current_class = (*child_iter)->value;
        }

        if (type == "METHOD_DECLARATION")
        {
            // Get method name
            auto child_iter = children.begin();
            child_iter++;
            current_method = (*child_iter)->value;

            // Create start basic block with method_name
            BasicBlock *start_block = new BasicBlock(bbid++, current_class + "." + current_method);
            list_blocks.push_back(start_block);
            list_entry_blocks.push_back(start_block);
            current_block = start_block;
        }

        if (type == "EXPRESSION")
        {
            execute_ir_expression(n);
        }

        else if (type == "STATEMENT")
        {
            execute_ir_statement(n);
        }
        else if (type == "RETURN")
        {
            execute_ir_return(n);
        }
        else
        {
            // Recursive through children
            for (Node *&child : children)
            {
                execute(n = child);
            }
        }

        if (type == "METHOD_DECLARATION")
        {
            // Make end bblock
            BasicBlock *end_block = new BasicBlock(bbid++, "$END." + current_class + "." + current_method);
            list_blocks.push_back(end_block);
            current_block->true_exit = end_block;
        }
    }

    string execute_ir_expression(Node *n)
    {
        string ex_type = n->type;
        string ex_value = n->value;
        string lhs, rhs, op, res;

        if (ex_type == "Identifier")
        {
            return ex_value;
        }

        if (ex_type == "Integer_Literal")
        {
            return "$" + ex_value;
        }

        if (ex_value == "TRUE" || ex_value == "FALSE")
        {
            return "$" + ex_value;
        }

        if (ex_value == "NOT" || ex_value == "LENGTH")
        {
            op = ex_value;

            lhs = "";
            auto child_iter = n->children.begin();
            rhs = execute_ir_expression(*child_iter);

            res = "_t" + to_string(temp_var_id++);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);
            // tac->print_tac();

            return res;
        }

        if (ex_value == "ARRAY_INDEX")
        {
            auto child_iter = n->children.begin();
            lhs = execute_ir_expression(*child_iter);
            child_iter++;
            rhs = execute_ir_expression(*child_iter);

            return lhs + "[" + rhs + "]";
        }

        if (ex_value == "THIS")
        {
            return "THIS";
        }

        if (ex_value == "+" || ex_value == "-" || ex_value == "*" || ex_value == "/" ||
            ex_value == ">" || ex_value == "<" || ex_value == "==" || ex_value == "AND" || ex_value == "OR")
        {
            op = ex_value;

            auto child_iter = n->children.begin();
            lhs = execute_ir_expression(*child_iter);
            child_iter++;
            rhs = execute_ir_expression(*child_iter);

            res = "_t" + to_string(temp_var_id++);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);

            // tac->print_tac();

            return res;
        }

        if (ex_value == "NEW_INT_ARRAY")
        {
            op = "new";
            lhs = "INT_ARRAY";
            auto child_iter = n->children.begin();
            rhs = execute_ir_expression(*child_iter);

            res = "_t" + to_string(temp_var_id++);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);

            return res;
        }

        if (ex_value == "NEW_CLASS_OBJECT")
        {
            op = "new";

            auto child_iter = n->children.begin();
            lhs = execute_ir_expression(*child_iter);

            res = "_t" + to_string(temp_var_id++);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);

            return res;
        }

        if (ex_value == "CALL_FUNCTION")
        {
            auto child_iter = n->children.begin();

            // Execute object
            string param1 = execute_ir_expression(*child_iter);
            TAC *tac_1 = new TAC(param1, "", "param", "");
            current_block->tac_instruction.push_back(tac_1);

            // Execute called function
            child_iter++;
            string func_name = (*(*child_iter)->children.begin())->value;

            op = "call " + func_name;

            // At param list
            child_iter++;
            int param_size = (*child_iter)->children.size() + 1;
            for (auto param_iter = (*child_iter)->children.begin(); param_iter != (*child_iter)->children.end(); param_iter++)
            {
                string param_res = execute_ir_expression(*param_iter);
                TAC *tac = new TAC(param_res, "", "param", "");
                current_block->tac_instruction.push_back(tac);
            }

            res = "_t" + to_string(temp_var_id++);
            TAC *tac_2 = new TAC(res, "", op, to_string(param_size));
            current_block->tac_instruction.push_back(tac_2);
            return res;
        }

        return "NULL";
    }

    string execute_ir_statement(Node *n)
    {
        string ex_type = n->type;
        string ex_value = n->value;
        string lhs, rhs, op, res, cond;

        if (ex_value == "STATEMENT_GROUP")
        {
            for (Node *&child : n->children)
            {
                execute_ir_statement(n = child);
            }
            return "NULL";
        }

        if (ex_value == "PRINT")
        {
            op = ex_value;
            auto child_iter = n->children.begin();
            res = execute_ir_expression(*child_iter);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);
        }

        if (ex_value == "ASSIGN")
        {
            op = "=";
            auto child_iter = n->children.begin();
            res = execute_ir_expression(*child_iter);

            child_iter++;
            rhs = execute_ir_expression(*child_iter);

            TAC *tac = new TAC(res, lhs, op, rhs);
            current_block->tac_instruction.push_back(tac);
        }

        if (ex_value == "IF")
        {
            auto child_iter = n->children.begin();
            cond = execute_ir_expression(*child_iter);

            // Create new basic block
            BasicBlock *if_block = new BasicBlock(bbid++);
            list_blocks.push_back(if_block);

            // Create merged basic block
            BasicBlock *merged_block = new BasicBlock(bbid++);
            list_blocks.push_back(merged_block);

            // Add Exits
            add_false_exit(current_block, merged_block, cond);
            add_true_exit(current_block, if_block);

            // Execute if statement
            current_block = if_block;
            child_iter++;
            execute_ir_statement(*child_iter);
            add_true_exit(if_block, merged_block);

            // Set merged block as current block
            current_block = merged_block;
        }
        if (ex_value == "IF_ELSE")
        {
            auto child_iter = n->children.begin();
            cond = execute_ir_expression(*child_iter);

            // Create if block
            BasicBlock *if_block = new BasicBlock(bbid++);
            list_blocks.push_back(if_block);

            // Create else block
            BasicBlock *else_block = new BasicBlock(bbid++);
            list_blocks.push_back(else_block);

            // Create merged block
            BasicBlock *merged_block = new BasicBlock(bbid++);
            list_blocks.push_back(merged_block);

            // Add Exits
            add_false_exit(current_block, else_block, cond);
            add_true_exit(current_block, if_block);

            // Execute if statement
            current_block = if_block;
            child_iter++;
            execute_ir_statement(*child_iter);
            add_true_exit(if_block, merged_block);

            // Execute else statement
            current_block = else_block;
            child_iter++;
            execute_ir_statement(*child_iter);
            add_true_exit(else_block, merged_block);

            // Set merged block as current block
            current_block = merged_block;
        }
        if (ex_value == "WHILE")
        {
            // Create condtion block
            BasicBlock *condition_block = new BasicBlock(bbid++);
            list_blocks.push_back(condition_block);

            // Create action block
            BasicBlock *action_block = new BasicBlock(bbid++);
            list_blocks.push_back(action_block);

            // Create merged basic block
            BasicBlock *merged_block = new BasicBlock(bbid++);
            list_blocks.push_back(merged_block);

            // Add Exit
            add_true_exit(current_block, condition_block);

            // Execute condition block
            current_block = condition_block;
            auto child_iter = n->children.begin();
            cond = execute_ir_expression(*child_iter);
            add_false_exit(condition_block, merged_block, cond);
            add_true_exit(condition_block, action_block);

            // Execute while 
            current_block = action_block;
            child_iter++;
            execute_ir_statement(*child_iter);
            add_true_exit(action_block, condition_block);

            current_block = merged_block;
        }
        return "NULL";
    }

    string execute_ir_return(Node *n)
    {
        string ex_type = n->type;
        string ex_value = n->value;
        string lhs, rhs, op, res;

        op = "return";

        auto child_iter = n->children.begin();
        res = execute_ir_expression(*child_iter);

        TAC *tac = new TAC(res, lhs, op, rhs);
        current_block->tac_instruction.push_back(tac);
        return res;
    }

    void add_true_exit(BasicBlock* from_block, BasicBlock* to_block){
        from_block->true_exit = to_block;
        TAC *true_tac = new TAC("", "", "GOTO", to_block->name);
        from_block->tac_instruction.push_back(true_tac);
    }

    void add_false_exit(BasicBlock* from_block, BasicBlock* to_block, string condition){
        from_block->false_exit = to_block;
        TAC *false_tac = new TAC(condition, "", "IFFALSE", to_block->name);
        current_block->tac_instruction.push_back(false_tac);
    }

    void generate_tree()
    {
        std::ofstream outStream;
        char *filename = "ir_tree.dot";
        outStream.open(filename);

        int count = 0;
        outStream << "digraph {\n graph [ splines = ortho ]\nnode [ shape = box ];" << std::endl;

        for (auto bb = list_blocks.begin(); bb != list_blocks.end(); bb++)
        {
            generate_tree_content(&outStream, *bb);
        }

        outStream << "}" << std::endl;
        outStream.close();

        printf("\nBuilt a ir-tree at %s. Use 'make ir' to generate the pdf version.\n", filename);
    }

    void generate_tree_content(ofstream *outStream, BasicBlock *bb)
    {
        int block_id = bb->id;
        string block_name = bb->name;
        string label;

        if (bb->method_name != "")
        {
            label = block_name + " : " + bb->method_name + "\n--------------\n";
        }
        else
        {
            label = block_name + "\n--------------\n";
        }

        // Print all TAC
        for (auto tac = bb->tac_instruction.begin(); tac != bb->tac_instruction.end(); tac++)
        {
            label += (*tac)->get_text() + "\n";
        }

        *outStream << "n" << block_id << " [label=\"" << label << "\"];" << endl;

        // Create spline
        if (bb->true_exit != NULL)
        {
            *outStream << "n" << block_id << " -> n" << bb->true_exit->id << " [xlabel= \"true\"];" << endl;
        }
        if (bb->false_exit != NULL)
        {
            *outStream << "n" << block_id << " -> n" << bb->false_exit->id << " [xlabel= \"false\"];" << endl;
        }
    }

    // -------------------- PART 2 : Java Bytecode---------------------------

    void generate_bytecode()
    {
        char *filename = "bytecode.class";
        outStream.open(filename);

        for (BasicBlock *entry_block : list_entry_blocks)
        {

            outwrite(entry_block->method_name);

            for (TAC *inst : entry_block->tac_instruction)
            {
                outlist(inst->get_bytecode());
            }

            gen_true_exit(entry_block);


        }

        outStream.close();
        printf("\nJava Bytecode generated at : %s\n", filename);
    }

    string gen_true_exit(BasicBlock* bblock){


        for (string checked_block_name : checked_bblock) {
            if (checked_block_name == bblock->name) {
                return "NULL";
            }

        checked_bblock.push_back(bblock->name);

        outwrite(bblock->name);

        for (TAC *inst : bblock->tac_instruction)
        {
            outlist(inst->get_bytecode());
        }

        if (bblock -> true_exit == NULL){
            return "NULL";
        }
        
        gen_true_exit(bblock->true_exit);

    }

        return "NULL";
    }

    void outwrite(string word, bool indent = false)
    {
        if (word != "")
        {
            if (indent){
                outStream << "\t" << word << endl;

            } else{

            outStream << word << endl;
            }
        }
    }

    void outlist(list<string> lw, bool indent=false)
    {
        for (string word : lw)
        {
            outwrite(word, indent);
        }
    }
};

#endif