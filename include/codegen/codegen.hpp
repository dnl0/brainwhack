#pragma once

#include <parser/parser.hpp>

/*
 * @TODO: think of a better (ligher) way to return data that 
 *          isn't a string (maybe write to file directly);
 */

std::string codegen(node_tree* u_data);                 // codegen from parse (safer)
std::string codegen(const std::vector <token>& u_data); // codegen from lex (no check at all)
