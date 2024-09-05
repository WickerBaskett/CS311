// player_test.cpp
// Glenn G. Chappell
// 2024-09-03
//
// For CS 311 Fall 2024
// Test program for class Player
// For Assignment 1, Exercise A
// Uses the "doctest" unit-testing framework, version 2
// Requires doctest.h, player.hpp, player.cpp

// Includes for code to be tested
#include "player.hpp"        // For class Player
#include "player.hpp"        // Double-inclusion check, for testing only

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
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <sstream>
using std::ostringstream;
#include <cstddef>
using std::size_t;
#include <utility>
// For std::move

// Printable name for this test suite
const std::string test_suite_name =
    "class Player"
    " - CS 311 Assn 1, Ex A";


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


TEST_CASE( "Function return types are correct" )
{
    Player t1;
    Player t2;

    SUBCASE( "Copy assn returns Player by ref" )
    {
        [[maybe_unused]] Player & r(t1 = t2);  // By-ref check
        REQUIRE( TypeCheck<Player>::check(t1 = t2) );
    }

    SUBCASE( "Move assn returns Player by ref" )
    {
        Player t_movable;
        [[maybe_unused]] Player & r(t1 = std::move(t_movable));
                                                     // By-ref check
        REQUIRE( TypeCheck<Player>::check(t1 = std::move(t_movable)) );
    }

    SUBCASE( "Player::getRealName returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.getRealName());
                                                     // By-value check
        REQUIRE( TypeCheck<string>::check(t1.getRealName()) );
    }

    SUBCASE( "Player::getUsername returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.getUsername());
                                                     // By-value check
        REQUIRE( TypeCheck<string>::check(t1.getUsername()) );
    }

    SUBCASE( "Player::getGames returns int by value" )
    {
        [[maybe_unused]] int && rr(t1.getGames());   // By-value check
        REQUIRE( TypeCheck<int>::check(t1.getGames()) );
    }

    SUBCASE( "Player::inactive returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1.inactive());  // By-value check
        REQUIRE( TypeCheck<bool>::check(t1.inactive()) );
    }

    SUBCASE( "Player::toString returns string by value" )
    {
        [[maybe_unused]] string && rr(t1.toString());  // By-value check
        REQUIRE( TypeCheck<string>::check(t1.toString()) );
    }

    SUBCASE( "Player::operator++ [pre] returns by ref" )
    {
        [[maybe_unused]] Player & r(++t1);  // By-ref check
        REQUIRE( TypeCheck<Player>::check(++t1) );
    }

    SUBCASE( "Player::operator++ [post] returns by value" )
    {
        [[maybe_unused]] Player && rr(t1++);  // by-value check
        REQUIRE( TypeCheck<Player>::check(t1++) );
    }

    SUBCASE( "Player::operator-- [pre] returns by ref" )
    {
        [[maybe_unused]] Player & r(--t1);  // By-ref check
        REQUIRE( TypeCheck<Player>::check(--t1) );
    }

    SUBCASE( "Player::operator-- [post] returns by value" )
    {
        [[maybe_unused]] Player && rr(t1--);  // by-value check
        REQUIRE( TypeCheck<Player>::check(t1--) );
    }

    SUBCASE( "operator== returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 == t2);  // by-value check
        REQUIRE( TypeCheck<bool>::check(t1 == t2) );
    }

    SUBCASE( "operator!= returns bool by value" )
    {
        [[maybe_unused]] bool && rr(t1 != t2);  // by-value check
        REQUIRE( TypeCheck<bool>::check(t1 != t2) );
    }

    SUBCASE( "operator<< returns ostream by ref" )
    {
        ostringstream ostr;
        [[maybe_unused]] ostream & r(ostr << t1);  // By-reference check
        REQUIRE( TypeCheck<ostream>::check(ostr << t1) );
    }
}


TEST_CASE( "Functions are const-correct (passes if it compiles)" )
{
    SUBCASE( "Calling functions on a const Player object" )
    {
        const Player tc1;

        [[maybe_unused]] string s1 = tc1.getRealName();
                                     // Player::getRealName
        [[maybe_unused]] string s2 = tc1.getUsername();
                                     // Player::getUsername
        [[maybe_unused]] int w = tc1.getGames();
                                     // Player::getGames
        [[maybe_unused]] bool b = tc1.inactive();
                                     // Player::inactive
        [[maybe_unused]] string s3 = tc1.toString();
                                     // Player::toString

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SUBCASE( "Taking const Player arguments" )
    {
        const Player tc1;
        const Player tc2;

        Player t3 = tc1;             // Copy ctor
        t3 = tc1;                    // Copy assn

        [[maybe_unused]] bool b1 = (tc1 == tc2);
                                     // op==
        [[maybe_unused]] bool b2 = (tc1 != tc2);
                                     // op!=
        ostringstream ostr;
        ostr << tc1;                 // op<<

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SUBCASE( "Taking const string arguments" )
    {
        const string s;

        Player t(s, s, 0);           // Data ctor
        t.setRealName(s);            // Player::setRealName
        t.setUsername(s);            // Player::setUsername

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }
}


TEST_CASE( "Default-cted Player object: blank name, 0 count" )
{
    Player t1;

    REQUIRE( t1.getRealName() == "UNKNOWN" );
    REQUIRE( t1.getUsername() == "UNKNOWN" );
    REQUIRE( t1.getGames() == 0 );
    REQUIRE( t1.inactive() );

    SUBCASE( "Set real name" )
    {
        t1.setRealName("abc");

        REQUIRE( t1.getRealName() == "abc" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );
    }

    SUBCASE( "Set username" )
    {
        t1.setUsername("def");

        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "def" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );
    }

    SUBCASE( "Set games" )
    {
        t1.setGames(20);

        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 20 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set real name, username" )
    {
        t1.setRealName("zebra");
        t1.setUsername("alligator");

        REQUIRE( t1.getRealName() == "zebra" );
        REQUIRE( t1.getUsername() == "alligator" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );
    }

    SUBCASE( "Set username, real name" )
    {
        t1.setUsername("emu");
        t1.setRealName("squirrel");

        REQUIRE( t1.getRealName() == "squirrel" );
        REQUIRE( t1.getUsername() == "emu" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );
    }

    SUBCASE( "Set real name, games" )
    {
        t1.setRealName("xyz");
        t1.setGames(30);

        REQUIRE( t1.getRealName() == "xyz" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 30 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set games, real name" )
    {
        t1.setGames(40);
        t1.setRealName("ghi");

        REQUIRE( t1.getRealName() == "ghi" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 40 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set username, games" )
    {
        t1.setUsername("xyz");
        t1.setGames(30);

        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "xyz" );
        REQUIRE( t1.getGames() == 30 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set games, username" )
    {
        t1.setGames(40);
        t1.setUsername("ghi");

        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "ghi" );
        REQUIRE( t1.getGames() == 40 );
        REQUIRE_FALSE( t1.inactive() );
    }
}


TEST_CASE( "Data-cted Player object" )
{
    Player t1("abc", "xyz", 100);

    REQUIRE( t1.getRealName() == "abc" );
    REQUIRE( t1.getUsername() == "xyz" );
    REQUIRE( t1.getGames() == 100 );
    REQUIRE_FALSE( t1.inactive() );

    SUBCASE( "Set real name" )
    {
        t1.setRealName("above");

        REQUIRE( t1.getRealName() == "above" );
        REQUIRE( t1.getUsername() == "xyz" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set username" )
    {
        t1.setUsername("below");

        REQUIRE( t1.getRealName() == "abc" );
        REQUIRE( t1.getUsername() == "below" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set games" )
    {
        t1.setGames(20);

        REQUIRE( t1.getRealName() == "abc" );
        REQUIRE( t1.getUsername() == "xyz" );
        REQUIRE( t1.getGames() == 20 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set real name, username, games" )
    {
        t1.setRealName("over");
        t1.setUsername("under");
        t1.setGames(111);

        REQUIRE( t1.getRealName() == "over" );
        REQUIRE( t1.getUsername() == "under" );
        REQUIRE( t1.getGames() == 111 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Set games, username, real name" )
    {
        t1.setGames(222);
        t1.setUsername("left");
        t1.setRealName("right");

        REQUIRE( t1.getRealName() == "right" );
        REQUIRE( t1.getUsername() == "left" );
        REQUIRE( t1.getGames() == 222 );
        REQUIRE_FALSE( t1.inactive() );
    }
}


TEST_CASE( "Copied Player objects" )
{
    SUBCASE( "Copy-cted Player object" )
    {
        Player t1("aaa", "bbb", 100);
        Player t2 = t1;

        REQUIRE( t1.getRealName() == "aaa" );
        REQUIRE( t1.getUsername() == "bbb" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "bbb" );
        REQUIRE( t2.getGames() == 100 );
        REQUIRE_FALSE( t2.inactive() );

        t2.setRealName("yyy");
        t2.setUsername("zzz");
        t2.setGames(10);

        REQUIRE( t1.getRealName() == "aaa" );
        REQUIRE( t1.getUsername() == "bbb" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "yyy" );
        REQUIRE( t2.getUsername() == "zzz" );
        REQUIRE( t2.getGames() == 10 );
        REQUIRE_FALSE( t2.inactive() );

        t1.setRealName("ppp");
        t1.setUsername("qqq");
        t1.setGames(20);

        REQUIRE( t1.getRealName() == "ppp" );
        REQUIRE( t1.getUsername() == "qqq" );
        REQUIRE( t1.getGames() == 20 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "yyy" );
        REQUIRE( t2.getUsername() == "zzz" );
        REQUIRE( t2.getGames() == 10 );
        REQUIRE_FALSE( t2.inactive() );
    }

    SUBCASE( "Copy-assigned Player object" )
    {
        Player t1("aaa", "bbb", 100);
        Player t2;
        t2 = t1;

        REQUIRE( t1.getRealName() == "aaa" );
        REQUIRE( t1.getUsername() == "bbb" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "bbb" );
        REQUIRE( t2.getGames() == 100 );
        REQUIRE_FALSE( t2.inactive() );

        t2.setRealName("yyy");
        t2.setUsername("zzz");
        t2.setGames(10);

        REQUIRE( t1.getRealName() == "aaa" );
        REQUIRE( t1.getUsername() == "bbb" );
        REQUIRE( t1.getGames() == 100 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "yyy" );
        REQUIRE( t2.getUsername() == "zzz" );
        REQUIRE( t2.getGames() == 10 );
        REQUIRE_FALSE( t2.inactive() );

        t1.setRealName("ppp");
        t1.setUsername("qqq");
        t1.setGames(20);

        REQUIRE( t1.getRealName() == "ppp" );
        REQUIRE( t1.getUsername() == "qqq" );
        REQUIRE( t1.getGames() == 20 );
        REQUIRE_FALSE( t1.inactive() );
        REQUIRE( t2.getRealName() == "yyy" );
        REQUIRE( t2.getUsername() == "zzz" );
        REQUIRE( t2.getGames() == 10 );
        REQUIRE_FALSE( t2.inactive() );
    }
}


TEST_CASE( "String conversions" )
{
    Player t1;
    Player t2("ttt", "uuu", 100);
    Player t3("", "", 0);

    SUBCASE( "Player::toString" )
    {
        REQUIRE( t1.toString() == "UNKNOWN (UNKNOWN): 0" );
        REQUIRE( t2.toString() == "ttt (uuu): 100" );
        REQUIRE( t3.toString() == " (): 0" );
    }

    SUBCASE( "operator<<(ostream,Player)" )
    {
        ostringstream ostr1;
        ostr1 << t1;
        REQUIRE( ostr1.str() == "UNKNOWN (UNKNOWN): 0" );
        ostringstream ostr2;
        ostr2 << t2;
        REQUIRE( ostr2.str() == "ttt (uuu): 100" );
        ostringstream ostr3;
        ostr3 << t3;
        REQUIRE( ostr3.str() == " (): 0" );
    }
}


TEST_CASE( "Increment & decrement" )
{
    Player t1;
    Player t2("aaa", "nnn", 10);

    SUBCASE( "Increment ordinary object" )
    {
        Player t3 = (++t2);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 11 );
        REQUIRE_FALSE( t2.inactive() );
        REQUIRE( t3.getRealName() == "aaa" );
        REQUIRE( t3.getUsername() == "nnn" );
        REQUIRE( t3.getGames() == 11 );
        REQUIRE_FALSE( t3.inactive() );

        Player t4 = (t2++);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 12);
        REQUIRE_FALSE( t2.inactive() );
        REQUIRE( t4.getRealName() == "aaa" );
        REQUIRE( t4.getUsername() == "nnn" );
        REQUIRE( t4.getGames() == 11 );
        REQUIRE_FALSE( t4.inactive() );

        ++(++t2);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 14 );
        REQUIRE_FALSE( t2.inactive() );
    }

    SUBCASE( "Increment object with zero count" )
    {
        ++t1;
        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 1 );
        REQUIRE_FALSE( t1.inactive() );

        t1++;
        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 2 );
        REQUIRE_FALSE( t1.inactive() );
    }

    SUBCASE( "Decrement ordinary object" )
    {
        Player t3 = (--t2);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 9 );
        REQUIRE_FALSE( t2.inactive() );
        REQUIRE( t3.getRealName() == "aaa" );
        REQUIRE( t3.getUsername() == "nnn" );
        REQUIRE( t3.getGames() == 9 );
        REQUIRE_FALSE( t3.inactive() );

        Player t4 = (t2--);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 8 );
        REQUIRE_FALSE( t2.inactive() );
        REQUIRE( t4.getRealName() == "aaa" );
        REQUIRE( t4.getUsername() == "nnn" );
        REQUIRE( t4.getGames() == 9 );
        REQUIRE_FALSE( t4.inactive() );

        --(--t2);
        REQUIRE( t2.getRealName() == "aaa" );
        REQUIRE( t2.getUsername() == "nnn" );
        REQUIRE( t2.getGames() == 6 );
        REQUIRE_FALSE( t2.inactive() );
    }

    SUBCASE( "Decrement object with zero count" )
    {
        --t1;
        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );

        t1--;
        REQUIRE( t1.getRealName() == "UNKNOWN" );
        REQUIRE( t1.getUsername() == "UNKNOWN" );
        REQUIRE( t1.getGames() == 0 );
        REQUIRE( t1.inactive() );
    }
}


TEST_CASE( "Equality & inequality" )
{
    Player t1("aaa", "nnn", 10);  // Base value
    Player t2("aaa", "nnn", 10);  // Same
    Player t3("bbb", "nnn", 10);  // Different real name
    Player t4("aaa", "ooo", 10);  // Different username
    Player t5("aaa", "nnn", 20);  // Different count

    SUBCASE( "Equality" )
    {
        REQUIRE( t1 == t1 );
        REQUIRE( t1 == t2 );
        REQUIRE( t2 == t1 );
        REQUIRE_FALSE( t1 == t3 );
        REQUIRE_FALSE( t3 == t1 );
        REQUIRE_FALSE( t1 == t4 );
        REQUIRE_FALSE( t4 == t1 );
        REQUIRE_FALSE( t1 == t5 );
        REQUIRE_FALSE( t5 == t1 );
    }

    SUBCASE( "Inequality" )
    {
        REQUIRE_FALSE( t1 != t1 );
        REQUIRE_FALSE( t1 != t2 );
        REQUIRE_FALSE( t2 != t1 );
        REQUIRE( t1 != t3 );
        REQUIRE( t3 != t1 );
        REQUIRE( t1 != t4 );
        REQUIRE( t4 != t1 );
        REQUIRE( t1 != t5 );
        REQUIRE( t5 != t1 );
    }
}


TEST_CASE( "Large values" )
{
    const size_t bigname_len = 1000001;
    string bigname1(bigname_len, 'a');
        // We make this into a long string
    string bigname2(bigname_len, 'b');

    int bigcount = 2147483641;
        // Almost greatest 32-bit signed value

    ostringstream ostr;
    ostr << bigname1 << " (" << bigname2 << "): " << bigcount;
    string bigstringform = ostr.str();
        // String form of Player(bigname1, bigname2, bigcount)

    SUBCASE( "Construction from large values" )
    {
        Player t1(bigname1, bigname2, bigcount);

        REQUIRE( t1.getRealName() == bigname1 );
        REQUIRE( t1.getUsername() == bigname2 );
        REQUIRE( t1.getGames() == bigcount );
        REQUIRE_FALSE( t1.inactive() );

        // Ck size, prefix, suffix first, to avoid huge error msgs
        auto actual = t1.toString();
        REQUIRE( actual.size() == bigstringform.size() );
        REQUIRE( actual.substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( actual.substr(actual.size()-20)
                     == bigstringform.substr(bigstringform.size()-20) );
        REQUIRE( t1.toString() == bigstringform );
    }

    SUBCASE( "Set functions, passing large values" )
    {
        Player t1;
        t1.setRealName(bigname1);
        t1.setUsername(bigname2);
        t1.setGames(bigcount);

        REQUIRE( t1.getRealName() == bigname1 );
        REQUIRE( t1.getUsername() == bigname2 );
        REQUIRE( t1.getGames() == bigcount );
        REQUIRE_FALSE( t1.inactive() );

        // Ck size, prefix, suffix first, to avoid huge error msgs
        auto actual = t1.toString();
        REQUIRE( actual.size() == bigstringform.size() );
        REQUIRE( actual.substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( actual.substr(actual.size()-20)
                     == bigstringform.substr(bigstringform.size()-20) );
        REQUIRE( t1.toString() == bigstringform );
    }
}


TEST_CASE( "Same-object tests" )
{
    SUBCASE("Copy assignment returns *this")
    {
        Player t1;
        Player t2;
        Player & r(t1 = t2);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("Move assignment returns *this")
    {
        Player t1;
        Player t_movable;
        Player & r(t1 = std::move(t_movable));
        REQUIRE( &r == &t1 );
    }

    SUBCASE("Pre-increment returns *this")
    {
        Player t1;
        Player & r(++t1);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("Pre-decrement returns *this")
    {
        Player t1;
        Player & r(--t1);
        REQUIRE( &r == &t1 );
    }

    SUBCASE("Post-increment returns copy")
    {
        Player t1;
        Player && rr1(t1++);
        Player && rr2(t1++);
        REQUIRE_FALSE( &rr1 == &t1 );
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("Post-decrement returns copy")
    {
        Player t1;
        Player && rr1(t1--);
        Player && rr2(t1--);
        REQUIRE_FALSE( &rr1 == &t1 );
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("getRealName returns copy")
    {
        Player t1;
        string && rr1(t1.getRealName());
        string && rr2(t1.getRealName());
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("getUsername returns copy")
    {
        Player t1;
        string && rr1(t1.getUsername());
        string && rr2(t1.getUsername());
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("getGames returns copy")
    {
        Player t1;
        int && rr1(t1.getGames());
        int && rr2(t1.getGames());
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("inactive returns copy")
    {
        Player t1;
        bool && rr1(t1.inactive());
        bool && rr2(t1.inactive());
        REQUIRE_FALSE( &rr1 == &rr2 );
    }

    SUBCASE("operator<< returns original stream")
    {
        ostringstream ostr;
        Player t1;
        ostream & r(ostr << t1);
        REQUIRE( &r == &ostr );
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

