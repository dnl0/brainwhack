#pragma once

#include <lexer/lexer.hpp>

#include <vector>

#include "stmt.hpp"

class parse_tree {
    private:
        std::vector <std::shared_ptr <statement_>> data_ {}; // shared_ptr to make casting easier
    public:
        parse_tree() = default;

        const std::vector <std::shared_ptr <statement_>>& data()        { return data_; };
        std::shared_ptr <statement_> back() const                       { return data_.back(); }
        std::vector <std::shared_ptr <statement_>>::iterator begin()    { return data_.begin(); }
        std::vector <std::shared_ptr <statement_>>::iterator end()      { return data_.end(); }

        friend parse_tree parse(const std::vector <token_> data);
};

parse_tree parse(const std::vector <token_> data);
