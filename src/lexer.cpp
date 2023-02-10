#include <lexer/lexer.hpp>

#include <iostream>

token tokenize(const char u_data)
{
    token result;

    switch (u_data) {
        case '>':
            result.m_cdata = "++ptr;";
            result.m_type = p_operator;
            break;
        case '<':
            result.m_cdata = "--ptr;";
            result.m_type = p_operator;
            break;
        case '+':
            result.m_cdata = "++*ptr;";
            result.m_type = d_operator;
            break;
        case '-':
            result.m_cdata = "--*ptr;";
            result.m_type = d_operator;
            break;
        case '.':
            result.m_cdata = "putchar(*ptr);";
            result.m_type = io_command;
            break;
        case ',':
            result.m_cdata = "*ptr = getchar();";
            result.m_type = io_command;
            break;
        case '[':
            result.m_cdata = "while(*ptr != 0){";
            result.m_type = l_punctuator;
            break;
        case ']':
            result.m_cdata = "}";
            result.m_type = l_punctuator;
            break;
        default:
            result.m_cdata = "\0";
            result.m_type = comment;
            result.m_data = '\0';
            return result;
    }

    result.m_data = u_data;
    return result;
}

std::vector <token> lex(std::string u_input)
{
    std::vector <token> result {};
    for (auto& x: u_input) { result.push_back(tokenize(x)); }
    return result;
}
