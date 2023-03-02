#include <utils/error_handling.hpp>
#include <utils/text.hpp>

#include <iostream>

namespace main_ {
    void process_issue(issue_ reason, std::string s)
    {
        using namespace text;

        switch (reason) {
            case no_file_:
                std::cerr << bold("\nfatal") << ": specify a file\n";
                exit(EXIT_FAILURE);
            case not_bf_file_:
                std::cerr << bold("\nfatal") << ": isn't a .bf file\n";
                exit(EXIT_FAILURE);
            case file_not_found_:
                std::cerr << bold("\nfatal") << ": file " << s << " not found\n";
                exit(EXIT_FAILURE);
            case cant_create_c_file:
                std::cerr << bold("\nfatal") << ": not able to create the output .c file\n"; 
                exit(EXIT_FAILURE);
            default: break;
        }
    }
} // main_


namespace parser_ {
    void process_issue(issue_ reason, token_ bad_apple)
    {
        using namespace text;

        switch (reason) {
            case unopened_bracket_:
                std::cerr << bold("\nfatal") << ": closing bracket at "
                    << bad_apple.line << ":" << bad_apple.column <<
                    " doesn't correspond to any opening bracket\n";
                exit(EXIT_FAILURE);
                break;
            case unclosed_bracket_:
                std::cerr << bold("\nfatal") << ": bracket at "
                    << bad_apple.line << ":" << bad_apple.column <<
                    " is not closed\n";
                exit(EXIT_FAILURE);
                break;
            default: break;
        }

    }
} // parser_issue_
