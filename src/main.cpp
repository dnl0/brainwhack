/*
 * @TODO:
 *      + use as much std:: as possible, so far
 *           i'm basically writing C-with-classes
 *           code more rather than C++, which is
 *           counter-productive, and also requires
 *           a lot of unnecessary boilerplate code
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <brainwhack.hpp>

/*void print_vector(const std::vector <l_token>&& vec)
{
    for (auto& x: vec) {
        std::cout << x.m_data << " ";
    }
    std::cout << "\n";
}*/

/*void print_tree(const std::string& prefix, const node* head, bool isLeft)
{
    if( head != nullptr ) {
        std::cout << prefix;
        std::cout << (isLeft ? "├ " : "└ " );
        std::cout << head->m_data.m_data << std::endl;
        print_tree( prefix + (isLeft ? "│ " : "  "), head->m_left, true);
        print_tree( prefix + (isLeft ? "│ " : "  "), head->m_right, false);
    }
}*/

/*void print_tree(const p_abstract_syntax_tree tree)
{
    //print_tree("", tree->get_head(), false);    
}*/

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

    /*
     * lexer
     */

#ifdef DEBUG
    // print_vector(lex(buffer.str()));
#endif

#ifdef TEST_PARSER
    /*
     * parser (needs rework)
     */

    parse(lex(buffer.str()));
#endif

#ifdef DEBUG
    // print_tree(pt->get_head());
#endif

    /* 
     * codegen
     */

    // just do a syntax check
    //print_tree(parse(lex(buffer.str())));

    // works okay with vectors
    std::string ccode = codegen(lex(buffer.str()));

    // doesn't work with parser :(
    // std::string ccode = codegen(parse(lex(buffer.str())));

    /* 
     * copy result to file
     */

    // move this to header probably
    std::string filename = argv[1];
    filename[filename.size()-2] = 'c';  // <name>.bf -> <name>.cf
    filename.pop_back();                // <name>.cf -> <name>.c
    std::ofstream ofile {filename};
    if (!ofile) { std::cerr << "fatal: not able to create the output .c file\n"; return -1; }

    ofile << ccode;
}
