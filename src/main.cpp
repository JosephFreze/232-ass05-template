
#include <stdio.h>

#include <iostream>
#include <format>

#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Test Declarations — implemented in tests.cpp
// ============================================================

// STAGE 0
void test_printLegacyData_int(void);
void test_printLegacyData_double(void);

// STAGE 1
void test_createTwoStructNodes_links_correctly(void);

// STAGE 2
void test_createTwoClassNodes_links_correctly(void);

// STAGE 3
void test_createTwoTemplateNodes_links_correctly(void);

// STAGE 4
void test_linkedList_addFirst_updates_counter(void);
void test_linkedList_addLast_places_at_end(void);
void test_linkedList_deleteValue_removes_variant(void);
void test_linkedList_destroyList_clears_all(void);
void test_linkedList_deleteFirst(void);
void test_linkedList_deleteLast(void);
void test_linkedList_printList(void);

// ============================================================
// Required by Unity Framework
// ============================================================
void setUp(void)    {}
void tearDown(void) {}

// ============================================================
// Main Test Runner
// ============================================================

class Node
{
    public: int value;
    public: Node * nextPtr;
};


template <typename T>
class classNodeT
{
    public: T value;
    public: classNodeT * nextPtr;
};

using namespace std;


int main(void) 
{
    Node node;
    node.value = 5;
    node.nextPtr = NULL;

    classNodeT<int> nodeT;
    nodeT.value = 5;

    classNodeT<string> nodeT2;
    nodeT2.value = "hello world";

    cout << nodeT.value << endl;
    cout << nodeT2.value << endl;

    std::string name = "John";
    
    double num = 3.14159;

    std::string formatted_str = std::format("My name is {:.2s} and pi is {:.2f}", name, num);

    // std::cout << std::format("My name is {:.2s} and pi is {:.2f}", name, num) << std::endl;

    std::cout << std::format("first var{0} and second var {1} and first var {0}", 1, 2) << std::endl; 





    UNITY_BEGIN();

    // ========== STAGE 0 ==========
    RUN_TEST(test_printLegacyData_int);
    RUN_TEST(test_printLegacyData_double);

    // ========== STAGE 1 ==========
    RUN_TEST(test_createTwoStructNodes_links_correctly);

    // ========== STAGE 2 ==========
    RUN_TEST(test_createTwoClassNodes_links_correctly);

    // ========== STAGE 3 ==========
    RUN_TEST(test_createTwoTemplateNodes_links_correctly);

    // ========== STAGE 4 ==========
    RUN_TEST(test_linkedList_addFirst_updates_counter);
    RUN_TEST(test_linkedList_addLast_places_at_end);
    RUN_TEST(test_linkedList_deleteValue_removes_variant);
    RUN_TEST(test_linkedList_destroyList_clears_all);
    RUN_TEST(test_linkedList_deleteFirst);
    RUN_TEST(test_linkedList_deleteLast);
    RUN_TEST(test_linkedList_printList);

    int result = UNITY_END();
    return result;
}