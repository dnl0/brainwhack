#pragma once

#include <lexer/lexer.hpp>

namespace main_ {
    enum issue_ {
        none_ = -1,
        no_file_ = 1,
        not_bf_file_,
        more_than_one_file, // @TODO: allow running multiple files
        file_not_found_,
        cant_create_c_file_,
        unknown_options_,
    };

    void process_issue(issue_, std::string s = "");
} // main_

namespace parser_ {
    enum issue_ { 
        none_ = -1, 
        unopened_bracket_ = 1,
        unclosed_bracket_,
    };

    void process_issue(issue_, token_);
} // parser_issue_

namespace interpreter_ {
    enum issue_ {
        none_ = -1,
        unknown_id = 1,
    };

    void process_issue(issue_, token_);
} // interepter_issue_
