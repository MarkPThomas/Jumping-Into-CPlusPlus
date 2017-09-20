// A non-standard but widely supported preprocessor directive designed to cause the current source file to be included only once in a single compilation.
// This backfires when the same file is intentionally copied into several parts of a project. 
// With include guard based on file path these copies would be treated differently while #pragma once may arbitrarily treat them as the same file in a compiler-dependent way.
#pragma once 

// The most common alternative to #pragma once is to use #define to set an 'include guard' macro, the name of which is picked by the programmer to be unique to that file.
// A good naming standard is for the directory path or namespace from the project head node, and/or the name of the company, to precede the {filename}_H name.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
// Contents of the header (currently outside of the 'include guard', below.
#endif


struct Node
{
	Node* next;
	int value;
};

Node* addNode(Node*  list, int value);
void printList(const Node* list);