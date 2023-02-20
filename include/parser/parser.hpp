/*
 * @TODO: explain code with comments where necessary
 *        fix balancing of the parse tree
 *        fix deleting issue (or use smart pointers)
 *        check for opened parantheses
 *        optimize operations
 */

#pragma once

#include <lexer/lexer.hpp>

struct node {
    node* m_root;   // questionable whether necessary
    node* m_left;
    node* m_right;
    token m_data;

    inline const int  line()   const { return m_data.m_line;   }
    inline const int column()  const { return m_data.m_column; }
    inline const char& get()   const { return m_data.m_data;   }
};

class node_tree {
    private:
        node* m_head;
    public:
        node_tree() 
        {
            m_head = new node;
            m_head->m_right = nullptr;
            m_head->m_left = nullptr;
        }

        inline char get() const         { return m_head->m_data.m_data; }
        inline node* get_head() const   { return m_head; }

        void add_node(token data) noexcept;
        static void add_left (node* head, token data) noexcept;
        static void add_right(node* head, token data) noexcept;
        static void delete_nodes(node* head) noexcept;

        void add_token(token data) noexcept;

        ~node_tree()
        {
            delete_nodes(m_head);
        }
};

node* check_parantheses(node* head);
node_tree* parse(std::vector <token> token_stream);
