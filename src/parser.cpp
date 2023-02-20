// warning: doesn't function correctly yet
//
// @TODO: write a static function add_node that will
//        add a node for left and right to avoid 
//        code duplication

#include <parser/parser.hpp>

#include <iostream>

void node_tree::add_left(node* head, token data) noexcept
{
    if (!head) {
        std::clog << "warning: passing nullptr in add_left function\n";
        return;
    }
    while (head->m_left) { head = head->m_left; }
    
    head->m_left = new node;
    if (!head->m_left) { 
        std::cerr << "fatal: not enough space, can't add a node\n"; 
        exit(EXIT_FAILURE);
    }
    head->m_left->m_root  = head;
    head->m_left->m_data  = data;
    head->m_left->m_left  = nullptr;
    head->m_left->m_right = nullptr;
}

void node_tree::add_right(node* head, token data) noexcept
{
    if (!head) {
        std::clog << "warning: passing nullptr in add_right function\n"; 
        return;
    }
    while (head->m_right) { head = head->m_left; }

    head->m_right = new node;
    if (!head->m_right) {
        std::cerr << "fatal: not enough space, can't add a node\n"; 
        exit(EXIT_FAILURE);
    }
    head->m_right->m_root  = head;
    head->m_right->m_data  = data;
    head->m_right->m_left  = nullptr;
    head->m_right->m_right = nullptr;
}

void node_tree::delete_nodes(node* head) noexcept
{
    if (!head)         { return; }
    if (head->m_right) { delete_nodes(head->m_right); }
    if (head->m_left)  { delete_nodes(head->m_left);  }

    delete head;
}

void node_tree::add_token(token data) noexcept
{
    static node* head_ref = m_head;
    /*
     * the problem with this approach is that when new opening bracket opens 
     * it effectively takes this owndership over this ref, and so other refs
     * of previous brackets are lost, which leads to current, wrong behavior
     */
    static node* bracket_ref = m_head;
    /* one way to fix this issue would be to do one of the followings:
     *      * implement some sort of array or linked list that is gonna
     *          save all the refs to all the brackets. not only it is
     *          pain to implement but will also be quite inneficient
     *          and take more space and time, but will provide more 
     *          functionality in the unforeseeable future. on the other
     *          hand it's something that is needed to build a fully 
     *          functional parse tree, since right now it doesn't even
     *          save closing brackets to its corresponding opening
     *          brackets, so it's pretty unavoidable unless i can think
     *          of something better.
     */

    bool opened_brackets = false;
    switch (data.m_type) {
        case p_operator:
        case d_operator:
        case io_command:
            add_right(head_ref, data);
            head_ref = head_ref->m_right;
            break;
        case b_open:
            add_right(head_ref, data);
            head_ref = head_ref->m_right;
            brackets_ref = head_ref;
            break;
        case b_close:
            add_left(brackets_ref, data);
            break;
        case comment:
            break; // avoid warning
    }
}

node* check_brackets(node* head)
{
    while (head->m_right) {
        if (head->get() == '[' && head->m_left == nullptr) {
            return head;
        }
        head = head->m_right; // since opening brackets
                              // are found on the right
                              // side, and closing ones
                              // are always on the left
    }

    return nullptr; // bit counter-intuitive but if brackets
                    // are closed there is no need to return
                    // head, and if it is not closed we need
                    // to return head so that a caller could
                    // read the line and column of that head
}

node_tree* parse(std::vector <token> token_stream)
{
    node_tree* result = new node_tree {};

    for (auto& x: token_stream) {
        result->add_token(x);
    }

    {
        node* found_mistake = check_brackets(result->get_head());
        if (found_mistake) {
            std::cerr << "fatal: brackets at " << found_mistake->line()
                << " " << found_mistake->column() << " not closed\n";
            //exit(EXIT_FAILURE);
        }
    }

    return result;
}
