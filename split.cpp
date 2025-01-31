/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef> // for NULL

// A helper function to recursively add a node to the end of a list
void appendToListRecursively(Node*& head, Node* nodeToAdd)
{
    // If the list is empty the node becomes the first element
    if (!head)
    {
        head = nodeToAdd; 
    }
    else
    {
        // keeps moving to the next node until we reach the end
        appendToListRecursively(head->next, nodeToAdd);
    }
}

void split(Node*& in, Node*& odds, Node*& evens)
{
    // Base case: If there's nothing left in the list
    if (!in) return;

    // Save the followingNode of the list before we modify anything
    Node* followingNode = in->next;
    in->next = NULL;  // Disconnect the current node

    // Add the current node to the correct list
    if (in->value % 2 != 0)  // If it's odd
    {
        appendToListRecursively(odds, in);
    }
    else  // If it's even
    {
        appendToListRecursively(evens, in);
    }

    //original list erased
    in = NULL;

    
    split(followingNode, odds, evens);
}

