// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// Author: Joseph Freze
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"





std::string printLegacyData(LegacyData data, char type) {
    std::string result = "unknown";
    
    if(type == 'i')
    {
        result = std::format("{}", data.i);
        return result;
    }
    if(type == 'd')
    {
        result = std::format("{}", data.d);
        return result;
    }
    if(type == 'c')
    {
        if(data.cPtr != NULL)
        {
            result = std::format("{}", data.cPtr);
            return result;
        }
    }
    return result;
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type)
{
    if (nPtr == nullptr)
    {
        return;
    }

    if (type == 'i')
    {
        nPtr->value.i = val.i;
    }
    else if (type == 'd')
    {
        nPtr->value.d = val.d;
    }
    else if (type == 'c')
    {
        nPtr->value.cPtr = val.cPtr;
    }

    nPtr->nextPtr = nullptr;
    nPtr->typeData = type;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    // TODO: Allocate dynamically using new, initialize both nodes, link them, and return head
    LegacyData data;

    structNode* head = new structNode;
    data.i = 5;

    initStructNode(head, data, 'i');

    structNode* second = new structNode;
    data.d = 3.14;

    initStructNode(second, data, 'd');

    head->nextPtr = second;

    return head;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type)
{
    if (type == 'i')
    {
        value.i = val.i;
    }
    else if (type == 'd')
    {
        value.d = val.d;
    }
    else if (type == 'c')
    {
        value.cPtr = val.cPtr;
    }

    typeData = type;
    nextPtr = nullptr;
}

classNode* createTwoClassNodes()
{
    LegacyData data;

    data.i = 5;
    classNode* head = new classNode(data, 'i');

    data.d = 3.14;
    classNode* second = new classNode(data, 'd');

    head->nextPtr = second;

    return head;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes()
{
    classNodeT<int>* head = new classNodeT<int>(5);
    classNodeT<int>* second = new classNodeT<int>(3);

    head->nextPtr = second;

    return head;
}
// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList()
{
    headPtr = nullptr;
    counter = 0;
}

LinkedList::~LinkedList()
{
    destroyList();
}

// uncoment the following code to implement the LinkedList methods

void LinkedList::destroyList()
{
    classNodeVariant* currentPtr = headPtr;

    while (currentPtr != nullptr)
    {
        classNodeVariant* nextPtr = currentPtr->nextPtr;
        delete currentPtr;
        currentPtr = nextPtr;
    }

    headPtr = nullptr;
    counter = 0;
}

int LinkedList::addFirst(classNodeVariant* newNodePtr)
{
    if (newNodePtr == nullptr)
    {
        return -1;
    }

    newNodePtr->nextPtr = headPtr;
    headPtr = newNodePtr;
    counter++;

    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr)
{
    if (newNodePtr == nullptr)
    {
        return -1;
    }

    newNodePtr->nextPtr = nullptr;

    if (headPtr == nullptr)
    {
        headPtr = newNodePtr;
    }
    else
    {
        classNodeVariant* currentPtr = headPtr;

        while (currentPtr->nextPtr != nullptr)
        {
            currentPtr = currentPtr->nextPtr;
        }

        currentPtr->nextPtr = newNodePtr;
    }

    counter++;

    return 0;
}

int LinkedList::deleteFirst()
{
    if (headPtr == nullptr)
    {
        return -1;
    }

    classNodeVariant* tempPtr = headPtr;
    headPtr = headPtr->nextPtr;

    delete tempPtr;
    counter--;

    return 0;
}

int LinkedList::deleteLast()
{
    if (headPtr == nullptr)
    {
        return -1;
    }

    if (headPtr->nextPtr == nullptr)
    {
        delete headPtr;
        headPtr = nullptr;
        counter--;

        return 0;
    }

    classNodeVariant* currentPtr = headPtr;

    while (currentPtr->nextPtr->nextPtr != nullptr)
    {
        currentPtr = currentPtr->nextPtr;
    }

    delete currentPtr->nextPtr;
    currentPtr->nextPtr = nullptr;

    counter--;

    return 0;
}

int LinkedList::deleteValue(ModernData targetValue)
{
    if (headPtr == nullptr)
    {
        return -1;
    }

    if (headPtr->value == targetValue)
    {
        return deleteFirst();
    }

    classNodeVariant* currentPtr = headPtr;

    while (currentPtr->nextPtr != nullptr)
    {
        if (currentPtr->nextPtr->value == targetValue)
        {
            classNodeVariant* tempPtr = currentPtr->nextPtr;

            currentPtr->nextPtr = tempPtr->nextPtr;

            delete tempPtr;
            counter--;

            return 0;
        }

        currentPtr = currentPtr->nextPtr;
    }

    return -1;
}

int LinkedList::printList()
{
    if (headPtr == nullptr)
    {
        return -1;
    }

    classNodeVariant* currentPtr = headPtr;

    while (currentPtr != nullptr)
    {
        if (std::holds_alternative<int>(currentPtr->value))
        {
            std::cout << std::get<int>(currentPtr->value);
        }
        else if (std::holds_alternative<double>(currentPtr->value))
        {
            std::cout << std::get<double>(currentPtr->value);
        }
        else if (std::holds_alternative<std::string>(currentPtr->value))
        {
            std::cout << std::get<std::string>(currentPtr->value);
        }

        std::cout << std::endl;
        currentPtr = currentPtr->nextPtr;
    }

    return 0;
}

int LinkedList::listLength()
{
    return counter;
}