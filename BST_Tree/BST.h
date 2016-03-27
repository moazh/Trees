//
// Created by Moaz Alhabbal on 3/17/16.
//

#ifndef PROJECT1_TREES_BST_H
#define PROJECT1_TREES_BST_H

#include <stdio.h>

class BST {
public:
    int data;
    BST *left;
    BST *right;
};

BST *createNode_BST(int data) {
    BST *node = new BST();
    node->data = data;
    node->left = node->right = NULL;

    return node;
}

BST *insert(BST *root, int data) {
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


bool search(BST *root, int data) {

    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data > root->data)
        return search(root->right, data);
    else
        return search(root->left, data);
}

int findMin(BST *root) {

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

BST *DeleteNode(BST *root, int data) {

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
            BST *current = root;
            root = root->right;
            delete (current);
        }
            // one child case (left)
        else if (root->right == NULL) {
            BST *current = root;
            root = root->left;
            delete (current);
        }
            // two children case
        else {
            int min = findMin(root->right);
            root->data = min;
            root->right = DeleteNode(root->right, data);
        }
    }
    return root;
}

void traverse_BST_INORDER(BST *root) {


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

void BST_print_dot_aux(BST *node, FILE *stream) {
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

void BST_print_dot(BST *tree, FILE *stream) {
    fprintf(stream, "digraph BST {\n");
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
