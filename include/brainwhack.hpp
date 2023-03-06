#pragma once

#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <codegen/codegen.hpp>
#include <interpreter/interpreter.hpp>

#include <utils/text.hpp>
#include <utils/error_handling.hpp>

struct options_ {
    std::string filename {};
    bool do_codegen {};
    bool print_help {};
    std::string unknown {};
    bool empty {true};
};

options_ parse_options(std::vector <std::string> options);
void print_help();
std::string bf_to_c_filename(std::string& source);
std::string file_to_string(const std::string& filename);
void string_to_c_file(const std::string& source, std::string filename);
