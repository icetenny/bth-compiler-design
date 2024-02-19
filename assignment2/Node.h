#ifndef NODE_H
#define NODE_H

#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <map>

using namespace std;

class Record
{
public:
	string id;
	string name;
	string recordtype;
	string returntype;

	virtual ~Record() {}

	Record() : name(""), recordtype(""), returntype("") {}

	void print_record()
	{
		cout << "name: " << name << " , recordtype: " << recordtype << ", returntype: " << returntype << endl;
	}

	void set_name(string n)
	{
		name = n;
	}

	void set_type(string t)
	{
		returntype = t;
	}
};

class VariableRecord : public Record
{
public:
	VariableRecord()
	{
		recordtype = "VARIABLE";
	}
};

class MethodRecord : public Record
{
public:
	map<string, VariableRecord *> variable_map;
	list<string> param_list;
	int param_count = 0;
	MethodRecord()
	{
		recordtype = "METHOD";
	}
	void print_param_list()
	{
		cout << "PRINT PARAM FOR METHOD " << name << " : ";
		for (const auto &str : param_list)
		{
			cout << str << " ";
		}
		cout << endl;
	}

	void print_var_map()
	{

		cout << "PRINT VAR MAP FOR METHOD " << name << " : ";
		for (const auto &pair : variable_map)
		{
			cout << pair.first << " ";
		}
		cout << endl;
	}
};

class ClassRecord : public Record
{
public:
	map<string, MethodRecord *> method_map;
	map<string, VariableRecord *> variable_map;
	ClassRecord()
	{
		recordtype = "CLASS";
	}

	MethodRecord *get_method(string key)
	{
		auto it = method_map.find(key);
		if (it != method_map.end())
		{
			return it->second;
		}
		else
		{
			return new MethodRecord();
		}
	}

	void print_method_map()
	{

		cout << "PRINT METHOD MAP FOR CLASS " << name << " : ";
		for (const auto &pair : method_map)
		{
			cout << pair.first << " ";
		}
		cout << endl;
	}

	void print_var_map()
	{

		cout << "PRINT VAR MAP FOR CLASS " << name << " : ";
		for (const auto &pair : variable_map)
		{
			cout << pair.first << " ";
		}
		cout << endl;
	}

	void super_print()
	{
		print_var_map();

		cout << "PRINT METHOD MAP FOR CLASS " << name << " : ";
		for (const auto &pair : method_map)
		{
			cout << "==================" << endl;
			cout << pair.first << " : ";
			pair.second->print_var_map();
		}
		cout << endl;
	}
};

class Node
{
public:
	int id, lineno;
	string type, value;
	list<Node *> children;

	Node(string t, string v, int l) : type(t), value(v), lineno(l) {}
	Node()
	{
		type = "uninitialised";
		value = "uninitialised";
	} // Bison needs this.

	void print_tree(int depth = 0)
	{
		for (int i = 0; i < depth; i++)
			cout << "  ";
		cout << type << ":" << value << endl; //<< " @line: "<< lineno << endl;
		for (auto i = children.begin(); i != children.end(); i++)
			(*i)->print_tree(depth + 1);
	}

	void generate_tree()
	{
		std::ofstream outStream;
		char *filename = "tree.dot";
		outStream.open(filename);

		int count = 0;
		outStream << "digraph {" << std::endl;
		generate_tree_content(count, &outStream);
		outStream << "}" << std::endl;
		outStream.close();

		printf("\nBuilt a parse-tree at %s. Use 'make tree' to generate the pdf version.\n", filename);
	}

	void generate_tree_content(int &count, ofstream *outStream)
	{
		id = count++;
		if (value != "")
		{
			*outStream << "n" << id << " [label=\"" << type << ":" << value << " line : " << lineno << "\"];" << endl;
		}
		else
		{
			*outStream << "n" << id << " [label=\"" << type << " line : " << lineno << "\"];" << endl;
		}

		for (auto i = children.begin(); i != children.end(); i++)
		{
			(*i)->generate_tree_content(count, outStream);
			*outStream << "n" << id << " -> n" << (*i)->id << endl;
		}
	}
};

class Scope
{
public:
	Scope *parent_scope;
	list<Scope *> children_scope;
	int num_children = 0;
	int depth = 0;
	int scope_id;
	map<string, ClassRecord *> class_record_map; // Records in this scope
	map<string, MethodRecord *> method_record_map;
	map<string, VariableRecord *> variable_record_map;
	map<string, VariableRecord *> parents_variable_record_map;
	string scope_type, scope_name, scope_return_type;

	Scope(int id, string type, string name, string return_type) : scope_id(id), scope_type(type), scope_name(name), scope_return_type(return_type)
	{
	}

	Scope(int id, Record *r) : scope_id(id), scope_type(r->recordtype), scope_name(r->name), scope_return_type(r->returntype)
	{
		cout << "New Scope from record : " << scope_type << " : " << scope_name << endl;
	}

	Scope(int id)
	{
		scope_id = id;
		scope_type = "goal";
		scope_name = "goal_name";
		scope_return_type = "void";
	}

	void make_new_child_scope(int id, Record *re)
	{
		Scope *new_scope = new Scope(id, re);
		new_scope->parent_scope = this;
		new_scope->depth = depth + 1;
		new_scope->parents_variable_record_map = this->variable_record_map;
		children_scope.push_back(new_scope);
		num_children++;
	}

	Scope *get_child(int index = -1)
	{

		if (index == -1)
		{
			return children_scope.back();
		}

		else
		{
			auto it = children_scope.begin();

			for (int i = 0; i < index; ++i)
			{
				it++;
			}
			return *it;
		}
		return children_scope.back();
	}

	void add_record(Record *re)
	{
		if (re->recordtype == "CLASS")
		{
			ClassRecord *c = dynamic_cast<ClassRecord *>(re);
			class_record_map[c->name] = c;
		}
		else if (re->recordtype == "METHOD")
		{
			MethodRecord *m = dynamic_cast<MethodRecord *>(re);
			method_record_map[m->name] = m;
		}
		else if (re->recordtype == "VARIABLE")
		{
			VariableRecord *v = dynamic_cast<VariableRecord *>(re);
			variable_record_map[v->name] = v;
		}

		cout << "Record added : " << re->name << " : " << re->recordtype << endl;
	}

	void test_print()
	{
		cout << "Print scope : " << scope_type << " : " << scope_name << endl;
	}

	string check_record(string key)
	{
		// Dont check parent var map
		if (variable_record_map.find(key) != variable_record_map.end())
		{
			return "VARIABLE";
		}
		if (method_record_map.find(key) != method_record_map.end())
		{
			return "METHOD";
		}
		if (class_record_map.find(key) != class_record_map.end())
		{
			return "CLASS";
		}
		return "NULL";
	}

	string traversal_check_record(string key)
	{
		string res = check_record(key);
		if (res == "NULL")
		{
			if (parents_variable_record_map.find(key) != parents_variable_record_map.end())
			{
				return "VARIABLE";
			}
		}
		return res;
	}

	Record *get_record(string key)
	{
		auto variableIt = variable_record_map.find(key);
		if (variableIt != variable_record_map.end())
		{
			return variableIt->second;
		}

		auto methodIt = method_record_map.find(key);
		if (methodIt != method_record_map.end())
		{
			return methodIt->second;
		}

		auto classIt = class_record_map.find(key);
		if (classIt != class_record_map.end())
		{
			return classIt->second;
		}

		auto parentvariableIt = parents_variable_record_map.find(key);
		if (parentvariableIt != parents_variable_record_map.end())
		{
			return parentvariableIt->second;
		}

		// Key not found in any map
		return nullptr;
	}

	Record *lookup_record(string key)
	{
		Record *re = get_record(key);
		if (re != nullptr)
		{
			return re;
		}
		else
		{
			Scope *c_scope = this;
			while (c_scope->parent_scope != nullptr)
			{
				c_scope = c_scope->parent_scope;
				Record *re = c_scope->get_record(key);
				if (re != nullptr)
				{
					return re;
				}
			}
			return new Record();
		}
	}
};

class SymbolTable
{
public:
	Scope *current_scope;
	Scope *root_scope;
	int scope_id_count = 0;
	bool semantic_error = false;
	int lineno;
	int children_class_index, children_method_index;
	ClassRecord *current_class_record;
	MethodRecord *current_method_record;
	string exec_node_type = "";

	SymbolTable()
	{
		current_scope = new Scope(scope_id_count);
		scope_id_count++;
		// current_scope->test_print();

		root_scope = current_scope;
		// cout << root_scope->num_children << endl;
	}

	void test_print()
	{
		cout << "ST Start" << endl;
	}

	void init(Node *root_node)
	{
		execute(root_node);
	}

	void execute(Node *n)
	{
		string type = n->type;
		string value = n->value;
		int id = n->id;
		list<Node *> children = n->children;

		lineno = n->lineno;

		if ((type == "CLASS_DECLARATION") || (type == "MAIN_CLASS_DECLARATION"))
		{
			execute_class_declaration(children.begin());
		}
		else if (type == "METHOD_DECLARATION")
		{
			execute_method_declaration(children.begin());
		}
		else if (type == "VAR_DECLARATION")
		{
			execute_var_declaration(children.begin());
		}
		else if (type == "EXPRESSION" || type == "STATEMENT")
		{
			execute_ex_st(n);
		}

		// Recursive through children
		for (Node *&child : children)
		{
			execute(n = child);
		}

		if ((type == "CLASS_DECLARATION") || (type == "MAIN_CLASS_DECLARATION") || (type == "METHOD_DECLARATION"))
		{
			exit_scope();
		}
	}

	void execute_ex_st(Node *n)
	{
		string type = n->type;
		string value = n->value;
		int id = n->id;
		list<Node *> children = n->children;

		lineno = n->lineno;

		if (type == "Identifier")
		{
			if (current_scope->traversal_check_record(value) == "NULL")
			{
				sem_error("Variable not declared : " + value);
			}
		}

		if (!(value == "NEW_CLASS_OBJECT" || value == "CALL_METHOD"))
		{
			for (Node *&child : children)
			{
				execute_ex_st(n = child);
			}
		}
	}

	void execute_class_declaration(auto iter)
	{
		exec_node_type = "CLASS";
		current_class_record = new ClassRecord();
		current_class_record->set_type((*iter)->value);
		current_class_record->set_name((*iter)->value);

		cout << "Exe class" << endl;

		current_scope->test_print();

		add_record_to_scope(current_class_record);

		make_and_enter_scope(current_class_record);

		// Add THIS
		VariableRecord *v = new VariableRecord();
		v->set_type(current_scope->scope_name);
		v->set_name("this");
		add_record_to_scope(v);
	}

	void execute_method_declaration(auto iter)
	{
		exec_node_type = "METHOD";
		current_method_record = new MethodRecord();
		auto iter2 = (*iter)->children.begin();
		current_method_record->set_type((*iter2)->type);
		iter++;
		current_method_record->set_name((*iter)->value);

		// Add method record to current class record
		current_class_record->method_map[current_method_record->name] = current_method_record;

		cout << "Exe method" << endl;

		current_scope->test_print();

		add_record_to_scope(current_method_record);

		make_and_enter_scope(current_method_record);

		iter++;
		// At param list
		for (auto it_param_list = (*iter)->children.begin(); it_param_list != (*iter)->children.end(); it_param_list++)
		{
			auto child_iter = (*it_param_list)->children.begin();
			execute_var_declaration(child_iter);
			current_method_record->param_list.push_back((*child_iter)->type);
			current_method_record->param_count++;
		}

		current_method_record->print_param_list();
	}

	void execute_var_declaration(auto iter)
	{
		VariableRecord *v = new VariableRecord();
		v->set_type((*iter)->type);

		iter++;
		v->set_name((*iter)->value);

		if (exec_node_type == "METHOD")
		{
			// Add var record to current method record
			current_method_record->variable_map[v->name] = v;
		}
		else if (exec_node_type == "CLASS")
		{
			// Add var record to current class record
			current_class_record->variable_map[v->name] = v;
		}

		add_record_to_scope(v);
	}

	void make_and_enter_scope(Record *re)
	{
		current_scope->make_new_child_scope(scope_id_count, re);
		scope_id_count++;
		enter_scope();
		// current_scope->test_print();
	}

	void add_record_to_scope(Record *re)
	{
		if ((current_scope->check_record(re->name)) != re->recordtype)
		{
			current_scope->add_record(re);
		}
		else
		{
			sem_error("Duplicate Identifier");
		}
	}

	void enter_scope(int index = -1)
	{
		current_scope = current_scope->get_child(index);
		cout << "Entering scope, now in: " << current_scope->scope_name << " : " << current_scope->scope_type << endl;
	}

	void exit_scope()
	{
		current_scope = current_scope->parent_scope;
		cout << "Exiting scope, now in: " << current_scope->scope_name << " : " << current_scope->scope_type << endl;
	}

	void semantic_traversal(Node *root_node)
	{
		children_class_index = 0;
		children_method_index = 0;
		current_scope = root_scope;
		sem_execute(root_node);
	}

	void sem_execute(Node *n)
	{
		string type = n->type;
		string value = n->value;
		int id = n->id;
		list<Node *> children = n->children;

		lineno = n->lineno;

		if (type == "METHOD_DECLARATION")
		{
			auto iter = children.begin();
			iter++;
			string method_name = (*iter)->value;
			enter_scope(children_method_index++);
		}
		else if ((type == "CLASS_DECLARATION") || (type == "MAIN_CLASS_DECLARATION"))
		{
			auto iter = children.begin();
			string class_name = (*iter)->value;
			enter_scope(children_class_index++);
		}

		else if (type == "VAR_DECLARATION")
		{
			auto iter = children.begin();
			string var_type = (*iter)->type;

			if (!(var_type == "TYPE_INT" || var_type == "TYPE_INT_ARRAY" || var_type == "TYPE_BOOLEAN"))
			{
				if (get_identifier_record_type(var_type) != "CLASS")
				{
					sem_error("Identifier is not CLASS");
				}
			}
		}

		else if (type == "RETURN")
		{
			sem_execute_return(children.begin());
		}

		else if (type == "STATEMENT")
		{
			if (value == "ASSIGN")
			{
				sem_execute_statement_assign(children.begin());
			}
			else if (value == "IF")
			{
				sem_execute_statement_if(children.begin());
			}
			else if (value == "IF_ELSE")
			{
				sem_execute_statement_if_else(children.begin());
			}
			else if (value == "WHILE")
			{
				sem_execute_statement_while(children.begin());
			}
			else if (value == "PRINT")
			{
				sem_execute_statement_print(children.begin());
			}
		}

		// Recursive through children
		for (Node *&child : children)
		{
			sem_execute(n = child);
		}

		if ((type == "CLASS_DECLARATION") || (type == "MAIN_CLASS_DECLARATION"))
		{
			exit_scope();
			children_method_index = 0;
		}
		else if (type == "METHOD_DECLARATION")
		{
			exit_scope();
		}
	}

	void sem_execute_return(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		string return_type;

		int save_return_line = lineno;

		return_type = sem_execute_expression(iter);

		lineno = save_return_line;

		cout << return_type << current_scope->scope_return_type << endl;
		if (return_type != current_scope->scope_return_type)
		{
			sem_error("Unmatched Return Type");
		}
	}

	void sem_execute_statement_assign(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		Record rec;
		string type_left, type_right;

		if (type == "Identifier")
		{
			type_left = get_identifier_return_type(value);
			iter++;
			type_right = sem_execute_expression(iter);

			if (type_left != type_right)
			{
				sem_error("Unmatched Type Assign");
			}
		}
		else if (type == "ARRAY_INDEX")
		{
			auto child_iter = (*iter)->children.begin();
			string type_array = get_identifier_return_type((*child_iter)->value);

			if (type_array != "TYPE_INT_ARRAY")
			{
				sem_error("VARIABLE IS NOT INT ARRAY");
			}

			child_iter++;
			string type_index = sem_execute_expression(child_iter);
			if (type_index != "TYPE_INT")
			{
				sem_error("INDEX IS NOT INT");
			}

			iter++;
			type_right = sem_execute_expression(iter);

			if (type_right != "TYPE_INT")
			{
				sem_error("Unmatched Type Assign in Int Array");
			}
		}
		else
		{
			sem_error("Invalid Assign");
		}
	}

	void sem_execute_statement_if(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		Record rec;

		if (type == "EXPRESSION" || type == "Identifier")
		{
			string type_if = sem_execute_expression(iter);
			if (type_if == "TYPE_BOOLEAN")
			{
				iter++;
				string statement_type = (*iter)->type;
				if (statement_type == "STATEMENT")
				{
					sem_execute(*iter);
				}
				else
				{
					sem_error("Invalid if statement");
				}
			}
			else
			{
				sem_error("If Expression is not boolean");
			}
		}
		else
		{
			sem_error("Invalid If");
		}
	}

	void sem_execute_statement_if_else(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		Record rec;

		if (type == "EXPRESSION" || type == "Identifier")
		{
			string type_if_else = sem_execute_expression(iter);
			if (type_if_else == "TYPE_BOOLEAN")
			{
				iter++;
				if ((*iter)->type == "STATEMENT")
				{
					sem_execute(*iter);
					iter++;
					if ((*iter)->type == "STATEMENT")
					{
						sem_execute(*iter);
					}
					else
					{
						sem_error("Invalid else statement");
					}
				}
				else
				{
					sem_error("Invalid if statement");
				}
			}
			else
			{
				sem_error("If Else expression is not boolean");
			}
		}
		else
		{
			sem_error("Invalid If Else");
		}
	}

	void sem_execute_statement_while(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		Record rec;

		if (type == "EXPRESSION" || type == "Identifier")
		{
			string type_while = sem_execute_expression(iter);
			if (type_while == "TYPE_BOOLEAN")
			{
				iter++;
				string statement_type = (*iter)->type;
				if (statement_type == "STATEMENT")
				{
					sem_execute(*iter);
				}
				else
				{
					sem_error("Invalid while statement");
				}
			}
			else
			{
				sem_error("While Expression is not boolean");
			}
		}
		else
		{
			sem_error("Invalid While");
		}
	}

	void sem_execute_statement_print(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		Record rec;

		if (type == "EXPRESSION" || type == "Identifier" || type == "Integer_Literal")
		{
			sem_execute_expression(iter);
		}
		else
		{
			sem_error("Invalid Print");
		}
	}

	string sem_execute_expression(auto iter)
	{
		string type = (*iter)->type;
		string value = (*iter)->value;
		string return_type_left, return_type_right;

		lineno = (*iter)->lineno;

		cout << type << value << endl;

		if (type == "Identifier")
		{
			return get_identifier_return_type(value);
		}
		else if (type == "Integer_Literal")
		{
			return "TYPE_INT";
		}
		else if (value == "TRUE" || value == "FALSE")
		{
			return "TYPE_BOOLEAN";
		}
		else if (value == "THIS")
		{
			return get_identifier_return_type("this");
		}
		else if (value == "+" || value == "-" || value == "*" || value == "/")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);
			child_iter++;
			return_type_right = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_INT" || return_type_right != "TYPE_INT")
			{
				sem_error("Unmatched Type Expression");
			}
			return "TYPE_INT";
		}
		else if (value == "<" || value == ">")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);
			child_iter++;
			return_type_right = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_INT" || return_type_right != "TYPE_INT")
			{
				sem_error("Unmatched Type Expression");
			}
			return "TYPE_BOOLEAN";
		}
		else if (value == "AND" || value == "OR")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);
			child_iter++;
			return_type_right = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_BOOLEAN" || return_type_right != "TYPE_BOOLEAN")
			{
				sem_error("Unmatched Type Expression");
			}
			return "TYPE_BOOLEAN";
		}
		else if (value == "==")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);
			child_iter++;
			return_type_right = sem_execute_expression(child_iter);

			if (return_type_left != return_type_right)
			{
				sem_error("Unmatched Type Expression");
			}
			return "TYPE_BOOLEAN";
		}
		else if (value == "ARRAY_INDEX")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);
			child_iter++;
			return_type_right = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_INT_ARRAY" || return_type_right != "TYPE_INT")
			{
				sem_error("Unmatched Array Index Type");
			}
			return "TYPE_INT";
		}
		else if (value == "LENGTH")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_INT_ARRAY")
			{
				sem_error("Unmatched Array Length Type");
			}
			return "TYPE_INT";
		}
		else if (value == "NOT")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_BOOLEAN")
			{
				sem_error("Invalid Not type");
			}
			return "TYPE_BOOLEAN";
		}
		else if (value == "NEW_INT_ARRAY")
		{
			auto child_iter = (*iter)->children.begin();
			return_type_left = sem_execute_expression(child_iter);

			if (return_type_left != "TYPE_INT")
			{
				sem_error("Unmatched New INT Array");
			}
			return "TYPE_INT_ARRAY";
		}
		else if (value == "NEW_CLASS_OBJECT")
		{
			auto child_iter = (*iter)->children.begin();

			string child_type = (*child_iter)->type;
			string child_value = (*child_iter)->value;

			if (child_type != "Identifier")
			{
				sem_error("Invalid new class");
			}

			else if (root_scope->check_record(child_value) != "CLASS")
			{
				sem_error("Undefined Class");
			}
			return child_value;
		}

		else if (value == "CALL_FUNCTION")
		{
			auto child_iter = (*iter)->children.begin();
			string called_obj = sem_execute_expression(child_iter);

			child_iter++;
			// string called_method = (*child_iter)->value;
			string called_method = (*(*child_iter)->children.begin())->value;

			if ((*(*child_iter)->children.begin())->type != "Identifier")
			{
				sem_error("Called in not identifier");
				return "NULL";
			}

			Record *re = root_scope->lookup_record(called_obj);

			if (re->recordtype != "CLASS")
			{
				sem_error("Called variable is not a class");
				return "NULL";
			}

			ClassRecord *c = dynamic_cast<ClassRecord *>(re);
			MethodRecord *m = c->get_method(called_method);

			if (m->name != called_method)
			{
				sem_error("No method in this class");
				return "NULL";
			}

			child_iter++;
			// At parm list
			int param_size = (*child_iter)->children.size();
			if (m->param_count != param_size)
			{
				sem_error("Unmatch parameter count");
				return m->returntype;
			}

			auto defined_param_iter = m->param_list.begin();
			auto called_param_iter = (*child_iter)->children.begin();

			for (; defined_param_iter != m->param_list.end() && called_param_iter != (*child_iter)->children.end(); ++defined_param_iter, ++called_param_iter)
			{
				string defined_param_type = *defined_param_iter;
				string called_param_type = sem_execute_expression(called_param_iter);
				if (defined_param_type != called_param_type)
				{
					sem_error("Unmatch parameter type");
					return m->returntype;
				}
			}

			return m->returntype;
		}

		return "NULL";
	}

	string get_identifier_return_type(string name)
	{
		Record *rec;
		rec = current_scope->lookup_record(name);

		if (rec->recordtype == "")
		{
			sem_error("Unknown Identifier");
		}
		else
		{
			return rec->returntype;
		}

		return "NULL";
	}

	string get_identifier_record_type(string name)
	{
		Record *rec;
		rec = current_scope->lookup_record(name);

		if (rec->recordtype == "")
		{
			sem_error("Unknown Identifier");
		}
		else
		{
			return rec->recordtype;
		}

		return "NULL";
	}

	void sem_error(string error_message = "Semantic error")
	{
		cerr << "\t@error at line " << lineno << ". " << error_message << endl;
		semantic_error = true;
	}

	void generate_tree()
	{
		std::ofstream outStream;
		char *filename = "st.dot";
		outStream.open(filename);

		// int count = 0;
		outStream << "digraph {" << std::endl;
		generate_tree_content(&outStream, root_scope);
		outStream << "}" << std::endl;
		outStream.close();

		printf("\nBuilt a st-tree at %s. Use 'make st' to generate the pdf version.\n", filename);
	}

	void generate_tree_content(ofstream *outStream, Scope *sc)
	{
		string label = sc->scope_type + ":" + sc->scope_name + "\n -----------------------------------\n";

		for (auto pair : sc->class_record_map)
		{
			label += "name: " + pair.second->name + "; record: " + pair.second->recordtype + "; return_type: " + pair.second->returntype + "\n";
		}
		for (auto pair : sc->method_record_map)
		{
			label += "name: " + pair.second->name + "; record: " + pair.second->recordtype + "; return_type: " + pair.second->returntype + "\n";
		}
		for (auto pair : sc->variable_record_map)
		{
			label += "name: " + pair.second->name + "; record: " + pair.second->recordtype + "; return_type: " + pair.second->returntype + "\n";
		}

		*outStream << "n" << sc->scope_id << " [label=\"" << label << "\"];" << endl;
		for (auto i = sc->children_scope.begin(); i != sc->children_scope.end(); i++)
		{
			generate_tree_content(outStream, *i);
			*outStream << "n" << sc->scope_id << " -> n" << (*i)->scope_id << endl;
		}
	}
};

#endif