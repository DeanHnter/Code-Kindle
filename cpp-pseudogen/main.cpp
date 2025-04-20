#include <bits/stdc++.h>
#include <iostream>

using namespace std;
set<string> data_type, condition, loop, Array;
set<char> useless, bracket;
map<string, string> map_variable, keyword, condmap;
set<string> qualifiers;
int indent;
ofstream outFile("output.txt", ios::out);
map<string, string> opmap = {
    {"+", "Add"}, {"-", "Subtract"}, {"*", "Multiply"}, 
    {"/", "Divide"}, {"%", "Modulo"}, {"&&", "AND"}, 
    {"||", "OR"}, {"!", "NOT"}, {"->", "access member"}
};

void intialize() //Create mapping for different elements of code i.e variables, datatypes, words that are of no use etc.
{
    qualifiers = {"const", "volatile", "static", "extern", "register"};
    /* store the appropriate keyword in appropriate set*/
    data_type = {"int", "float", "string", "char", "double", "long", "short", "unsigned", "bool", "void"};
    useless = {'<', '>', ';', ',', ' ', '"', '(', '*', '&'};
    condition = {"if", "else", "else if", "switch"};
    loop = {"for"};
    keyword = {{"int", "Integer"}, {"char", "Character"}, {"string", "String"}, {"float", "Float"}, {"double", "Double"}, {"long", "Long"}, {"short", "Short"}, {"unsigned", "Unsigned"}, {"bool", "Boolean"}, {"void", "Void"}};
    condmap = {{">", " greater "}, {"<", " less than "}, {"!=", " not equal "}, {"==", " equals "}, {">=", " greater than or equal to "}, {"<=", "less than or equal to"}};
    bracket = {'(', ')', '{', '}'};
}

void func_cin(string line)
{ //Create pseudo code for 'cin'

    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end()) //Covering up the spaces
        i++;
    i = i + 3; // covering up 'cin' i.e 3 words;
    while (i < line.size())
    {
        string temp = "";
        while (i < line.size() && useless.find(line[i]) != useless.end())
            i++;

        if (i >= line.size())
            break;
        while (i < line.size() && !(useless.find(line[i]) != useless.end()))
        {
            temp += line[i];
            i++;
        }
        for (int j = 0; j < indent; j++)
        {
            outFile << "   ";
            cout << "   ";
        }
        outFile << "Enter ";
        cout << "Enter ";
        outFile << map_variable[temp] << " " << temp << "\n";
        cout << map_variable[temp] << " " << temp << "\n";
    }
}

void func_cout(string line)
{ //Create pseudo code for 'cout'
    size_t i = 0;
    while (i < line.size() && line[i] == ' ') //Covering up the spaces
        i++;
    i = i + 4; // covering up 'cin' i.e 3 words;
    while (i < line.size())
    {
        string temp = "";
        while (i < line.size() && useless.find(line[i]) != useless.end())
            i++;

        if (i >= line.size())
            break;
        while (i < line.size() && !(useless.find(line[i]) != useless.end()))
        {
            temp += line[i];
            i++;
        }
        for (int j = 0; j < indent; j++)
        {
            outFile << "   ";
            cout << "   ";
        }
        outFile << "Print ";
        cout << "Print ";
        outFile << map_variable[temp] << " " << temp << "\n";
        cout << map_variable[temp] << " " << temp << "\n";
    }
}

void func_return(string line) //Create pseudo code for 'return' statement for a function including 'main' as well
{
    size_t i = 0;
    while (i < line.size() && line[i] == ' ') //Covering up the spaces
        i++;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "function Returns ";
    cout << "function Returns ";
    i = i + 6; //covering up return
    string temp;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    temp = line[i];
    outFile << temp << "\n";
    cout << temp << "\n";
}

void func_dt(string line) //Mapping of varaibles to their data types.
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end()) //Covering up the spaces
        i++;

    string Data_type = "";
    while (i < line.size() && !(useless.find(line[i]) != useless.end()))
    {
        Data_type += line[i];
        i++;
    }
    size_t check_array = 0;
    string temp;
    vector<string> var_name;
    string qualifier = "";
    // Check for qualifiers before data type
    while (i < line.size()) {
        // Check if current Data_type is a qualifier
        if (qualifiers.find(Data_type) != qualifiers.end()) {
            qualifier += Data_type + " ";
            // Get next token after qualifier
            Data_type = "";
            while (i < line.size() && useless.find(line[i]) != useless.end())
                i++;
            while (i < line.size() && !useless.count(line[i])) {
                Data_type += line[i];
                i++;
            }
        } else {
            break; // Exit when non-qualifier found
        }
    }

    while (i < line.size())
    {
        temp = "";
        while (i < line.size() && useless.find(line[i]) != useless.end())
            i++;

        if (i >= line.size())
            break;
        size_t detect_function = 0;
        while (i < line.size() && (!(useless.find(line[i]) != useless.end()) || line[i] == '('))
        {
            if (line[i] == '[')
            {
                i += 2;
                check_array = 1;
                break;
            }
            if (line[i] == '(')
            {
                detect_function = 1;
                break;
            }
            temp += line[i];
            i++;
        }
        if (detect_function)
        {
            for (int j = 0; j < indent; j++)
            {
                outFile << "   ";
                cout << "   ";
            }
            outFile << "Declare Function " << temp << "\n";
            cout << "Declare Function " << temp << "\n";
            break;
        }

        if (check_array)
        {
            for (int j = 0; j < indent; j++)
            {
                outFile << "   ";
                cout << "   ";
            }
            map_variable[temp] = keyword[Data_type];
            outFile << "Declare 1 " << keyword[Data_type] << " Array " << temp << "\n";
            cout << "Declare 1 " << keyword[Data_type] << " Array " << temp << "\n";
            check_array = 0;
            continue;
        }
        map_variable[temp] = keyword[Data_type];
        var_name.push_back(temp);
    }

    if (!var_name.empty())
    {
        for (int j = 0; j < indent; j++)
        {
            outFile << "   ";
            cout << "   ";
        }
        outFile << "Declare " << qualifier << keyword[Data_type] << " variable ";
        cout << "Declare " << qualifier << keyword[Data_type] << " variable ";
        for (auto value : var_name)
        {
            outFile << value << " ";
            cout << value << " ";
        }
        outFile << "\n";
        cout << "\n";
    }

    if (line.find("(*") != string::npos) {
        outFile << "Function pointer " << temp << "\n";
    }
}

void func_cond(string line) //Generatting Pseudo code for conditions like if. (currently only if), else can be included later on.
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    while (line[i] != '(')
        i++;
    i++;
    outFile << "Check if ";
    cout << "Check if ";
    while (line[i] != ')')
    {
        outFile << line[i];
        cout << line[i];
        i++;
    }
    outFile << "\n";
    cout << "\n";
    for (int j = 0; j < indent + 1; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "If True then : ";
    outFile << "\n";
    cout << "If True then : ";
    cout << "\n";
}

void func_loop(string line) //Create pseudo code for loops like for, while etc
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Start a loop from ";
    cout << "Start a loop from ";
    while (line[i] != '(')
        i++;
    i++;
    while (line[i] != ';')
    {
        outFile << line[i];
        cout << line[i];
        i++;
    }
    i++;
    outFile << " till ";
    cout << " till ";
    while (line[i] != ';')
    {
        outFile << line[i];
        cout << line[i];
        i++;
    }
    outFile << "\n";
    cout << "\n";
}

void func_oper(string line) //Create pseudo code for different operations
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Perform operation: ";
    cout << "Perform operation: ";
    string temp = "";
    while (line[i] == ' ')
        i++;

    while (i < line.size() && (!(useless.find(line[i]) != useless.end()) || line[i] == ' '))
    {
        temp += line[i];
        i++;
    }
    for (auto& [op, pseudocode] : opmap) {
        size_t pos = temp.find(op);
        if (pos != string::npos) {
            temp.replace(pos, op.length(), pseudocode);
        }
    }
    outFile << temp << "\n";
    cout << temp << "\n";
}

void func_scanf(string line) // pseudo for "scanf"
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 5; // skip "scanf"
    while (i < line.size() && line[i] != '"')
        i++; // move to first quote if present
    // skip format string if any
    if (i < line.size() && line[i] == '"')
    {
        i++;
        while (i < line.size() && line[i] != '"')
            i++;
        if (i < line.size())
            i++; // skip closing quote
    }
    // now read variable names after commas or &
    while (i < line.size())
    {
        while (i < line.size() && useless.find(line[i]) != useless.end())
            i++;
        string temp = "";
        while (i < line.size() && !(useless.find(line[i]) != useless.end()))
        {
            if (line[i] == '&')
            {
                i++; // skip ampersand
                continue;
            }
            temp += line[i];
            i++;
        }
        if (temp.empty())
            continue;
        for (int j = 0; j < indent; j++)
        {
            outFile << "   ";
            cout << "   ";
        }
        outFile << "Input into " << map_variable[temp] << " " << temp << "\n";
        cout << "Input into " << map_variable[temp] << " " << temp << "\n";
    }
}

void func_printf(string line) // pseudo for "printf"
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 6; // skip "printf"
    // Extract format string inside quotes
    string format = "";
    while (i < line.size() && line[i] != '"')
        i++;
    if (i < line.size() && line[i] == '"')
    {
        i++;
        while (i < line.size() && line[i] != '"')
        {
            format += line[i];
            i++;
        }
        if (i < line.size())
            i++; // skip ending quote
    }

    // Print the literal text first (if any)
    if (!format.empty())
    {
        for (int j = 0; j < indent; j++)
        {
            outFile << "   ";
            cout << "   ";
        }
        outFile << "Print Text: " << format << "\n";
        cout << "Print Text: " << format << "\n";
    }

    // After the closing quote there might be comma separated variables
    while (i < line.size() && line[i] != ')')
        i++;
    // Actually, the variable list is between closing quote and ')' separated by commas
    // We need to go back to just after closing quote; but easier: search for ',' tokens and names before ')'
    size_t pos = line.find(',');
    if (pos != string::npos)
    {
        i = pos + 1;
        while (i < line.size() && line[i] != ')')
        {
            while (i < line.size() && useless.find(line[i]) != useless.end())
                i++;
            string temp = "";
            while (i < line.size() && !(useless.find(line[i]) != useless.end()))
            {
                temp += line[i];
                i++;
            }
            if (temp.empty())
                continue;
            for (int j = 0; j < indent; j++)
            {
                outFile << "   ";
                cout << "   ";
            }
            outFile << "Print " << map_variable[temp] << " " << temp << "\n";
            cout << "Print " << map_variable[temp] << " " << temp << "\n";
        }
    }
}

void func_else_cond(string line)
{
    // prints an else branch
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Else :\n";
    cout << "Else :\n";
}

void func_while_loop(string line)
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Start while loop with condition ";
    cout << "Start while loop with condition ";
    while (line[i] != '(' && i < line.size())
        i++;
    i++;
    while (i < line.size() && line[i] != ')')
    {
        outFile << line[i];
        cout << line[i];
        i++;
    }
    outFile << "\n";
    cout << "\n";
}

void func_do_loop(string line)
{
    // The line containing 'do' usually starts the loop body, condition will appear later on while();
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Start do-while loop body\n";
    cout << "Start do-while loop body\n";
}

void func_switch(string line)
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Switch on ";
    cout << "Switch on ";
    while (i < line.size() && line[i] != '(')
        i++;
    i++;
    while (i < line.size() && line[i] != ')')
    {
        outFile << line[i];
        cout << line[i];
        i++;
    }
    outFile << "\n";
    cout << "\n";
}

void func_case(string line)
{
    size_t i = 0;
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    string keyword_case = "";
    // assume word "case" is passed; skip it
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 4; // skip "case"
    string value = "";
    while (i < line.size() && line[i] != ':')
    {
        if (useless.find(line[i]) == useless.end())
            value += line[i];
        i++;
    }
    outFile << "Case " << value << " :\n";
    cout << "Case " << value << " :\n";
}

void func_struct(string line)
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 6; // skip 'struct'
    string name = "";
    while (i < line.size() && !(useless.find(line[i]) != useless.end()))
    {
        name += line[i];
        i++;
    }
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Declare struct " << name << "\n";
    cout << "Declare struct " << name << "\n";
}

void func_enum(string line)
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 4; // skip 'enum'
    string name = "";
    while (i < line.size() && !(useless.find(line[i]) != useless.end()))
    {
        name += line[i];
        i++;
    }
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Declare enum " << name << "\n";
    cout << "Declare enum " << name << "\n";
}

void func_typedef(string line)
{
    size_t pos = line.find("typedef");
    size_t end = line.rfind(';');
    string parts = line.substr(pos+7, end-pos-7);
    // Parse "old new" from parts
    size_t space = parts.find_last_of(' ');
    string old_type = parts.substr(0, space);
    string new_type = parts.substr(space+1);
    
    for (int j = 0; j < indent; j++) {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Define type alias " << new_type << " for " << old_type << "\n";
}

void func_include(string line)
{
    string header = line; // raw line
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Include library " << header.substr(header.find('<')+1, header.find('>')-header.find('<')-1) << "\n";
    cout << "Include library " << header.substr(header.find('<')+1, header.find('>')-header.find('<')-1) << "\n";
}

void func_define(string line)
{
    size_t i = 0;
    while (i < line.size() && useless.find(line[i]) != useless.end())
        i++;
    i += 7; // skip '#define'
    string macro = "";
    while (i < line.size() && !(useless.find(line[i]) != useless.end()))
        macro += line[i++];
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Define macro " << macro << "\n";
    cout << "Define macro " << macro << "\n";
}

void func_break_stmt(string line)
{
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Break from loop/switch\n";
    cout << "Break from loop/switch\n";
}

void func_continue_stmt(string line)
{
    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Continue to next iteration\n";
    cout << "Continue to next iteration\n";
}

void func_preprocessor(string line)
{
    // Remove leading spaces
    size_t i = 0;
    while (i < line.size() && line[i] == ' ')
        i++;
    if (i >= line.size() || line[i] != '#')
        return;
    i++; // skip '#'
    // Extract directive
    string directive = "";
    while (i < line.size() && !isspace(line[i]))
    {
        directive += line[i];
        i++;
    }
    // Skip spaces
    while (i < line.size() && isspace(line[i]))
        i++;
    string rest = line.substr(i);

    for (int j = 0; j < indent; j++)
    {
        outFile << "   ";
        cout << "   ";
    }

    if (directive == "include")
    {
        size_t start = rest.find('<');
        size_t end = rest.find('>');
        string header = rest;
        if (start != string::npos && end != string::npos && end > start)
            header = rest.substr(start + 1, end - start - 1);
        outFile << "Include library " << header << "\n";
        cout << "Include library " << header << "\n";
    }
    else if (directive == "define")
    {
        outFile << "Define macro " << rest << "\n";
        cout << "Define macro " << rest << "\n";
    }
    else if (directive == "ifdef")
    {
        outFile << "If macro defined " << rest << "\n";
        cout << "If macro defined " << rest << "\n";
    }
    else if (directive == "ifndef")
    {
        outFile << "If macro NOT defined " << rest << "\n";
        cout << "If macro NOT defined " << rest << "\n";
    }
    else if (directive == "endif")
    {
        outFile << "End preprocessor conditional\n";
        cout << "End preprocessor conditional\n";
    }
    else if (directive == "elif")
    {
        outFile << "Else if preprocessor condition: " << rest << "\n";
        cout << "Else if preprocessor condition: " << rest << "\n";
    }
    else if (directive == "else")
    {
        outFile << "Preprocessor else branch\n";
        cout << "Preprocessor else branch\n";
    }
    else if (directive == "undef")
    {
        outFile << "Undefine macro " << rest << "\n";
        cout << "Undefine macro " << rest << "\n";
    }
    else if (directive == "pragma")
    {
        outFile << "Compiler pragma: " << rest << "\n";
        cout << "Compiler pragma: " << rest << "\n";
    }
    else if (directive == "error")
    {
        outFile << "Preprocessor error: " << rest << "\n";
        cout << "Preprocessor error: " << rest << "\n";
    }
    else if (directive == "warning")
    {
        outFile << "Preprocessor warning: " << rest << "\n";
        cout << "Preprocessor warning: " << rest << "\n";
    }
    else if (directive == "if")
    {
        outFile << "Preprocessor if condition: " << rest << "\n";
        cout << "Preprocessor if condition: " << rest << "\n";
    }
    else
    {
        outFile << "Preprocessor directive '" << directive << "' with args: " << rest << "\n";
        cout << "Preprocessor directive '" << directive << "' with args: " << rest << "\n";
    }
}

void func_goto(string line) {
    string label = line.substr(line.find("goto")+5);
    outFile << "Jump to label " << label << "\n";
}

void func_label(string line) {
    string label = line.substr(0, line.find(":"));
    outFile << "Label " << label << ":\n";
}

void process_comments(string line) {
    if (line.find("//") != string::npos) {
        outFile << "Note: " << line.substr(line.find("//")+2) << "\n";
    }
    // Handle /* */ comments similarly
}

void func_malloc(string line) {
    size_t eq_pos = line.find('=');
    size_t var_start = line.rfind(' ', eq_pos) + 1;
    string var = line.substr(var_start, eq_pos-var_start);
    
    for (int j = 0; j < indent; j++) {
        outFile << "   ";
        cout << "   ";
    }
    outFile << "Allocate memory for " << var << "\n";
}

void func_union(string line) {}

void check(string word, string line) //Checking for various conditions.
{
    if (word == "cin")
    {
        func_cin(line);
    }
    else if (word == "cout")
    {
        func_cout(line);
    }
    else if (word == "return")
    {
        func_return(line);
    }
    else if (data_type.find(word) != data_type.end())
    {
        func_dt(line);
    }
    else if (condition.find(word) != condition.end())
    {
        func_cond(line);
    }
    else if (loop.find(word) != loop.end())
    {
        func_loop(line);
    }
    else if (map_variable.find(word) != map_variable.end())
    {
        func_oper(line);
    }
    else if (word == "scanf")
    {
        func_scanf(line);
    }
    else if (word == "printf")
    {
        func_printf(line);
    }
    else if (word == "else")
    {
        func_else_cond(line);
    }
    else if (word == "while")
    {
        func_while_loop(line);
    }
    else if (word == "do")
    {
        func_do_loop(line);
    }
    else if (word == "switch")
    {
        func_switch(line);
    }
    else if (word == "case")
    {
        func_case(line);
    }
    else if (word == "struct")
    {
        func_struct(line);
    }
    else if (word == "enum")
    {
        func_enum(line);
    }
    else if (word == "typedef")
    {
        func_typedef(line);
    }
    else if (word == "break")
    {
        func_break_stmt(line);
    }
    else if (word == "continue")
    {
        func_continue_stmt(line);
    }
    else if (line.rfind("#", 0) == 0)
    {
        func_preprocessor(line);
    }
    else if (word == "goto") func_goto(line);
    else if (word == "malloc") func_malloc(line);
    else if (line.find(":") != string::npos && line.find(";") == string::npos) 
        func_label(line);
    else if (word == "union") func_union(line);
    else{}
}

int main()
{
    ifstream inFile("prog.cpp");
    //Input file containing Pseudo code

    intialize();
    string line;
    size_t i = 0;
    // cout << "line" << inFile << "\n";
    while (getline(inFile, line))
    {
        i = 0;
        string word = "";
        while (i < line.size() && ((useless.find(line[i]) != useless.end())))
            i++;

        while (i < line.size() && !(useless.find(line[i]) != useless.end()))
        {
            word += line[i];
            i++;
        }
        if (word == "{")
        {
            indent++;
            continue;
        }
        if (word == "}")
        {
            indent--;
            continue;
        }
        check(word, line);
    }

    inFile.close();
    outFile.close();

    return 0;
}
