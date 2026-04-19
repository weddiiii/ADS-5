// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <string>
#include <cctype>
#include <sstream>
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
        if (isspace(inf[i])) continue;

        if (isdigit(inf[i])) {
            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i];
                i++;
            }
            result += ' ';
            i--;
        } else if (inf[i] == '(') {
            ops.Put('(');
        } else if (inf[i] == ')') {
            while (!ops.IsEmpty() && ops.Peek() != '(') {
                result += ops.Peek();
                result += ' ';
                ops.Get();
            }
            ops.Get();
        } else {
            while (!ops.IsEmpty() &&
                   priority(ops.Peek()) >= priority(inf[i])) {
                result += ops.Peek();
                result += ' ';
                ops.Get();
            }
            ops.Put(inf[i]);
        }
    }

    while (!ops.IsEmpty()) {
        result += ops.Peek();
        result += ' ';
        ops.Get();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            st.Put(std::stoi(token));
        } else {
            int b = st.Peek();
            st.Get();
            int a = st.Peek();
            st.Get();
            st.Put(apply(a, b, token[0]));
        }
    }

    return st.Peek();
}
