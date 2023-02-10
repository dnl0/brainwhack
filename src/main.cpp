#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

//#include <parser/parser.hpp>
#include <codegen/codegen.hpp>

void print_tree(const std::string& prefix, const node* head, bool isLeft)
{
    if( head != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├ " : "└ " );

        std::cout << head->m_data.m_data << std::endl;

        // enter the next tree level - left and right branch
        print_tree( prefix + (isLeft ? "│ " : "  "), head->m_left, true);
        print_tree( prefix + (isLeft ? "│ " : "  "), head->m_right, false);
    }
}

void print_tree(const node* head)
{
    print_tree("", head, false);    
}

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
        std::cerr << "fatal: file " << argv[1] << "not found\n";
        return -1;
    }

    // lex the file and print token stream
    std::stringstream buffer;
    buffer << ifile.rdbuf();

    // parser (doesn't work correctly)
    // node_tree pt = parse(lex(buffer.str()));
    // print_tree(pt.get_head());

    // codegen
    std::string ccode = codegen(lex(buffer.str()));

    std::string filename = argv[1];
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    std::ofstream ofile {filename};
    if (!ofile) { std::cerr << "fatal: not able to create the output .c file\n"; return -1; }

    ofile << ccode;
}
