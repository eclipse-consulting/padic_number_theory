
/** 
 *   Demo FLINT program to demonstrate some use of the padic module.
 */


#include "padic.hpp"

#include "exprtk.hpp"
#include "acutest.h"
#include <iostream>
#include <limits>


void test_case_1() 
{
#define P 7ull
#define X 127ull
#define PREC 10ull

    flint::Fmpz p;
    p.set( static_cast<flint::unsigned_long_t>(P) );

    auto ctx = std::make_shared<flint::PadicContext>(p);

    flint::PadicNumber padic(ctx, flint::signed_long_t(PREC));
    padic.set( static_cast<flint::unsigned_long_t>(X) );

    const std::string x_str_terse = padic.toString(flint::PadicPrintMode::TERSE);
    const std::string x_str_series = padic.toString(flint::PadicPrintMode::SERIES);

    TEST_CHECK(x_str_terse == "127");
    TEST_CHECK(x_str_series == "1 + 4*7^1 + 2*7^2");

    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    parser.compile(x_str_terse, expr);
    auto lhs = expr.value();

    parser.compile(x_str_series, expr);
    auto rhs = expr.value();
    
    TEST_CHECK(lhs == rhs);


    std::cout << "x ≡ 127 mod 7^10" << "\n";
    std::cout << "p = " << p << " (0b" << p.toString(flint::Base(2)) << "), is prime: " << p.isPrime() << "\n";
    std::cout << "x = " << x_str_terse << " (" << x_str_series << ")" << "\n";
    std::cout << "\n";
}

void test_case_2() 
{
#define P 2ull
#define X 1057ull
#define PREC 10ull

    flint::Fmpz p;
    p.set(static_cast<flint::unsigned_long_t>(P));

    auto ctx = std::make_shared<flint::PadicContext>(p);

    flint::PadicNumber padic(ctx, flint::signed_long_t(PREC));
    padic.set(static_cast<flint::unsigned_long_t>(X));

    const std::string x_str_terse = padic.toString(flint::PadicPrintMode::TERSE);
    const std::string x_str_series = padic.toString(flint::PadicPrintMode::SERIES);

    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    parser.compile(x_str_terse, expr);
    auto lhs = expr.value();

    parser.compile(x_str_series, expr);
    auto rhs = expr.value();
    
    TEST_CHECK(lhs == rhs);

    std::cout << "x ≡ 1057 mod 2^10" << "\n";
    std::cout << "p = " << p << " (0b" << p.toString(flint::Base(2)) << "), is prime: " << p.isPrime() << "\n";
    std::cout << "x = " << x_str_terse << " (" << x_str_series << ")" << "\n";
    std::cout << "\n";
}

void test_case_3() 
{
#define P 3ull
#define X -127ll
#define PREC 10ull

    flint::Fmpz p;
    p.set(static_cast<flint::unsigned_long_t>(P));

    auto ctx = std::make_shared<flint::PadicContext>(p);

    flint::PadicNumber padic(ctx, flint::signed_long_t(PREC));
    padic.set(static_cast<flint::signed_long_t>(X));

    const std::string x_str_terse = padic.toString(flint::PadicPrintMode::TERSE);
    const std::string x_str_series = padic.toString(flint::PadicPrintMode::SERIES);

    TEST_CHECK(x_str_terse == "58922");    
    TEST_CHECK(x_str_series == "2 + 2*3^1 + 1*3^3 + 1*3^4 + 2*3^5 + 2*3^6 + 2*3^7 + 2*3^8 + 2*3^9");

    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    parser.compile(x_str_terse, expr);
    auto lhs = expr.value();

    parser.compile(x_str_series, expr);
    auto rhs = expr.value();
    
    TEST_CHECK(lhs == rhs);

    std::cout << "x ≡ -127 mod 3^10" << "\n";
    std::cout << "p = " << p << " (0b" << p.toString(flint::Base(2)) << "), is prime: " << p.isPrime() << "\n";
    std::cout << "x = " << x_str_terse << " (" << x_str_series << ")" << "\n";
    std::cout << "\n";
}


void test_logarithm() 
{
#define P 5ull
#define X 7380996ull

    flint::Fmpz p;
    p.set(static_cast<flint::unsigned_long_t>(P));

    auto ctx = std::make_shared<flint::PadicContext>(p, 10, 25);

    flint::PadicNumber x(ctx);
    x.set(static_cast<flint::unsigned_long_t>(X));

    auto y = flint::log(x);

    const std::string x_str_terse = x.toString(flint::PadicPrintMode::TERSE);
    const std::string x_str_series = x.toString(flint::PadicPrintMode::SERIES);

    const std::string y_str_terse = y.toString(flint::PadicPrintMode::TERSE);
    const std::string y_str_series = y.toString(flint::PadicPrintMode::SERIES);

    TEST_CHECK(x_str_series == "1 + 4*5^1 + 4*5^2 + 2*5^3 + 4*5^4 + 1*5^5 + 2*5^6 + 4*5^7 + 3*5^8 + 3*5^9");
    TEST_CHECK(y_str_series == "4*5^1 + 1*5^2 + 3*5^3 + 1*5^4 + 1*5^5 + 4*5^6 + 1*5^7 + 1*5^8 + 2*5^9 + 1*5^10 + 3*5^11 + 4*5^12 + 4*5^13 + 1*5^14 + 2*5^15 + 4*5^18 + 2*5^19");

    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    parser.compile(y_str_terse, expr);
    auto lhs = expr.value();

    parser.compile(y_str_series, expr);
    auto rhs = expr.value();
    
    TEST_CHECK(lhs == rhs);


    std::cout << "log(7380996) mod 5^20" << "\n";
    std::cout << "p = " << p << " (0b" << p.toString(flint::Base(2)) << "), is prime: " << p.isPrime() << "\n";
    std::cout << "x =" << x_str_terse << " (" << x_str_series << ")" << "\n";
    std::cout << "log(x) = " << y_str_terse << " (" << y_str_series << ")" << "\n";
    std::cout << "\n";
}


void test_exp() 
{

    flint::Fmpz p;
    p.set(static_cast<flint::unsigned_long_t>(2));

    auto ctx = std::make_shared<flint::PadicContext>(p, 10, 25);

    flint::PadicNumber x(ctx);
    x.set(static_cast<flint::unsigned_long_t>(4));

    auto y = flint::exp(x);

    const std::string x_str_terse = x.toString(flint::PadicPrintMode::TERSE);
    const std::string x_str_series = x.toString(flint::PadicPrintMode::SERIES);

    const std::string y_str_terse = y.toString(flint::PadicPrintMode::TERSE);
    const std::string y_str_series = y.toString(flint::PadicPrintMode::SERIES);

    TEST_CHECK(x_str_terse == "4");
    TEST_CHECK(y_str_terse == "934221");
    TEST_CHECK(x_str_series == "1*2^2");
    TEST_CHECK(y_str_series == "1 + 1*2^2 + 1*2^3 + 1*2^6 + 1*2^8 + 1*2^14 + 1*2^17 + 1*2^18 + 1*2^19");


    exprtk::expression<double> expr;
    exprtk::parser<double> parser;

    parser.compile(y_str_terse, expr);
    auto lhs = expr.value();

    parser.compile(y_str_series, expr);
    auto rhs = expr.value();
    
    TEST_CHECK(lhs == rhs);


    std::cout << "exp(4) mod 2^10" << "\n";
    std::cout << "p: " << p << " (0b" << p.toString(flint::Base(2)) << "), is prime: " << p.isPrime() << "\n";
    std::cout << "x = " << x_str_terse << " (" << x_str_series << ")" << "\n";
    std::cout << "exp(x) = " << y_str_terse << " (" << y_str_series << ")" << "\n";
    std::cout << "\n";
}

bool multiply_with_overflow_check(flint::unsigned_long_t a, flint::unsigned_long_t b, flint::unsigned_long_t& result) {
    if (a > 0 && b > std::numeric_limits<flint::unsigned_long_t>::max() / a) {
        return false; // Overflow would occur
    }
    result = a * b;
    return true;
}

void test_add() 
{
    std::cout << "x + y" << "\n";

    flint::unsigned_long_t x_int = 1ull;
    for (flint::unsigned_long_t p = 2ull; p <= 47ull; p++)
    {

        flint::Fmpz prime;
        prime.set(p);
        if (prime.isPrime())
        {
            if (!multiply_with_overflow_check(x_int, p, x_int)) 
            {
                throw std::overflow_error("Integer overflow detected");
            }
            std::cout << p << ": " << x_int << "\n";
        }
    }

    for (flint::unsigned_long_t p = 2ull; p <= 47ull; p++)
    {

        flint::Fmpz prime;
        prime.set(p);
        if (prime.isPrime())
        {
            std::cout << "p: " << prime << " (0b" << prime.toString(flint::Base(2)) << ")" << "\n";

            auto ctx = std::make_shared<flint::PadicContext>(prime, 0, 1);

            flint::PadicNumber x(ctx);
            x.set(static_cast<flint::unsigned_long_t>(x_int));
            std::cout << "x = " << x << " (" << x.toString(flint::PadicPrintMode::SERIES) << ")" << "\n";

            flint::PadicNumber y(ctx);
            y.set(static_cast<flint::unsigned_long_t>(1));
            std::cout << "y = " << y << " (" << y.toString(flint::PadicPrintMode::SERIES) << ")" << "\n";

            auto z = x + y;
            std::cout << "x + y = " << z << " (" << z.toString(flint::PadicPrintMode::SERIES) << ")" << "\n";
            std::cout << "\n";
        }
    }
}


TEST_LIST = {
   { "test_case_1", test_case_1 },
   { "test_case_2", test_case_2 },
   { "test_case_2", test_case_3 },
   { "test_logarithm", test_logarithm },
   { "test_exp", test_exp },
   { "test_add", test_add },

   { NULL, NULL }     /* zeroed record marking the end of the list */
};