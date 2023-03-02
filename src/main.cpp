#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <brainwhack.hpp>

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
            main_::process_issue(main_::no_file_);
        }
        int size = strlen(argv[1]);
        if (argv[1][size-3] != '.' ||
            argv[1][size-2] != 'b' ||
            argv[1][size-1] != 'f') 
        {
            main_::process_issue(main_::not_bf_file_);
        }
    }
    std::ifstream ifile {argv[1], ifile.in };
    if (!ifile) {
        main_::process_issue(main_::file_not_found_, argv[1]);
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
        main_::process_issue(main_::cant_create_c_file);
    }
    ofile << ccode;
    ofile.close();
#endif // TEST_CODEGEN

#ifdef TEST_INTERPRETER
    interpret(parse(lex(buffer)));
#endif // TEST_INTERPRETER

#endif // DEBUG
}
