/*
Name: Krishna Kant Verma
Roll No: 2211CS19
Computer System Lab - 2
Assignment No: 1
Indian Institute of Technology Patna
*/

// all required header files in this program (for in/out,vector,map,string and Some Basic Algorithms)
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <unordered_map>

// using namespace as standard library
using namespace std;

// creating class (polynomial Blueprint datatype) that stored the coefficient and exponent values
class Polynomial
{
public:
    int coefficient;
    int exponent;
};

// Comparator Function to sort the result in decresing order of exponents
static bool cmp(Polynomial p1, Polynomial p2)
{
    // sort in decresing order according to exponents
    return p1.exponent > p2.exponent;
}

// function that parses the input polynomial is operable format and store it into vector of Polynomial type
void parseParameters(string expression, vector<int> &polynomial1)
{
    int temp = 0;
    // mainting signs of each number
    int sign = 1;

    // iterating through input expression
    for (int i = 0; i < expression.size(); i++)
    {
        // skip the character if "[" "(" "]" " "
        if (expression[i] == '[' or expression[i] == ' ' or expression[i] == '(' or expression[i] == ']')
        {
            continue;
        }
        // tracking negative sign
        else if (expression[i] == '-')
        {
            sign = -1;
        }
        // push results when encounter comma or closing bracket
        else if (expression[i] == ',' or expression[i] == ')')
        {
            temp *= sign;
            polynomial1.push_back(temp);
            // resetting the values again
            sign = 1;
            temp = 0;
        }
        // evaluating interger value in input expression
        else
        {
            temp = temp * 10 + (expression[i] - '0');
        }
    }
}

// function that solves two polynomial equation and give proper result
void solveMultiplication(vector<Polynomial> &p1, vector<Polynomial> &p2, vector<Polynomial> &result)
{
    // map stores exponents and corresponding coefficient value
    unordered_map<int, int> multiplies;

    // iterating over both Polynomial Array to get the result
    for (int i = 0; i < p1.size(); i++)
    {
        for (int j = 0; j < p2.size(); j++)
        {
            multiplies[p1[i].exponent + p2[j].exponent] += (p1[i].coefficient * p2[j].coefficient);
        }
    }
    // storing back the results stored in map to result vector
    for (auto x : multiplies)
    {
        result.push_back({x.second, x.first});
    }
}

// main function
int main()
{
    // initializing two temp Vectors
    vector<int> polynomial1, polynomial2;
    // taking input exrpession 1 in string format
    cout << "Enter Polynomials in Specified Format\n"
            "[(coefficient, exponent)(coefficient, exponent)...]";
    cout << "\nExample: [(8,6)(4,3)(-10,2)]\n";
    string input1;
    cout << "\nEnter Polynomial p1(x)= ";
    getline(cin, input1);
    // taking input expression 2 in string format
    string input2;
    cout << "\nEnter Polynomial p2(x)= ";
    getline(cin, input2);

    // parsing the coefficients and exponents from input expression 1
    parseParameters(input1, polynomial1);
    // parsing the coefficients and exponents from input expression 2
    parseParameters(input2, polynomial2);

    // size of each Polynomial
    // polynomial 1 size
    int n = polynomial1.size() / 2;
    // polynomial 2 size
    int m = polynomial2.size() / 2;

    // vector of Polynomial Type to Store the Input in operable Forms and Store Results in required form
    vector<Polynomial> p1(n);
    vector<Polynomial> p2(m);
    vector<Polynomial> result;

    // index pointer to map temp vectors to Polynomial Vectors
    int j = 0;
    // mapping polynomial 1
    for (int i = 0; i < n; i++)
    {
        p1[i].coefficient = polynomial1[j++];
        p1[i].exponent = polynomial1[j++];
    }
    j = 0;
    // mapping polynomial 2
    for (int i = 0; i < m; i++)
    {
        p2[i].coefficient = polynomial2[j++];
        p2[i].exponent = polynomial2[j++];
    }

    // calling function to multiply two polynomials
    solveMultiplication(p1, p2, result);
    // sorting the results in required format
    sort(result.begin(), result.end(), cmp);

    // printing results
    cout << "\n\nResulting Polynomial P(x)= ";
    cout << "[";
    for (auto x : result)
    {
        cout << "(";
        cout << x.coefficient << "," << x.exponent;
        cout << ")";
    }
    cout << "]";
    cout << endl;
    return 0;
}

// thank you so much