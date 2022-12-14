// References: Mod 4 slides, mod 3 slides, exam 1 review slides
// https://www.geeksforgeeks.org/practice-questions-height-balancedavl-tree/
#include <iostream>
#include <sstream>
#include "AVLTree.hpp"
using namespace std;

/*  Note:
    1. You will have to comment main() when unit testing your code because catch uses its own main().
    2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int checkNumCommands(string line1)
{
    for (char c : line1)
    {
        if (!isdigit(c))
            return 0;
    }

    int numCommands = stoi(line1);
    return numCommands;
}

bool verifyName(string name)
{
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }

    return true;
}

bool verifyUFID(string ufid)
{
    if (ufid.size() != 8)
        return false;

    for (char c : ufid)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}

bool verifyDigit(string n)
{
    for (char c : n)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    try
    {
        AVLTree t;

        string line;
        getline(cin, line);
        int numCommands = checkNumCommands(line);

        if (numCommands < 1)
            throw exception();

        for (int i = 0; i < numCommands; i++)
        {
            getline(cin, line);
            istringstream in(line);

            string command;
            getline(in, command, ' ');

            if (command == "insert")
            {
                string name, ufid, buffer;

                getline(in, buffer, '\"');
                getline(in, name, '\"');
                getline(in, buffer, ' ');
                getline(in, ufid, '\n');

                if (!(verifyName(name) && verifyUFID(ufid)))
                {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // Call insert function here 
                t.Insert(name, ufid);
            }
            else if (command == "remove")
            {
                string ufid;
                getline(in, ufid);

                if (!verifyUFID(ufid))
                {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // Call remove function here
                t.Remove(ufid);
            }
            else if (command == "search")
            {
                string name, ufid, buffer;

                getline(in, buffer, '\n');

                if (buffer[0] == '\"') // If command is search NAME
                {
                    name = buffer.substr(1, buffer.size() - 2);

                    if (!verifyName(name))
                    {
                        cout << "unsuccessful" << endl;
                        continue;
                    }

                    // Call search NAME function here
                    t.SearchName(name);
                }
                else if (isdigit(buffer[0])) // If command is search ID
                {
                    ufid = buffer;

                    if (!verifyUFID(ufid))
                    {
                        cout << "unsuccessful" << endl;
                        continue;
                    }

                    // Call search ID function here
                    t.SearchID(ufid);
                }
                else
                {
                    cout << "unsuccessful" << endl;
                    continue;
                }
            }
            else if (command == "printInorder")
            {
                // Call PrintInorder function here
                t.PrintInorder();
            }
            else if (command == "printPreorder")
            {
                // Call PrintPreorder function here
                t.PrintPreorder();
            }
            else if (command == "printPostorder")
            {
                // Call PrintPostorder function here
                t.PrintPostorder();
            }
            else if (command == "printLevelCount")
            {
                // Call PrintLevelCount function here
                t.PrintlevelCount();
            }
            else if (command == "removeInorder")
            {
                string n;
                getline(in, n);

                if (!verifyDigit(n))
                {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                int n_ = stoi(n);
                // Call RemoveInorder function here
                t.RemoveInorder(n_);
            }
            else
                // If misspelled command or typo otherwise
                cout << "unsuccessful" << endl;
        }

    }
    catch (const std::exception& e)
    {
        std::cerr << "please enter a valid series of commands" << endl;
    }

    return 0;
}
