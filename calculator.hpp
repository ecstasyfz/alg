#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

long double stod(string s) {
    return 0;
}

long double calculator(std::string &expr) {
    long double res;

    stack<char> brackets_stack;
    stack<char> symbols_stack;

    set<char> bracket_symbols;
    set<char> symbols;

    vector<string> parse;

    for (int i = 0; i < expr.size(); i++) {
        static bool operator_on = true;
        if (symbols.count(expr[i])) {
           if (bracket_symbols.count((expr[i]))) {
               switch (expr[i]) {
                    case '(' :
                       brackets_stack.push(expr[i]);
                       break;
                    case '[' :
                       brackets_stack.push(expr[i]);
                       break;
                    case '{' :
                       brackets_stack.push(expr[i]);
                       break;
                    case ')' :
                       if (brackets_stack.empty() || brackets_stack.top() != '(') {
                           return 0;
                       }
                       brackets_stack.pop();
                       break;
                    case ']' :
                       if (brackets_stack.top() != '[') {
                           return 0;
                       }
                       brackets_stack.pop();
                       break;
                    case '}' :
                       if (brackets_stack.top() != '{') {
                           return 0;
                       }
                       brackets_stack.pop();
                       break;
               }
            } else {
                if (operator_on) {
                    return 0;
                } else {
                    operator_on = true;
                } 
            }
            parse.push_back({expr[i]});
        } else {
            int j = i;
            while (!(symbols.count(expr[++i]))) {}
            parse.push_back(expr.substr(j, i));
            operator_on = false;
        }
    }

    for (auto &s : parse) {

    }

    return res;
}


#endif
