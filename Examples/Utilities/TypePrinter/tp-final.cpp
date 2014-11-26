//! A Simple Type Printer Program

/*!@file
 * Final stage of the type printer developed in a series of steps.
 *
 * This type printer works for all builtin types including such with
 * cv-qualification, pointers and reference (lvalue and rvalue).
*/

#include <string>

/*!
 * Primary template for the type printer.
 *
 * @note
 * This is declared but not defined.
 *
 * Definitions will only be done as full and partial specialisations.
*/
template<typename T>
struct TP;
    
/*!
 * Helper to create partial specialisations for simple basic types.
 *
 * This helper will later be called from other macros to create the
 * required specialisations.
*/
#define TEMPLATE_SIMPLE(t)\
    template<>\
    struct TP<t> {\
        static std::string str() { return {#t}; }\
    };

/*!
 * Helper to create partial specialisations for signed/unsigned types.
 *
 * This helper will later be called from other macros to create the
 * required specialisations.
*/
#define TEMPLATE_SIGNED_UNSIGNED(t)\
    TEMPLATE_SIMPLE(signed t)\
    TEMPLATE_SIMPLE(unsigned t)
    
/*!
 * Main driver for calling the helpers.
 *
 * This driver not only helps to create the specialisations but also
 * the tests.
*/
#define DO_FOR_EACH_BASIC_TYPE(M)\
    M(SIMPLE, void)\
    M(SIMPLE, bool)\
    M(SIMPLE, char)\
    M(SIMPLE, wchar_t)\
    M(SIGNED_UNSIGNED, char)\
    M(SIGNED_UNSIGNED, short)\
    M(SIGNED_UNSIGNED, int)\
    M(SIGNED_UNSIGNED, long)\
    M(SIGNED_UNSIGNED, long long)\
    M(SIMPLE, float)\
    M(SIMPLE, double)\
    M(SIMPLE, long double)\
    M(SIMPLE, std::nullptr_t)
    
/*!
 * Connect the main driver to helpers to create specialisations.
 *
 * This macro provides the glue between driver macro and helper macros
 * when specialisations are created.
*/
#define GENERATE_TEMPLATE(s, t)\
    TEMPLATE_ ## s(t)

/*!
 * Helper to create test cases for simple basic types.
 *
 * This helper will later be called from other macros to create the
 * required test cases.
*/
#define TESTCASE_SIMPLE(t)\
    X_(TP<t>::str(), #t);
    
/*!
 * Helper to create test cases for signed/unsigned types.
 *
 * This helper will later be called from other macros to create the
 * required test cases.
*/
#define TESTCASE_SIGNED_UNSIGNED(t)\
    X_(TP<signed t>::str(), "signed " #t);\
    X_(TP<unsigned t>::str(), "unsigned " #t);
    
/*!
 * Connect the main driver to helpers to create test cases.
 *
 * This macro provides the glue between driver macro and helper macros
 * when test cases are created.
*/
#define GENERATE_TESTCASE(s, t)\
    TESTCASE_ ## s(t)

/*!
 * Helper to create specialisations for cv-qualified types.
 *
 * This helper will later be called to create the required specialisation for:
 * @li const
 * @li volatile
 * @li const volatile
*/
#define TEMPLATE_CV_QUALIFIED(cv)\
    template<typename T>\
    struct TP<T cv> {\
        static std::string str() { return TP<T>::str() + " " #cv; }\
    };

/*!
 * Helper to create specialisations for decorated types.
 *
 * This helper will later be called to create the required specialisation for
 * @li *
 * @li &
 * @li &&
*/
#define TEMPLATE_DECORATED(d)\
    template<typename T>\
    struct TP<T d> {\
        static std::string str() { return TP<T>::str() + "" #d; }\
    };

// --------------------------------------------
// Actually create template specialisations now
// --------------------------------------------

// For all the basic types:
//
DO_FOR_EACH_BASIC_TYPE(GENERATE_TEMPLATE)
    
// For the cv-qualifications:
//
TEMPLATE_CV_QUALIFIED(const)
TEMPLATE_CV_QUALIFIED(volatile)
TEMPLATE_CV_QUALIFIED(const volatile)

// For the decorations:
//
TEMPLATE_DECORATED(&)
TEMPLATE_DECORATED(&&)
TEMPLATE_DECORATED(*)
    
#include "../..//Utilities/PT/PT.h"

#ifndef TYPEPRINTER_INCLUDE_ONLY
/*!
 * main function for testing the TypePrinter.
*/
int main() {

#ifdef ALL_BASIC_TYPES

    // actually create tst cases for all basic types
    //
    DO_FOR_EACH_BASIC_TYPE(GENERATE_TESTCASE)

#endif

#ifdef SOME_CV_QUALIFICATIONS
    
    X_(TP<int const>::str()          , "signed int const");
    X_(TP<signed const int>::str()   , "signed int const");
    X_(TP<const signed int>::str()   , "signed int const");
    X_(TP<const volatile int>::str() , "signed int const volatile");

#endif
    
#ifdef SOME_DECORATIONS
    
    X_(TP<void *>::str()              , "void*");
    X_(TP<void *>::str()              , "void*");
    X_(TP<void **>::str()             , "void**");
    X_(TP<void *const *>::str()       , "void* const*");
    
    X_(TP<char const*>::str()         , "char const*");
    X_(TP<char* const>::str()         , "char* const");
    
    X_(TP<char &>::str()              , "char&");
    X_(TP<const char&>::str()         , "char const&");

    X_(TP<char &&>::str()             , "char&&");
    X_(TP<char *&>::str()             , "char*&");
    X_(TP<char *const &>::str()       , "char* const&");

#endif

}
#endif

