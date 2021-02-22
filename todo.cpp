// Coded By Vishal Mourya
// This is a simple TODO Command line application made by me in C++
// This todo application uses files to store you todo list and updating,etc.

#include<bits/stdc++.h>
// our todo list can contain maximum of MAX entries
#define MAX 100001

using namespace std;

void Display(){
    // Create a text string, which is used to output the text file
    string myText;

    // Read from the text file
    ifstream MyReadFile("todo1.txt");
    int cnt = 1;

    vector<string> vs; // this will store all the data from file to alter

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        vs.push_back( myText );
        cnt++;
    }

    // juts manipulating data to get proper formatting
    reverse( vs.begin() , vs.end() );
    int per = 0;

    for( int i = 0 ; i < vs.size() ; i++ ) {
        int tmp1 = vs[i].length();
        if( vs[i][ tmp1 - 1 ] == '0' ) per++;
    }

    for( int i = 0 ; i < vs.size() ; i++ ) {
        int tmp1 = vs[i].length();

        if( vs[i][ tmp1 - 1 ] == '0' )
            cout << "[" << per-- << "]" << " " << vs[i].substr(0,tmp1-1) << "\n";
    }
    if( cnt == 0 ) cout << "Todo list is Empty!!";
    // Close the file
    MyReadFile.close(); 
}

void Append(string task){
    // using files to store out todo
    freopen("todo1.txt", "a", stdout); 
    cout << task << 0 << "\n";
}

void displayUsage() {
    // just printing the menu
    string str = "Usage :-\n"
    "$ ./todo add \"todo item\"  # Add a new todo\n"
    "$ ./todo ls               # Show remaining todos\n"
    "$ ./todo del NUMBER       # Delete a todo\n"
    "$ ./todo done NUMBER      # Complete a todo\n"
    "$ ./todo help             # Show usage\n"
    "$ ./todo report           # Statistics";
    
    cout << str << "\n";
}

void addToTodo(string task) {
    cout << "Added todo: \"" << task << "\"" << "\n";
    Append(task);
}

void displayList() {
    Display();
}

void delFromTodo(string taskNumber) {
    freopen("todo1.txt" , "r" , stdin);
    int num = stoi(taskNumber);
    
    vector<string> vs;
    string s;
    // read till the input is present in file
    while( getline(cin , s) ) {
        vs.push_back(s);
    }

    // if the given number exceeds the size of our todo list just print the error messgae
    if( num > vs.size() ) {
        cout << "Error: Missing NUMBER for deleting todo.\n";
    }
    else {
        cout << "Deleted todo #" << num << "\n";
        // delete the selected task from todo list
        vs.erase( vs.begin() + num - 1 );
    }
    

    freopen("todo1.txt", "w" , stdout);
    for( int i = 0 ; i < vs.size() ; i++ ) cout << vs[i] << "\n";
}

void doneFromTodo( string taskNumber ) {

    int num = stoi(taskNumber);

    vector<string> vs;
    // marking todo as done
    cout << "Marked todo #" << num << " as done.\n";

    freopen("todo1.txt", "r", stdin); 
    string s;
    while( getline(cin,s) ) {
        vs.push_back(s);
    }
    vs[ num - 1 ][ vs[num-1].length() - 1 ] = '1';

    freopen("todo1.txt", "w", stdout); 
    for( int i = 0 ; i < vs.size() ; i++ ) cout << vs[i] << "\n";    
}

void displayReport() {
    
    int cntPending = 0 , cntCompleted = 0;
    string myText;

    // Read from the text file
    ifstream MyReadFile("todo1.txt");
    int cnt = 1;
    
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
       int slen = myText.length();
       if( myText[ slen - 1] == '1' ) cntCompleted++;
       else cntPending++;
    }

    cout << "2020-12-22 ";
    cout << "Pending : " << cntPending << " ";
    cout << "Completed : " << cntCompleted << "\n";
}

int main( int argLength , char** args ) {
    
    if( argLength == 1 ) {
        // if length is 1, then diaply menu
        displayUsage();
    }
    else if( argLength == 2 ) {
        string opt = args[1];
        if( opt == "help"  ) {
                displayUsage();
        }
        else if( opt == "report" ) {
                displayReport();
        }
        else if( opt == "ls" ) {
                displayList();
        }
        else {
                cout << "Error: Missing todo string. Nothing added!\n";
        }
    }
    else if( argLength == 3 ) {
        string arg1 = args[1];
        string arg2 = args[2];

        if( arg1 == "add" ) {
            addToTodo(arg2); 
        }
        else if( arg1 == "del" ) {
            delFromTodo(arg2); 
        }
        else if( arg1 == "done" ) {
            doneFromTodo(arg2); 
        }
        else {
            cout << "Error: Missing todo string. Nothing added!\n";
        }
    }
    else {
        cout << "Error: Missing NUMBER for deleting todo.\n";
    }

}