#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <brainwhack.hpp>

#ifdef DEBUG_ALL

#define DEBUG
#define TEST_LEXER
#define TEST_PARSER
#define TEST_CODEGEN

#endif // DEBUG_ALL

#ifdef DEBUG

void print_vector(const std::vector <token_>&& vec)
{
    for (auto& x: vec) {
        if (x.type != comment_)
            std::cout << x.data << " ";
    }
    std::cout << "\n";
}

void print_list(std::list <statement_*> l)
{
    for (auto& x: l) {
        std::cout << ((*x).id) << " ";
        if ((*x).statement_type == ctrl_stmt_) {
            print_list( static_cast <control_statement_*> (x)->body );
        }
    }
}

void print_tree(parse_tree& pt)
{
    print_list(pt.data());

    std::cout << "\n";
}

#endif // DEBUG

auto main(int argc, char** argv) -> int {
    {
        if (argv[1] == NULL) {
            std::cerr << "fatal: specify a file\n";
            return -1;
        }
        int size = strlen(argv[1]);
        if (argv[1][size-3] != '.' ||
            argv[1][size-2] != 'b' ||
            argv[1][size-1] != 'f') {
            std::cerr << "fatal: isn't a .bf file\n";
            return -1;
        }
    }
    std::ifstream ifile {argv[1], ifile.in };
    if (!ifile) {
        std::cerr << "fatal: file " << argv[1] << " not found\n";
        return -1;
    }

    std::stringstream stream_buffer;
    stream_buffer << ifile.rdbuf();
    std::string buffer = stream_buffer.str(); 
    ifile.close();

#ifdef DEBUG

#ifdef TEST_LEXER
    std::cout << "log: lex stream:\n";
    print_vector( lex(buffer) );
#endif // TEST_LEXER

#ifdef TEST_PARSER
    auto lexed  = lex(buffer);
    std::cout << "log: lexer has lexed\n";
    auto parsed = parse(lexed);
    std::cout << "log: parser has parsed\n\n";

    std::cout << "log: de-parsed tree:\n";
    print_tree(parsed);
#endif // TEST_PARSER

#ifdef TEST_CODEGEN
    std::string ccode = codegen(parse(lex(buffer)));

    // @TODO: move this to header probably
    std::string filename = argv[1];
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    std::ofstream ofile {filename};
    if (!ofile) { std::cerr << "fatal: not able to create the output .c file\n"; return -1; }

    ofile << ccode;
    ofile.close();
#endif // TEST_CODEGEN

#ifdef TEST_INTERPRETER
    interpret(parse(lex(buffer)));
#endif // TEST_INTERPRETER

#endif // DEBUG
}
