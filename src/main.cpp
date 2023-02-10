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
    if (argv[1] == NULL) {
        std::cerr << "specify a file\n";
        return -1;
    }
    std::ifstream ifile {argv[1], ifile.in };
    if (!ifile) {
        std::cerr << "file " << argv[1] << "not found\n";
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
    std::ofstream ofile {"brainwack.c"};
    if (!ofile) {
        std::cerr << "not able to create the output file\n";
    }
    ofile << ccode;
}
