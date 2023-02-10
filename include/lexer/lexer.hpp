/*
 * TODO: explain code with comments where necessary
 */

#pragma once

#include <vector>
#include <string>

// p - pointer, d - data, l - loop
enum type { comment = -1, p_operator, d_operator, io_command, l_punctuator };

struct token {
    char m_data;
    type m_type;
    std::string m_cdata;

    token() = default;
    token(char u_data, type u_type, std::string u_cdata)
        : m_data {u_data}, m_type {u_type}, m_cdata {u_cdata}
    {
    }

    token(const token& other) {
        m_data  = other.m_data;
        m_type  = other.m_type;
        m_cdata = other.m_cdata;
    }
    ~token() = default;
};

token tokenize(const char u_data);
std::vector <token> lex(std::string u_input);
