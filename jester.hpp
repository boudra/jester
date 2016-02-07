#ifndef JESTER_HPP
#define JESTER_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <functional>
#include <map>

namespace jester {

bool assert_true(bool expression) {
    if(!expression) throw std::runtime_error("Expression evaluated false");
    return expression;
}

bool assert_false(bool expression) {
    if(expression) throw std::runtime_error("Expression evaluated true");
    return expression;
}

template <typename a_type, typename b_type>
bool assert_equal(a_type a, b_type b) {
    const bool equal = (a == b);
    if(!equal) {
        std::stringstream detailed;
        detailed << "Failed asserting that: "
            << "\x1B[33m"
            << a
            << "\x1B[0m"
            << " equals: "
            << "\x1B[33m"
            << b
            << "\x1B[0m";
        throw std::runtime_error(detailed.str());
    }
    return equal;
}

struct test_context {
    std::map<std::string, std::function<void()>>* tests;
    std::function<void()> before_each;
    std::function<void()> after_each;
};

std::stack<test_context*> contexts;

void describe(std::string name, std::function<void()> func) {

    std::string prefix;
    test_context context = { new std::map<std::string, std::function<void()>>()
    };
    auto& tests = *context.tests;
    size_t failed = 0;

    prefix.reserve(contexts.size() * 2);

    for(int i = 0; i < contexts.size(); ++i) {
        prefix += "  ";
    }

    std::cout << prefix << name << std::endl;

    contexts.push(&context);
    try {
        func();
    } catch(const std::exception& e) {
        failed++;
    }
    contexts.pop();

    for(auto kv : tests) {
        if(context.before_each) context.before_each();
        try {
            kv.second();
            std::cout
                << prefix
                << "\x1B[32m"
                << " \u2714 "
                << kv.first
                << "\x1B[0m"
                << std::endl;
        } catch(const std::exception& e) {
            std::cout
                << prefix
                << "\x1B[31m"
                << " \u2716 "
                << kv.first
                << "\x1B[0m"
                << std::endl
                << prefix
                << e.what()
                << std::endl;
            failed++;
        }
        if(context.after_each) context.after_each();
    }

    std::cout << std::endl;

    if(contexts.size() == 0) {

        if(failed > 0) {
            std::cout << (failed) << " Test(s) failed" << std::endl;
        } else {
            std::cout << "OK" << std::endl;
        }

    }

    if(failed > 0) {
        throw std::runtime_error("Describe block failed");
    }

}

void it(std::string name, std::function<void()> func) {
    contexts.top()->tests->emplace(name, func);
}

void before_each(std::function<void()> func) {
    contexts.top()->before_each = func;
}

void after_each(std::function<void()> func) {
    contexts.top()->before_each = func;
}

}

#endif
