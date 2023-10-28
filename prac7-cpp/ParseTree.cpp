#include "ParseTree.h"

using namespace std;

/**
 * A node in a Parse Tree data structure
 * @param type The type of node (see element types).
 * @param value The node's value. This should only be present on terminal nodes/leaves, and empty otherwise.
 */
ParseTree::ParseTree(string type, string value) {
    ParseTree::type = type;
    ParseTree::value = value;
}

/**
 * Adds a ParseTree as a child of this ParseTree
 * @param child The ParseTree to add
 */
void ParseTree::addChild(ParseTree* child) {
    ParseTree::children.push_back(child);
}

/**
 * Get a list of child nodes in the order they were added.
 * @return A LinkedList of ParseTrees
 */
list<ParseTree*> ParseTree::getChildren() {
    return ParseTree::children;
}

/**
 * Get the type of this Node
 * @return The type of node (see element types).
 */
string ParseTree::getType() {
    return ParseTree::type;
}

/**
 * Get the value of this Node
 * @return The node's value. This should only be used on terminal nodes/leaves, and empty otherwise.
 */
string ParseTree::getValue() {
    return ParseTree::value;
}

/**
 * Generate a string from this ParseTree
 * @return A printable representation of this ParseTree
 */
string ParseTree::tostring() {
    return ParseTree::tostring(0);
}

/**
 * Generate a string from this ParseTree
 * @return A printable representation of this ParseTree with indentation
 */
string ParseTree::tostring(int depth) {
    // Set indentation
    string indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "  \u2502 ";
    }

    // Generate output
    string output = "";
    if (ParseTree::children.size() > 0) {
        // Output if the node has children
        output += ParseTree::type + "\n";
        for (ParseTree* child : children) {
            output += indent + "  \u2514 " + child->tostring(depth + 1);
        }
        output += indent + "\n";
    } else {
        // Output if the node is a leaf/terminal
        output += ParseTree::type + " " + ParseTree::value + "\n";
    }
    return output;
}