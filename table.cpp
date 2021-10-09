//
//  table.cpp
//  Created by Dharma on 6/4/21.
//
#include <iostream>
#include <string>
#include <vector>
#include "table.hpp"
#include <set>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>



using namespace std;
/*/
struct Record(string keyword, vector<string> current){
    string keyword = keyword;
}
*/


bool stringToDouble(std::string s, double& d)
    {
        char* end;
        d = std::strtof(s.c_str(), &end);
        return end == s.c_str() + s.size()  &&  !s.empty();
    }

bool computeNumer (string recordVal, string oper, string comparison){
// already lowercase -> go through and do comparison
    
// turn the operator in character form
    char numOperFirst = oper.at(0);
    char numOperSecond;
    if (oper.length() == 2)
        numOperSecond = oper.at(1);
    else
        numOperSecond = '9';
    
    // turn the recordVal and comparison into doubles
    double DrecordVal = 0;
    stringToDouble(recordVal, DrecordVal);
    
    
    double Dcomparison = 0;
    stringToDouble(comparison, Dcomparison);
    
    
    // do the actual comparison and respond true or false
switch(numOperFirst){
        case 'l':
            if (numOperSecond == 'e'){
                if (DrecordVal <= Dcomparison)
                    return true;
                else    // does not mean the query
                    return false;
            }
            else    {     // only < for operator
                if (DrecordVal < Dcomparison)
                    return true;
                else
                    return false;
            }
        case 'g':
            if (numOperSecond == 'e'){
                if (DrecordVal >= Dcomparison)
                    return true;
                else    // does not mean the query
                    return false;
            }
            else    {     // only > for operator
                if (DrecordVal > Dcomparison)
                    return true;
                else
                    return false;
            }
        case 'n':
            if (numOperSecond == 'e'){
                if (DrecordVal != Dcomparison)
                    return true;
                else
                    return false;
                }
        
        case 'e':
            if (numOperSecond == 'q'){
                if (DrecordVal == Dcomparison)
                    return true;
                else
                    return false;
                }
}
    
    return false;
    
}

// compute if it's a string
bool compute (string recordVal, string oper, string comparison) {
    char firstOpDig = oper.at(0);
    char secondOpDig;
   if (oper.length() == 2)
        secondOpDig = oper.at(1);
    else
        secondOpDig = '9';
    
switch(firstOpDig){
    case '<':
        if (secondOpDig == '='){
            if (recordVal <= comparison)
                return true;
            else    // does not mean the query
                return false;
        }
        else    {     // only < for operator
            if (recordVal < comparison)
                return true;
            else
                return false;
        }
    case '>':
        if (secondOpDig == '='){
            if (recordVal >= comparison)
                return true;
            else    // does not mean the query
                return false;
        }
        else    {     // only > for operator
            if (recordVal > comparison)
                return true;
            else
                return false;
        }
    case '=':
        if (secondOpDig == '='){
            if (recordVal == comparison)
                return true;
            else    // does not mean the query
                return false;
        }
        else    {     // only = for operator
            if (recordVal == comparison)
                return true;
            else
                return false;
        }
    case '!':
        if (secondOpDig == '='){
            if (recordVal != comparison)
                return true;
            else
                return false;
        }
    }
    return false;
}



bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}

Table:: Table(std::string keyColumn, const std::vector<std::string>& columns) {
    
    for (int i = 0; i < columns.size(); i++){
        columnNames.push_back(columns[i]);
    }
    // find index of the keycol
    for (int j = 0; j < columns.size(); j++){
        if (columns[j] == keyColumn)
            keyColIndex = j;
        else
            continue;
    }
    // initialize name of keyColumn, size of column, root node
    keyCol = keyColumn;
    numCol = columns.size();
    root = nullptr;
}


// check for duplicate strings, empty strings, or key column is not any
// insert into a set if not empty
bool Table::good() const {
    set<string> acceptedColumns;
    bool hasKeyValue = false;;
    for(int i = 0; i < columnNames.size(); i++){
        if (columnNames[i] != "")
            acceptedColumns.insert(columnNames[i]);
        if (columnNames[i] == keyCol)
            hasKeyValue = true;
    }
    
    if (hasKeyValue == true && acceptedColumns.size() == columnNames.size()){
       // cout << "true" << endl;
        return true;
    }
    else{
      //  cout << "damn false" << endl;
        return false;
    }
}




/*/ Insert:
 
 - each time we insert a new string it will be a new node
 - find out which column is the key column
 - make that how we sort it
 - 
*/

bool Table::insert(const string &recordString){
    if (this->good() == false)
        return false;
    // put it into a vector
    // create a new node
    // attach the node to the root if the root is a nullptr
    // else go through the tree by the keycolumn
    
    vector<string> temp(numCol);
    StringParser parser(recordString);
    string a;
    
    for (int k = 0; k < numCol; k++){
    if (!parser.getNextField(a))
        return false;
    else {
        temp[k] = a;
        }
    }

 
    
    // create a new node and insert it into the tree
    Node* currNode = new Node;
    for(int i = 0; i < temp.size(); i++){
        currNode->insert(temp[i]);
    }
    currNode->keyValue = temp[keyColIndex];
    // empty tree
    Node* tempToPass = root;
    placeNode(*currNode, currNode->keyValue, tempToPass);
    return true;
}

// correctly place the ndoe in the tree
void Table::placeNode(Node &currNode, string keyValue, Node* temp){
    if (root == nullptr){
        root = &currNode;
    }
    else {
        if (keyValue > temp->keyValue && (temp->right == nullptr)){
            temp->right = &currNode;
            currNode.parent = temp;
            return;
        }
        if(keyValue <= temp->keyValue && (temp->left == nullptr)){
            temp->left = &currNode;
            currNode.parent = temp;
            return;
        }
        if (keyValue > temp->keyValue)
            placeNode(currNode, keyValue, temp->right);
        if (keyValue <= temp->keyValue)
            placeNode(currNode, keyValue, temp->left);
    }
}

// recursive function to find the value
void Table ::findHelper(string key, vector<vector<string>>& records, Node* curr) const{
    if (curr->keyValue == key) {
        records.push_back(curr->colValues);
        
        if(curr->left == nullptr)
            return;
        else 
        findHelper(key, records, curr->left);
    }
    if (key > curr->keyValue && (curr->right == nullptr))
        return;
    if (key < curr->keyValue && (curr->left == nullptr))
        return;
    if(key > curr->keyValue)
        findHelper(key, records, curr->right);
    if (key < curr->keyValue)
        findHelper(key,records,curr->left);
}

void Table::find(string key, vector<vector<string>>& records) const {
    records.clear();
    Node* currNode = root;
    if (root == nullptr)
        return;
    
    
    // traverse through the tree and if the the keyword is equal push it
    else {
        findHelper(key, records, currNode);
    }
}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const {
    // find which index the query is
    // go through each value and if it satisfies that requirement -> add  it to the vector if it does
    // if it's a bad nut -> immediately add one to the end

    // go through and check if operator is a numeric oeprator
            // both comparison and query and numeric and valid and not nullptr
    records.clear();
    
    
    string qColString = query;
    string oper;
    string comparison;
    
    // check if the operator is valid
    // check if operator is numeric, the others are numeric
    if (!divideQuery(query, qColString, oper, comparison)){
        records.clear();
        return -1;              // this is bc the operator is not valid
    }
    
    // go thru the tree and look at the key col and comparison
    // add each record that is true
    
    int qColumn = findQueryIndex(qColString);
    
    if (qColumn == -10) {
        records.clear();
        return -1;
    }
    
    // traverse tree and correctly place in records
    Node* curr = root;
    int returnValue = 0;
    selectHelper(qColumn, oper, comparison, records, curr, returnValue);
    
    return returnValue;
}




bool Table::divideQuery (std::string query, std::string &qColString, std::string &oper, std::string &comparison) const{
    
    // get the keycolumn
    StringParser findquery(query);
    findquery.getNextField(query);
    qColString = query;
    
    // get the oper
    findquery.getNextField(query);
    oper = query;
    
    // check if oper is valid
    const vector<string> correctOperators = {"<", "<=", ">", ">=", "!=", "==", "=", "lt", "le", "gt","ge","ne", "eq" } ;
    for(int i = 0; i < oper.size(); i++){
        oper[i] = tolower(oper[i]);
    }
    bool okayOperator = false;
    
    for (int j = 0; j < correctOperators.size(); j++){
        if (correctOperators[j] == oper){
            okayOperator = true;
            break;
        }
        else {
            continue;
        }
    }
            if (okayOperator == false)
                return false;
    
        // get the comparison string
        findquery.getNextField(query);
        comparison = query;
    
    // see if there is more left in query -> if so, it's too long
    if (findquery.getNextField(query) == true)
        return false;
        // check that if operator is numeric so are comparison and colString
    int qColIndex = findQueryIndex(qColString);

    
    double qColDouble = 0;
    double comparisonDouble = 0;
    if(isNumericOper(oper)){
        if (isValidNumeric(this->root->colValues[qColIndex], qColDouble, comparison, comparisonDouble) == false) {
            // check the next value just in case
            if (root->left != nullptr){
                if(isValidNumeric(this->root->left->colValues[qColIndex], qColDouble, comparison, comparisonDouble) == false)
                    return false;
                }
            if(root->right != nullptr){
                if(isValidNumeric(this->root->right->colValues[qColIndex], qColDouble, comparison, comparisonDouble) == false)
                    return false;
            }
        }
    }
        return true;
}
    
    

bool Table::isValidNumeric(string qColString, double qColDouble, string comparison, double comparisonDouble) const {
    //if (stringToDouble(qColString, qColDouble) == false)
      //  return false;
    if(stringToDouble(comparison, comparisonDouble) == false)
        return false;
    // both the comparison and colstring are valid numeric
    return true;
}


bool Table::isNumericOper(string oper) const{
    vector<string> numericOper = {"lt", "le","gt", "ge","ne", "eq"};
    for (int o = 0; o < numericOper.size(); o++){
        if (numericOper[o] == oper)
            return true;
    }
    return false;
}

void Table::selectHelper(int qColumn, std::string oper, std::string comparison, std::vector<std::vector<std::string>>& records, Node* curr, int& returnValue) const {
    
    // see if the operator is numeric
    // if it is then convert qcolstring & comparison to doubles
    
    // go through the root and if nullptr return 0;
    // else go through and return right and return left
    
    // go through and do the compute operator with each value in the tree
    // if its true then push that value onto records
    // if its false then move to the next one
    if (curr == nullptr)
        return;
    
    else if (!isNumericOper(oper))
    {
        if (compute(curr->colValues[qColumn], oper, comparison) == true) {
            records.push_back(curr->colValues);
            
            selectHelper(qColumn, oper, comparison, records, curr->left, returnValue);
            
            selectHelper(qColumn, oper, comparison, records, curr->right, returnValue);
        }
        else{
        
            selectHelper(qColumn, oper, comparison, records, curr->left, returnValue);
            
            selectHelper(qColumn, oper, comparison, records, curr->right, returnValue);
        }
    }
    else
        if (computeNumer(curr->colValues[qColumn], oper, comparison) == true) {
            double tempDouble2 = 0;
            // check if it was a valid operation before inputting
            if (!(stringToDouble(curr->colValues[qColumn], tempDouble2)))
                returnValue++;
            else
                records.push_back(curr->colValues);
            
            
            
            selectHelper(qColumn, oper, comparison, records, curr->left, returnValue);
            
            selectHelper(qColumn, oper, comparison, records, curr->right, returnValue);
        }
        else{
            double tempDouble = 0;
            if (!(stringToDouble(curr->colValues[qColumn], tempDouble)))
                returnValue++;
            
            selectHelper(qColumn, oper, comparison, records, curr->left, returnValue);
            
            selectHelper(qColumn, oper, comparison, records, curr->right, returnValue);
        }
    }
        

int Table::findQueryIndex(string query) const{
    for (int i = 0; i < numCol; i++){
        if (query == columnNames[i])
            return i;
    }
    return -10;             // means the query is not a column name
}

void Table::deleteTree(Node* root){
    if (root == nullptr)
        return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    delete root;
}


Table :: ~Table (){
    deleteTree(root);
}


/*/
 psuedocode:
 
 I have a node that has a pointer to the parent as well as the two children
 -> We will determine the order of the tree alphabetically by the string keycolumn
 
 
 
 
 
 */
 
 
