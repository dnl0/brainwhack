// warning: doesn't function correctly

#include <parser/parser.hpp>

void node_tree::add_left(node* head, token data)
{
    while (head->m_left) {
        head = head->m_left;
    }
    head->m_left          = new node;
    head->m_left->m_root  = head;
    head->m_left->m_data  = data;
    head->m_left->m_left  = nullptr;
    head->m_left->m_right = nullptr;
}

void node_tree::add_right(node* head, token data)
{
    while (head->m_right) {
        if (head->m_data.m_data == '[' && !head->m_right) {
            break;
        }
        head = head->m_left;
    }
    head->m_right          = new node;
    head->m_right->m_root  = head;
    head->m_right->m_data  = data;
    head->m_right->m_left  = nullptr;
    head->m_right->m_right = nullptr;
}

void node_tree::delete_nodes(node* head)
{
    if (head->m_right) {
        delete_nodes(head->m_right);
    }
    if (head->m_left) {
        delete_nodes(head->m_left);
    }

    delete [] head;
}

void node_tree::add_token(token data)
{
    static node* head_ref = m_head;

    bool opened_parantheses = false;
    switch (data.m_type) {
        case p_operator:
        case d_operator:
        case io_command:
            add_left(head_ref, data);
            head_ref = head_ref->m_left;
            break;
        case l_punctuator:
            if (!opened_parantheses) {
                add_left(head_ref, data);
                head_ref = head_ref->m_left;
                opened_parantheses = true;
            }
            else {
                add_right(m_head, data);
                head_ref = head_ref->m_right;
                opened_parantheses = false;
            }
            break;
        case comment:
            break;
    }
}

node_tree parse(std::vector <token> token_stream)
{
    node_tree result {};
    for (auto& x: token_stream) {
        result.add_token(x);
    }
    return result;
}
