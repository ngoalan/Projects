#include "arithmeticExpression.h"
#include<iostream>
#include<string>
#include <stack>
#include <cstdlib>
#include<sstream>
#include <fstream>


using namespace std;

int arithmeticExpression::priority(char o){
    int priority = 0;
    if(o=='('){
        priority = 3;
    }
    else if(o=='*'||o=='/'){
        priority = 2;
    }
    else if(o=='+'||o=='-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &outfile, TreeNode *node){
    if (node -> left != nullptr) {
        outfile << "\t" << node -> key << " -> " << node -> left -> key << endl;
        outfile << "\t" << node -> key << " -> " << node -> right -> key << endl;
        visualizeTree(outfile, node -> left);
        visualizeTree(outfile, node -> right);
    }
}


arithmeticExpression::arithmeticExpression(const string& input){
    root = nullptr;
    infixExpression = input;
}

void arithmeticExpression::buildTree(){ //to do 
    infixExpression = infix_to_postfix();
    stack <TreeNode*> s;
    
    for(unsigned i = 0; i < infixExpression.length(); i++){ //goes through the length of the expression
        TreeNode* node = new TreeNode(infixExpression.at(i), 'a' + i);
        if(priority(infixExpression.at(i)) == 0){//means its not an operator 
            s.push(node); //push onto the stack
        }
        else{ //means its an operator
            node -> right = s.top(); //second val is right
            s.pop();
            node -> left = s.top(); //first val is left
            s.pop();
            s.push(node); //push the operator
            
        }
    }
    root = s.top();
}

void arithmeticExpression::infix(){
    infix(root);
}

void arithmeticExpression::postfix(){
    postfix(root);
}

void arithmeticExpression::prefix(){
    prefix(root);
}

int arithmeticExpression::evaluate(){
    if(!isValidIntegerExpression(root)){
        throw invalid_argument("expression not valid");
    }
    else{
        return evaluateIntegerExpression(root);
    }
}

int arithmeticExpression::evaluateIntegerExpression(TreeNode* node){
    if(node ->data>='0'&& node->data <='9'){
        switch (node->data){
            case '0':
            return 0;
            break;
            case '1':
            return 1;
            break;
            case '2':
            return 2;
            break;
            case '3':
            return 3;
            break;
            case '4':
            return 4;
            break;
            case '5':
            return 5;
            break;
            case '6':
            return 6;
            break;
            case '7':
            return 7;
            break;
            case '8':
            return 8;
            break;
            case '9':
            return 9;
            break;
        }
    }
    int leftVal = evaluateIntegerExpression(node->left);
    int rightVal = evaluateIntegerExpression(node->right);
    if(node->data == '*'){
        return leftVal*rightVal;
    }
    if(node->data == '/'){
        return leftVal/rightVal;
    }
    if(node->data =='+'){
        return leftVal+rightVal;
    }
    if(node->data =='-'){
        if(leftVal>rightVal){
            return leftVal-rightVal;
        }
        else{
            return rightVal-leftVal;
            }
    }
    else{
        return 0;
        }
}

void arithmeticExpression::infix(TreeNode* node){
    if (node!=nullptr){
        if(node->data=='+' || node->data =='-'|| node->data=='/' || node->data =='*'){
            cout << '(';
        }
        infix(node->left);
        cout << node->data;
        infix(node->right);
        if(node->data=='+' || node->data =='-'|| node->data=='/' || node->data =='*'){
            cout << ')';
        }
    }
}

void arithmeticExpression::prefix(TreeNode *node){
    if(node!= nullptr){
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix(TreeNode *node) {
    if (node != nullptr) {
        postfix(node -> left);
        postfix(node -> right);
        cout << node -> data;
    }
}

bool arithmeticExpression::isValidIntegerExpression(TreeNode *treeRoot){
    /*if(treeRoot == nullptr){
        throw invalid_argument("expression not valid");
        return false;
    }*/
    if(treeRoot->data >='0' && treeRoot->data<='9'){
        return true;
    }
    else if(treeRoot->data=='+' || treeRoot->data =='-' || treeRoot->data =='/' || treeRoot->data =='*'){
        bool leftChild=isValidIntegerExpression(treeRoot->left);
        bool rightChild = isValidIntegerExpression(treeRoot->right);
        if(leftChild == true && rightChild == true){
        return true;
        }
        else{
            throw invalid_argument("expression not valid");
            return false;
        }
    }
    else{
        throw invalid_argument("expression not valid");
        return false;
    }
}
