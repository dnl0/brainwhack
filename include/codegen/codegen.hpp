#pragma once

#include <parser/parser.hpp>
//#include <lexer/lexer.hpp>

/*
 * @TODO: think of a better (ligher) way to return data that 
 *        isn't a string (maybe write to file directly)
 */

/*
std::string codegen(node_tree& u_data); // once i figure out how to 
                                        // make parser work properly
                                        // code gen has to accept
                                        // node tree as an argument
 */

std::string codegen(const std::vector <token>& u_data);
