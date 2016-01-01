# Jester

A minimalist and elegant test library for C++11

### Why?
I know that there are thoudands of test frameworks for C++ out there, and most of them are feature complete compared to Jester. But the reason I made Jester is that sometimes you just need a simple and lightweight solution to add some tests to your personal project.

Jester is heavily inspired by [Mocha](https://mochajs.org/).

### How to use

Jester is a header-only library so the only thing you need to do is download `jester.hpp` in this repository, drop it into your project directory and include it.

#### Example

```c++
// test.cpp
#include "jester.hpp"

using namespace jester;

int main(int argc, char *argv[]) {

    describe("thing", []() {

        it("this should fail", []() {
            assert_equal(2, 3);
        });

        it("this should succeed", []() {
            assert(true);
        });

        describe("sub-thing", []() {

            int x = 1;

            before_each([&]() { x = 3; });

            it("this should fail", []() {
                throw std::runtime_error("whoops");
            });

            it("this should succeed", [&x]() {
                assert_equal(3, x);
            });

        });

    });

    return 0;
}
```

## Contribute

Contributions are greatly appreciated. If you feel that Jester lacks a feature that you need, you can go ahead an make a pull request.


## License

Copyright (c) 2015 Mohamed Boudra

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
