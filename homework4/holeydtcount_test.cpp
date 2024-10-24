// holeydtcount_test.cpp
// Glenn G. Chappell
// 2024-09-26
//
// For CS 311 Fall 2024
// Test program for function holeyDTCount
// For Assignment 4, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, holeydtcount.h, holeydtcount.cpp

// Includes for code to be tested
#include "holeydtcount.hpp"  // For holeyDTCount
#include "holeydtcount.hpp"  // Double-inclusion check, for testing only

// Includes for the "doctest" unit-testing framework
#define DOCTEST_CONFIG_IMPLEMENT
                             // We write our own main
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
                             // Reduce compile time
#include "doctest.h"         // For doctest

// Includes for all test programs
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

// Additional includes for this test program
// (None)

// Printable name for this test suite
const std::string test_suite_name =
    "function holeyDTCount"
    " - CS 311 Assn 4, Ex A";

// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single
    // function that takes a single parameter, and returns true iff the
    // parameter has type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check([[maybe_unused]] const T & param)
    {
        return true;
    }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check([[maybe_unused]] const OtherType & param)
    {
        return false;
    }

};  // End class TypeCheck


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Return type" )
{
    INFO( "holeyDTCount returns int by value" );
    [[maybe_unused]] int && rr(holeyDTCount(4,3, 2,0, 3,2));
        // by-value check
    REQUIRE( TypeCheck<int>::check(holeyDTCount(4,3, 2,0, 3,2)) );
}


TEST_CASE( "n x 1 and 1 x n boards" )
{
    SUBCASE( "All 2 x 1 boards" )
    {
        REQUIRE( holeyDTCount(2,1, 0,0, 1,0) == 1);
        REQUIRE( holeyDTCount(2,1, 1,0, 0,0) == 1);
    }

    SUBCASE( "All 1 x 2 boards" )
    {
        REQUIRE( holeyDTCount(1,2, 0,0, 0,1) == 1);
        REQUIRE( holeyDTCount(1,2, 0,1, 0,0) == 1);
    }

    SUBCASE( "All 3 x 1 boards" )
    {
        REQUIRE( holeyDTCount(3,1, 0,0, 1,0) == 0 );
        REQUIRE( holeyDTCount(3,1, 0,0, 2,0) == 0 );
        REQUIRE( holeyDTCount(3,1, 1,0, 0,0) == 0 );
        REQUIRE( holeyDTCount(3,1, 1,0, 2,0) == 0 );
        REQUIRE( holeyDTCount(3,1, 2,0, 0,0) == 0 );
        REQUIRE( holeyDTCount(3,1, 2,0, 1,0) == 0 );
    }

    SUBCASE( "All 1 x 3 boards" )
    {
        REQUIRE( holeyDTCount(1,3, 0,0, 0,1) == 0 );
        REQUIRE( holeyDTCount(1,3, 0,0, 0,2) == 0 );
        REQUIRE( holeyDTCount(1,3, 0,1, 0,0) == 0 );
        REQUIRE( holeyDTCount(1,3, 0,1, 0,2) == 0 );
        REQUIRE( holeyDTCount(1,3, 0,2, 0,0) == 0 );
        REQUIRE( holeyDTCount(1,3, 0,2, 0,1) == 0 );
    }

    SUBCASE( "All 4 x 1 boards" )
    {
        REQUIRE( holeyDTCount(4,1, 0,0, 1,0) == 1 );
        REQUIRE( holeyDTCount(4,1, 0,0, 2,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 0,0, 3,0) == 1 );
        REQUIRE( holeyDTCount(4,1, 1,0, 0,0) == 1 );
        REQUIRE( holeyDTCount(4,1, 1,0, 2,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 1,0, 3,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 2,0, 0,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 2,0, 1,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 2,0, 3,0) == 1 );
        REQUIRE( holeyDTCount(4,1, 3,0, 0,0) == 1 );
        REQUIRE( holeyDTCount(4,1, 3,0, 1,0) == 0 );
        REQUIRE( holeyDTCount(4,1, 3,0, 2,0) == 1 );
    }

    SUBCASE( "All 1 x 4 boards" )
    {
        REQUIRE( holeyDTCount(1,4, 0,0, 0,1) == 1 );
        REQUIRE( holeyDTCount(1,4, 0,0, 0,2) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,0, 0,3) == 1 );
        REQUIRE( holeyDTCount(1,4, 0,1, 0,0) == 1 );
        REQUIRE( holeyDTCount(1,4, 0,1, 0,2) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,1, 0,3) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,2, 0,0) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,2, 0,1) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,2, 0,3) == 1 );
        REQUIRE( holeyDTCount(1,4, 0,3, 0,0) == 1 );
        REQUIRE( holeyDTCount(1,4, 0,3, 0,1) == 0 );
        REQUIRE( holeyDTCount(1,4, 0,3, 0,2) == 1 );
    }

    SUBCASE( "Various n x 1 boards with n > 4" )
    {
        REQUIRE( holeyDTCount(10,1,  0,0,  9,0) == 1 );
        REQUIRE( holeyDTCount(50,1,  1,0,  0,0) == 1 );
        REQUIRE( holeyDTCount(60,1,  1,0,  2,0) == 0 );
        REQUIRE( holeyDTCount(60,1, 24,0, 25,0) == 1 );
        REQUIRE( holeyDTCount(98,1, 97,0,  0,0) == 1 );
        REQUIRE( holeyDTCount(99,1, 98,0, 97,0) == 0 );
    }

    SUBCASE( "Various 1 x n boards with n > 4" )
    {
        REQUIRE( holeyDTCount(1,12, 0,11, 0, 0) == 1 );
        REQUIRE( holeyDTCount(1,48, 0, 0, 0, 1) == 1 );
        REQUIRE( holeyDTCount(1,62, 0,38, 0,37) == 0 );
        REQUIRE( holeyDTCount(1,62, 0,37, 0,36) == 1 );
        REQUIRE( holeyDTCount(1,98, 0,96, 0,97) == 1 );
        REQUIRE( holeyDTCount(1,99, 0, 0, 0,98) == 0 );
    }
}


TEST_CASE( "Small boards" )
{
    SUBCASE( "Various small boards" )
    {
        REQUIRE( holeyDTCount(2,4, 1,0, 0,2) ==  1 );
        REQUIRE( holeyDTCount(5,2, 1,0, 3,1) ==  1 );
        REQUIRE( holeyDTCount(3,4, 2,0, 2,1) ==  7 );
        REQUIRE( holeyDTCount(3,6, 1,2, 2,4) ==  3 );
        REQUIRE( holeyDTCount(4,5, 1,2, 2,3) ==  0 );
        REQUIRE( holeyDTCount(5,4, 4,1, 0,0) == 16 );
        REQUIRE( holeyDTCount(3,7, 1,1, 1,2) ==  0 );
    }
}


TEST_CASE( "Fibonacci Fun" )
{
    SUBCASE( "Boards whose results are Fibonacci numbers" )
    {
        REQUIRE( holeyDTCount( 1,2, 0,0, 0,1) ==    1 );
        REQUIRE( holeyDTCount( 2,2, 0,0, 0,1) ==    1 );
        REQUIRE( holeyDTCount( 3,2, 0,0, 0,1) ==    2 );
        REQUIRE( holeyDTCount( 4,2, 0,0, 0,1) ==    3 );
        REQUIRE( holeyDTCount( 5,2, 0,0, 0,1) ==    5 );
        REQUIRE( holeyDTCount( 6,2, 0,0, 0,1) ==    8 );
        REQUIRE( holeyDTCount( 7,2, 0,0, 0,1) ==   13 );
        REQUIRE( holeyDTCount( 8,2, 0,0, 0,1) ==   21 );
        REQUIRE( holeyDTCount( 9,2, 0,0, 0,1) ==   34 );
        REQUIRE( holeyDTCount(10,2, 0,0, 0,1) ==   55 );
        REQUIRE( holeyDTCount(11,2, 0,0, 0,1) ==   89 );
        REQUIRE( holeyDTCount(12,2, 0,0, 0,1) ==  144 );
        REQUIRE( holeyDTCount(13,2, 0,0, 0,1) ==  233 );
        REQUIRE( holeyDTCount(14,2, 0,0, 0,1) ==  377 );
        REQUIRE( holeyDTCount(15,2, 0,0, 0,1) ==  610 );
        REQUIRE( holeyDTCount(16,2, 0,0, 0,1) ==  987 );
        REQUIRE( holeyDTCount(17,2, 0,0, 0,1) == 1597 );
    }
}


TEST_CASE( "Larger boards" )
{
    SUBCASE( "Various larger boards" )
    {
        REQUIRE( holeyDTCount( 2,11, 0,4, 1,4) ==   65 );
        REQUIRE( holeyDTCount(12, 2, 7,0, 7,1) ==  105 );
        REQUIRE( holeyDTCount( 4, 7, 1,1, 3,4) ==   91 );
        REQUIRE( holeyDTCount(10, 3, 2,1, 6,2) ==   12 );
        REQUIRE( holeyDTCount( 4, 8, 1,0, 3,6) ==    0 );
        REQUIRE( holeyDTCount( 8, 4, 5,3, 1,0) ==  175 );
        REQUIRE( holeyDTCount( 6, 6, 3,0, 4,0) == 1276 );
        REQUIRE( holeyDTCount( 2,19, 0,9, 1,9) == 3025 );
        REQUIRE( holeyDTCount( 5, 8, 0,0, 1,0) == 6533 );
    }
}


TEST_CASE( "Slide Examples" )
{
    SUBCASE( "Examples from \"Thoughts on Assignment 4\" slides" )
    {
        REQUIRE( holeyDTCount(4,3, 2,0, 3,2) ==    4 );
        REQUIRE( holeyDTCount(3,2, 2,1, 0,0) ==    1 );
        REQUIRE( holeyDTCount(4,1, 1,0, 3,0) ==    0 );
        REQUIRE( holeyDTCount(8,5, 6,4, 7,4) == 8291 );
    }
}


// *********************************************************************
// Main Program
// *********************************************************************


// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    std::cout.flush();
    while (std::cin.get() != '\n') ;
}


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    doctest::Context dtcontext;
                             // Primary doctest object
    int dtresult;            // doctest return code; for return by main

    // Handle command line
    dtcontext.applyCommandLine(argc, argv);
    dtresult = 0;            // doctest flags no command-line errors
                             //  (strange but true)

    if (!dtresult)           // Continue only if no command-line error
    {
        // Run test suites
        cout << "BEGIN tests for " << test_suite_name << "\n" << endl;
        dtresult = dtcontext.run();
        cout << "END tests for " << test_suite_name << "\n" << endl;
    }

    // If we want to do something else here, then we need to check
    // dtcontext.shouldExit() first.

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from doctest
    return dtresult;
}

