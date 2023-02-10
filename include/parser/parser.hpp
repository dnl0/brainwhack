/*
 * TODO: explain code with comments where necessary
 */

#pragma once

#include <lexer/lexer.hpp>

struct node {
    node* m_root;
    node* m_left;
    node* m_right;
    token m_data;
};

class node_tree {
    private:
        node* m_head;
    public:
        node_tree() 
        {
            m_head          = new node;
            m_head->m_root  = nullptr;
            m_head->m_left  = nullptr;
            m_head->m_right = nullptr;
        }

        inline char get() const         { return m_head->m_data.m_data; }
        inline char get_left() const    { return m_head->m_left->m_data.m_data; }
        inline char get_right() const   { return m_head->m_right->m_data.m_data; }
        inline node* get_head() const   { return m_head; }

        void add_node(token data);
        static void add_left (node* head, token data);
        static void add_right(node* head, token data);
        static void delete_nodes(node* head);

        void add_token(token data);

        ~node_tree()
        {
            delete_nodes(m_head);
        }
};

node_tree parse(std::vector <token> token_stream);
