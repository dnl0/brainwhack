#pragma once

#include <parser/parser.hpp>
//#include <lexer/lexer.hpp>

/*
 * @TODO: think of a better (ligher) way to return data that 
 *          isn't a string (maybe write to file directly);
 *        figure out why code generation outputs not working
 *          c code;
 */

/*
std::string codegen(node_tree& u_data); // once i figure out how to 
                                        // make parser work properly
                                        // code gen will be accepting
                                        // node tree as an argument
 */

std::string codegen(const std::vector <token>& u_data);
