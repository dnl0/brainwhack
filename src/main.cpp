#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <brainwhack.hpp>
#include <utils/text.hpp>

#ifdef DEBUG_ALL

#define DEBUG
#define TEST_LEXER
#define TEST_PARSER
#define TEST_CODEGEN

#endif // DEBUG_ALL

std::string bf_to_c_filename(const std::string& source)
{
    std::string filename = source;
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    return filename;
}

#ifdef DEBUG

void print_vector(const std::vector <token_>&& vec)
{
    for (auto& x: vec) {
        if (x.type != comment_)
            std::cout << x.data << " ";
    }
    std::cout << "\n";
}

void print_list(std::list <std::shared_ptr <statement_>> l)
{
    for (auto& x: l) {
        std::cout << ((*x).id) << " ";
        if ((*x).statement_type == ctrl_stmt_) {
            print_list(std::static_pointer_cast <control_statement_> (x)->body );
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
    using namespace text;

    {
        if (argv[1] == NULL) {
            std::cerr << red(bold("\nfatal")) << ": specify a file\n";
            exit(EXIT_FAILURE);
        }
        int size = strlen(argv[1]);
        if (argv[1][size-3] != '.' ||
            argv[1][size-2] != 'b' ||
            argv[1][size-1] != 'f') {
            std::cerr << red(bold("\nfatal")) << ": isn't a .bf file\n";
            exit(EXIT_FAILURE);
        }
    }
    std::ifstream ifile {argv[1], ifile.in };
    if (!ifile) {
        std::cerr << red(bold("\nfatal")) << ": file " << argv[1] << " not found\n";
        return -1;
    }

    std::stringstream stream_buffer;
    stream_buffer << ifile.rdbuf();
    std::string buffer = stream_buffer.str(); 
    ifile.close();

#ifdef DEBUG

#ifdef TEST_LEXER
    std::cout << "log: lex stream:\n";
    print_vector(lex(buffer));
#endif // TEST_LEXER

#ifdef TEST_PARSER
    auto lexed  = lex(buffer);
    std::cout << italic("log") << ": lexer has lexed\n";
    auto parsed = parse(lexed);
    std::cout << italic("log") << ": parser has parsed\n\n";

    std::cout << "log: de-parsed tree:\n";
    print_tree(parsed);
#endif // TEST_PARSER

#ifdef TEST_CODEGEN
    std::string ccode = codegen(parse(lex(buffer)));

    std::ofstream ofile {bf_to_c_filename(argv[1])};
    if (!ofile) {
        std::cerr << red(bold("\nfatal")) << ": not able to create the output .c file\n"; 
        exit(EXIT_FAILURE);
    }
    ofile << ccode;
    ofile.close();
#endif // TEST_CODEGEN

#ifdef TEST_INTERPRETER
    interpret(parse(lex(buffer)));
#endif // TEST_INTERPRETER

#endif // DEBUG
}
