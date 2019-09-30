#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidInfix(string infix, int start, int end) {
    if (start > end)
        return false;
    while (infix[start] == ' ' || infix[start] == '!')
        start++;
    if (start > end)
        return false;
    
    if (islower(infix[start])) {
        start++;
        if (start > end)
            return true;
        while (infix[start] == ' ')
            start++;
        if (start > end)
            return true;
        
        if (infix[start] == '&' || infix[start] == '|') {
            start++;
            return isValidInfix(infix, start, end);
        }
        return false;
    }
    
    if (infix[start] == '(') {
        int numOpen = 1;
        int numClosed = 0;
        
        for (int i = start+1; i <= end; i++) {
            if (infix[i] == '(')
                numOpen++;
            if (infix[i] == ')')
                numClosed++;
            
            if (numOpen == numClosed) {
                if (!isValidInfix(infix, start + 1, i - 1))
                    return false;
                
                start = i + 1;
                if (start > end)
                    return true;
                while (infix[start] == ' ')
                    start++;
                if (start > end)
                    return true;
                
                if (infix[start] == '&' || infix[start] == '|') {
                    start++;
                    return isValidInfix(infix, start, end);
                }
                return false;
            }
        }
        
        return false;
    }
    
    return false;
}

void inToPost(string infix, string& postfix) {
    postfix = "";
    stack<char> oper;
    
    for (int i = 0; i < infix.size(); i++) {
        if (islower(infix[i]))
            postfix += infix[i];
        
        if (infix[i] == '(' || infix[i] == '!')
            oper.push(infix[i]);
        
        if (infix[i] == ')') {
            while (oper.top() != '(') {
                postfix += oper.top();
                oper.pop();
            }
            oper.pop();
        }
        
        if (infix[i] == '|') {
            while (!oper.empty() && oper.top() != '(') {
                postfix += oper.top();
                oper.pop();
            }
            oper.push(infix[i]);
        }
        
        if (infix[i] == '&') {
            while (!oper.empty() && oper.top() != '(' && oper.top() != '|') {
                postfix += oper.top();
                oper.pop();
            }
            oper.push(infix[i]);
        }
    }
    while (!oper.empty()) {
        postfix += oper.top();
        oper.pop();
    }
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    if (!isValidInfix(infix, 0, infix.size() - 1))
        return 1;
    inToPost(infix, postfix);
    
    for (int i = 0; i < infix.size(); i++) {
        if (islower(infix[i])) {
            if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i]))
                return 2;
            if (trueValues.contains(infix[i]) && falseValues.contains(infix[i]))
                return 3;
        }
    }
    
    stack<bool> operands;
    for (int i = 0; i < postfix.size(); i++) {
        if (islower(postfix[i])) {
            if (trueValues.contains(postfix[i]))
                operands.push(true);
            else
                operands.push(false);
        }
        else if (postfix[i] == '!') {
            bool operand = !operands.top();
            operands.pop();
            operands.push(operand);
        }
        else {
            bool operand2 = operands.top();
            operands.pop();
            bool operand1 = operands.top();
            operands.pop();
            if (postfix[i] == '&')
                operands.push(operand1 && operand2);
            else
                operands.push(operand1 || operand2);
        }
    }
    
    result = operands.top();
    return 0;
}

int main() {
    
}
