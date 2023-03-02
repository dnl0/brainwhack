#pragma once

#include <lexer/lexer.hpp>

namespace main_ {
    enum issue_ {
        none_ = -1,
        no_file_,
        not_bf_file_,
        file_not_found_,
        cant_create_c_file,
    };

    void process_issue(issue_, std::string s = "");
} // main_

namespace parser_ {
    enum issue_ { 
        none_ = -1, 
        unopened_bracket_, 
        unclosed_bracket_,
    };

    void process_issue(issue_, token_);
} // parser_issue_

namespace interpreter_ {
    enum issue_ {
        none_ = -1,
        unknown_id,
    };

    void process_issue(issue_, token_);
} // interepter_issue_
