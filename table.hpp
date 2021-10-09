//
//  table.hpp
//  Created by Dharma on 6/4/21.
//

#ifndef table_hpp
#define table_hpp

#include <string>
#include <vector>
#include <stdio.h>
#include <list>

const int ISNUMERIC = 1;
const int ISSTRING = 0;

struct Node
{
    public:
    Node* parent;
    Node* left;
    Node* right;
    std::string keyValue;
    
    Node() {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        numCol = 0;
    }
    
    void insert(std::string value){
        colValues.push_back(value);
        numCol++;
    }
    
    int size () {
        return numCol;
    }
    
    std::vector <std::string> colValues;
    int numCol;
} ;



class StringParser
{
  public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};

class Table
{
  public:
    Table(std::string keyColumn, const std::vector<std::string>& columns);
    ~Table();
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;

      // We prevent a Table object from being copied or assigned by
      // making the copy constructor and assignment operator unavailable.
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;
    
  private:
    std::vector<std::string> columnNames;
    Node* root;
    int keyColIndex;
    std::string keyCol;
    unsigned long numCol;
    void findHelper(std::string key, std::vector<std::vector<std::string>>& records, Node* curr) const;
    void placeNode(Node &currNode, std::string keyValue, Node* temp);
    int findQueryIndex(std::string query) const;
    void selectHelper(int qColumn, std::string oper, std::string comparison, std::vector<std::vector<std::string>>& records, Node* curr, int& returnValue) const;
    bool divideQuery(std::string query, std::string& qColString, std::string& oper, std::string& comparison) const;
    bool isNumericOper(std::string oper) const;
    bool isValidNumeric(std::string qColString, double qColDouble, std::string comparison, double comparisonDouble) const;
    void deleteTree(Node* root);
    
} ;


#endif /* table_hpp */
