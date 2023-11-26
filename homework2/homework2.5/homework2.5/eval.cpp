#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);

bool validInfixExpression(string infix);

bool is_operator(char c) {
    return c == '|' || c == '&' || c == '!';
}

string infixToPostfix(string infix);

bool evaluatePostfix(string postfix, Set trueValues, Set falseValues);



// MAIN MAIN fahsjdklfhajlskdfhajklshf
// MAIN MAIN fajksd;fljaskldjf;alskfdf
// MAIN MAIN fasjdflaskjdfklajsdfkjsld


//int main(){
//
//
//
//
//            string trueChars  = "tywz";
//            string falseChars = "fnx";
//            Set trues;
//            Set falses;
//            for (int k = 0; k < trueChars.size(); k++)
//                trues.insert(trueChars[k]);
//            for (int k = 0; k < falseChars.size(); k++)
//                falses.insert(falseChars[k]);
//
//            string pf;
//            bool answer;
//            assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
//            assert(evaluate("y|", trues, falses, pf, answer) == 1);
//            assert(evaluate("n t", trues, falses, pf, answer) == 1);
//            assert(evaluate("nt", trues, falses, pf, answer) == 1);
//            assert(evaluate("()", trues, falses, pf, answer) == 1);
//            assert(evaluate("()z", trues, falses, pf, answer) == 1);
//            assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
//            assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
//            assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
//            assert(evaluate("n+y", trues, falses, pf, answer) == 1);
//            assert(evaluate("", trues, falses, pf, answer) == 1);
//            assert(evaluate("!!f  |  !f & !(t&n) ", trues, falses, pf, answer) == 0 &&  pf == "ff!tn&!&|"  &&  answer);
//            assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
//            trues.insert('x');
//            assert(evaluate("((x))", trues, falses, pf, answer) == 3);
//            falses.erase('x');
//            assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
//            trues.erase('w');
//            assert(evaluate("w| f", trues, falses, pf, answer) == 2);
//            falses.insert('w');
//            assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
//            cout << "Passed all tests" << endl;
//        }




// ACTUAL FUNCTIONS t4hiqgoaublsjknzcfwoire
// ACTUAL FUNCTIONS ahsucdfobuvnnsrioravofi
// ACTUAL FUNCTIONS hq9nouwhfiouqwefnhrxoao

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    
    if(!validInfixExpression(infix))
        return 1;
    
    postfix = infixToPostfix(infix);
    
    // check that all letters appear in either true or false but not both
    // if one letter is in neither set return 2
    // if one letter is in both sets return 3

    for (char c: postfix){
        if (islower(c)){
            if (!trueValues.contains(c) && !falseValues.contains(c))
                return 2;
            else if (trueValues.contains(c) && falseValues.contains(c))
                return 3;
        }
    }
    
    result = evaluatePostfix(postfix, trueValues, falseValues);
    return 0;
}



    // converts infix to postfix
string infixToPostfix(string infix){
    string postfix;
    stack<char> operators;
    stack<char> nots;


    for (int i = 0; i < infix.size(); i++){
        char c = infix[i];
        switch (c) {
            case '!':
                if (nots.empty() == false)
                    nots.pop();
                else if (infix[i+1] == '(')
                    operators.push(c);
                else
                    nots.push(c);
                break;
            case '|':
            case '&':
                while (operators.empty() == false && operators.top() != '(' && operators.top() != '|'){
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(c);
                break;
            case '(':
                operators.push(c);
                break;
            case ')':
                while (operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop();
                if (operators.empty() == false && operators.top() == '!'){
                    postfix += operators.top();
                    operators.pop();
                }

                break;
            case ' ':
                break;
            default:
                postfix += c;
                while(nots.empty() == false){
                    postfix += nots.top();
                    nots.pop();
                }
                break;
        }
    }

    while (operators.empty() == false) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}





    // evaluates postfix expression
bool evaluatePostfix(string postfix, Set trueValues, Set falseValues){
    
    trueValues.insert('T');
    falseValues.insert('F');
    
    stack<char> operand;
        
    for (char c: postfix){
        switch(c){
            case '|':{
                bool op1 = trueValues.contains(operand.top());
                operand.pop();
                bool op2 = trueValues.contains(operand.top());
                operand.pop();
            
                if (op1 || op2)
                    operand.push('T');
                else
                    operand.push('F');
                break;
            }
                
            case '&':{
                bool op1 = trueValues.contains(operand.top());
                operand.pop();
                bool op2 = trueValues.contains(operand.top());
                operand.pop();
                
                if (op1 && op2)
                    operand.push('T');
                else
                    operand.push('F');
                break;
            }
                
            case '!':{
                bool op1 = trueValues.contains(operand.top());
                operand.pop();
                
                if (!op1)
                    operand.push('T');
                else
                    operand.push('F');
                break;
            }
                
            default:
                operand.push(c);
                break;
        }
    }
    
    return trueValues.contains(operand.top());
}





    // determines if infix expression is valid or not
    // checks that parentheses are valid and have open and closing parentheses
    // determines if rest of function is valid or not
bool validInfixExpression(string infix){

    stack<char> pStack;
    stack<char> math;
    

    for (int i = 0; i < infix.size(); i++){
        char c = infix[i];
        if (c == '('){
            if (infix[i+1] != '!' && islower(infix[i+1]) == false && infix[i+1] != '(')
                return false;
            pStack.push(c);
        }
        else if (c == ')'){
            if (pStack.empty() || pStack.top() != '(')
                return false;
            pStack.pop();
        }
        else if (c == '|' || c == '&' || c == '!' || islower(c))
            math.push(c);
        else if(c == ' '){}
        else
            return false;
    }
    
    
    
    if (math.empty() || pStack.empty() == false)
        return false;
    
    while(math.empty() == false){
        if(islower(math.top()) == false)
            return false;
        math.pop();
        while (!math.empty() && math.top() == '!')
            math.pop();
        if (math.empty())
            return true;
        if (is_operator(math.top()) )
            math.pop();
        else
            return false;
    }
    
    

    return true;
}
