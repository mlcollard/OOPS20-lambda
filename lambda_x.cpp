/*
    lambda.cpp

    Examples of captures in lambda functions
*/

#include <functional>
#include <sstream>
#include <assert.h>

// NOTE: return type for C++ functions/methods
double average(int n1, int n2) {
    return (n1 + n2) / 2;
}

// NOTE: trailing return type for C++ functions/methods
auto average2(int n1, int n2)->int {
    return (n1 + n2) / 2;
}

// NOTE: deduced return type for C++ functions/methods
auto average3(int n1, int n2) {
    return (n1 + n2) / 2;
}

// runs code with argument 5
int run(std::function<int(int)> code) {

    return code(5);
}

int main(int argc, char* argv[]) {

    // empty capture
    {
        auto result = run(
            [](int n)->int {
                return n + 2;
            }
        );
        assert(result == 7);
    }

    // empty capture, use constexpr
    {
        constexpr int INCR = 2;
        auto result = run(
            [](int n)->int {
                return n + INCR;
            }
        );
        assert(result == 7);
    }

    // const capture
    {
        int size = 2;
        const int INCR = size;
        auto result = run(
            [INCR](int n)->int {
                return n + INCR;
            }
        );
        assert(result == 7);
    }

    // const capture with int
    {
        int size = 2;
        auto result = run(
            [size](int n)->int {
                return n + size;
            }
        );
        assert(result == 7);
    }

    // reference capture, count calls
    {
        int numrun = 0;
        auto result = run(
            [&numrun](int n)->int {
                ++numrun;

                return n + 2;
            }
        );
        assert(numrun == 1);
        assert(result == 7);
    }

    // complex object by capture
    {
        std::istringstream input("2");
        auto result = run(
            [&input](int n) {

                int increase;
                input >> increase;

                return n + increase;
            }
        );
        assert(result == 7);
    }

    // declare and call directly by name
    {
        std::istringstream input("2");
        auto code = [&input](int n) {

            int increase;
            input >> increase;

            return n + increase;
        };
        auto result = code(5);
        assert(result == 7);
    }

    // declare, name, and then pass
    {
        std::istringstream input("2");
        auto code = [&input](int n) {

            int increase;
            input >> increase;

            return n + increase;
        };
        auto result = run(code);
    }

    // inline declare and call lambda directly
    {
        std::istringstream input("2");
        auto result = [&input](int n) {

            int increase;
            input >> increase;

            return n + increase;
        }(5);
        assert(result == 7);
    }

    return 0;
}
