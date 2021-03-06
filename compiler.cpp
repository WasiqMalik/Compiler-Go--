// 17L-4125 Hamza Murad
// 17L-6315 Muhammad Wasiq

#include <iostream>
#include <streambuf>
#include <fstream>
#include <string>
#include "lexer.h"
#include "translator.h"
#include "VM.h"

using namespace std;

int main()
{
    string file_path;
    cout << "Please Enter file path for Go-- Source file." << endl;
    cin >> file_path;

    if (file_path.find(string(".go")) == string::npos)
    {
        cout << "Please provide path to a go source file." << endl;
        return 1;
    }

    ifstream file(file_path);

    if (!file.is_open())
    {
        cout << "File open() failed." << endl;
        cout << "Exiting ... " << endl;
        return 1;
    }

    // store file in memory as a string
    string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Token::file_begin = Token::file_iter = str.begin();
    Token::file_end = str.end();

    file.close();

    cout << "Compiling ..." << endl;

    // start lexer
    Token::look = next_token(Token::file_iter, Token::file_end);

    // generate TAC and machine-code
    intialise_opcodes();
    Translator();

    // save output to files
    write_symbol_table();
    write_TAC();
    write_quads();

    cout << "-------------MACHINE CODE---------------"<< endl;
    for (int i = 0 ; i < quad.size(); i++)
        cout<< i + 1 << ") " << get<0>(quad[i]) << " " << get<1>(quad[i]) << " " << get<2>(quad[i]) << " " << get<3>(quad[i]) <<endl;


    // verify if complete file has been parsed
    if (Token::file_iter != Token::file_end)
    {
        cout << "Compiling Unsuccessful." << endl;
        return 1;
    }

    cout << "Compiling Successful." << endl;

    cout<<"[VM] executing code ..." <<endl;

    execute_machine_code(quad, symbols);

    cout<<"[VM] exiting ..." <<endl;

    return 0;
}