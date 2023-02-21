/*
 * @TODO:
 *      + parser
 *      + C codegen from parser
 *      + interpreter
 */
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

#ifdef TEST_LEXER
void print_vector(const std::vector <token_>&& vec)
{
    for (auto& x: vec) {
        std::cout << x.data << " ";
    }
    std::cout << "\n";
}
#endif // TEST_LEXER 

#ifdef TEST_PARSER
void print_tree(parse_tree& pt)
{
    for (auto it = pt.begin(), end = pt.end(); it != end; ++it) {
        std::cout << (*it)->symbol << " ";
        auto in = *it;
        while (in->next) {
            std::cout << in->next->symbol << " ";
            in = in->next;
        }
    }
    std::cout << "\n";
}
#endif // TEST_PARSER

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

    std::stringstream buffer;
    buffer << ifile.rdbuf();
    ifile.close();

#ifdef DEBUG

#ifdef TEST_LEXER
    print_vector( lex(buffer.str()) );
#endif // TEST_LEXER

#ifdef TEST_PARSER

    auto lexed  = lex(buffer.str());
    std::cout << "lexer has lexed\n";
    auto parsed = parse(lexed);
    std::cout << "parser has parsed\n";

    print_tree(parsed);
#endif // TEST_PARSER

#ifdef TEST_CODEGEN
    std::string ccode = codegen(lex(buffer.str()));

    // @TODO: move this to header probably
    std::string filename = argv[1];
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    std::ofstream ofile {filename};
    if (!ofile) { std::cerr << "fatal: not able to create the output .c file\n"; return -1; }

    ofile << ccode;
    ofile.close();
#endif // TEST_CODEGEN

#endif // DEBUG
}
