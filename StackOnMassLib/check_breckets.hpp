#pragma once

#ifndef CHECK_BRECKETS_HPP
#define CHECK_BRECKETS_HPP

#include <string>
#include "StackOnMass.hpp"

inline bool check_breckets(const std::string& str) {
    StackOnMass::TStackOnMass<char> stack(str.size() > 0 ? str.size() : 1);

    for (char ch : str) {
        if (ch == '(' || ch == '[' || ch == '{') {
            try {
                stack.push(ch);
            } catch (const std::overflow_error&) {
                return false;
            }
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.is_empty()) {
                return false;
            }
            char top = stack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;
            }
        }
    }

    return stack.is_empty();
}

#endif  // CHECK_BRECKETS_HPP
