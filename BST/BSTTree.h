//
// Created by Moaz Alhabbal on 3/17/16.
//

#ifndef PROJECT1_TREES_BST_H
#define PROJECT1_TREES_BST_H

#include <stdio.h>

class BSTTree {
public:
    int data;
    BSTTree *left;
    BSTTree *right;
};

BSTTree *createNode_BST(int data) {
    BSTTree *node = new BSTTree();
    node->data = data;
    node->left = node->right = NULL;

    return node;
}

BSTTree *insert(BSTTree *root, int data) {
    if (root == NULL) {
        root = createNode_BST(data);
    }
    else if (root->data > data) {
        root->left = insert(root->left, data);
    }
    else if (root->data < data) {
        root->right = insert(root->right, data);
    }
    else
        root->data = data;
    return root;
}


bool search(BSTTree *root, int data) {

    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data > root->data)
        return search(root->right, data);
    else
        return search(root->left, data);
}

int findMin(BSTTree *root) {

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

BSTTree *DeleteNode(BSTTree *root, int data) {

    if (root == NULL)
        return root;
    else if (root->data > data)
        root->left = DeleteNode(root->left, data);
    else if (root->data < data)
        root->right = DeleteNode(root->right, data);

    else {
        // no children case
        if (root->left == NULL && root->right == NULL) {
            delete (root);
            root = NULL;
        }
            // one child case (right)
        else if (root->left == NULL) {
            BSTTree *current = root;
            root = root->right;
            delete (current);
        }
            // one child case (left)
        else if (root->right == NULL) {
            BSTTree *current = root;
            root = root->left;
            delete (current);
        }
            // two children case
        else {
            int min = findMin(root->right);
            root->data = min;
            root->right = DeleteNode(root->right, min);
        }
    }
    return root;
}

void traverse_BST_INORDER(BSTTree *root) {


    if (root == NULL)
        return;
    traverse_BST_INORDER(root->left);
    printf("%d ", root->data);
    traverse_BST_INORDER(root->right);
}


void BST_print_dot_null(int key, int nullcount, FILE *stream) {
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void BST_print_dot_aux(BSTTree *node, FILE *stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->left->data);
        BST_print_dot_aux(node->left, stream);
    }
    else
        BST_print_dot_null(node->data, nullcount++, stream);

    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->right->data);
        BST_print_dot_aux(node->right, stream);
    }
    else
        BST_print_dot_null(node->data, nullcount++, stream);
}

void BST_print_dot(BSTTree *tree, FILE *stream) {
    fprintf(stream, "digraph BSTTree {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->data);
    else
        BST_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}

#endif //PROJECT1_TREES_BST_H
