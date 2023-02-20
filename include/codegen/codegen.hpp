#pragma once

#include <parser/parser.hpp>

/*
 * @TODO: 
 *      + think of a better (ligher) way to return data that 
 *          isn't a string (maybe write to file directly)
 *          (it's probably a vector)
 *      + add a prettyfying option (-DPRETTY) to make output
 *          C code formatted
 */

//std::string codegen(const parse_tree& u_data);                 // codegen from parse tree (safer) (doesn't work)
std::string codegen(const std::vector <token_>& u_data); // codegen from token stream (no check at all) (WIP)
