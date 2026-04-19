// Copyright 2025 NNTU-CS
#include "alg.h"

#include <cctype>
#include <sstream>
#include <string>

#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int apply(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> ops;
    std::string result;

    for (size_t i = 0; i < inf.size(); ++i) {
        if (isspace(inf[i])) {
            continue;
        } else if (isdigit(inf[i])) {
            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (inf[i] == '(') {
            ops.push('(');
        } else if (inf[i] == ')') {
            while (!ops.isEmpty() && ops.top() != '(') {
                result += ops.top();
                result += ' ';
                ops.pop();
            }
            ops.pop();
        } else {
            while (!ops.isEmpty() &&
                   priority(ops.top()) >= priority(inf[i])) {
                result += ops.top();
                result += ' ';
                ops.pop();
            }
            ops.push(inf[i]);
        }
    }

    while (!ops.isEmpty()) {
        result += ops.top();
        result += ' ';
        ops.pop();
    }

    // убрать последний пробел
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            st.push(std::stoi(token));
        } else {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            st.push(apply(a, b, token[0]));
        }
    }

    return st.top();
}
