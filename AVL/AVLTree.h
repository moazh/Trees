//
// Created by Moaz Alhabbal on 3/17/16.
//

#ifndef PROJECT1_TREES_AVL_H
#define PROJECT1_TREES_AVL_H

#include <stdio.h>

class AVLTree {
public:
    int data;
    AVLTree *left;
    AVLTree *right;
    int height;

};

bool search_AVL(AVLTree *avl, int data) {

    if (avl == NULL)
        return false;
    else if (avl->data == data)
        return true;
    else if (avl->data > data)
        return search_AVL(avl->left, data);
    else
        return search_AVL(avl->right, data);
}



int heightAVL(AVLTree *tree) {
    if (tree == NULL)
        return -1;

    return tree->height;
}

int isBalanced(AVLTree *tree) {
    return heightAVL(tree->left) - heightAVL(tree->right);
}

int MAX(int a, int b) {
    if (a > b)
        return a;
    else if (b > a)
        return b;
    else return a;
}

AVLTree *rotateRight(AVLTree *tree) {

    AVLTree *node = tree->left;
    tree->left = node->right;
    node->right = tree;
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    node->height = 1 + MAX(heightAVL(node->left), heightAVL(node->right));

    return node;
}

AVLTree *rotateLeft(AVLTree *tree) {

    AVLTree *node = tree->right;
    tree->right = node->left;
    node->left = tree;
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    node->height = 1 + MAX(heightAVL(node->left), heightAVL(node->right));

    return node;
}

AVLTree *balance(AVLTree *tree) {

    if (isBalanced(tree) < -1) {
        if (isBalanced(tree->right) > 0) {
            tree->right = rotateRight(tree->right);
        }
        tree = rotateLeft(tree);
    }
    else if (isBalanced(tree) > 1) {
        if (isBalanced(tree->left) < 0) {
            tree->left = rotateLeft(tree->left);
        }
        tree = rotateRight(tree);
    }
    return tree;
}

AVLTree *createNode_AVL(int data) {

    AVLTree *node = new AVLTree();
    node->data = data;
    node->left = node->right = NULL;
    node->height = 0;

    return node;
}

AVLTree *insert_AVL(AVLTree *tree, int data) {

    if (tree == NULL)
        tree = createNode_AVL(data);
    else if (tree->data > data)
        tree->left = insert_AVL(tree->left, data);
    else if (tree->data < data)
        tree->right = insert_AVL(tree->right, data);
    else {
        tree->data = data;
        return tree;
    }

    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));

    return balance(tree);
}

void traverse_AVL_INORDER(AVLTree *tree) {

    if (tree == NULL)
        return;

    traverse_AVL_INORDER(tree->left);
    printf("%d ", tree->data);
    traverse_AVL_INORDER(tree->right);
}

AVLTree *MIN(AVLTree *tree) {
    if (tree->left == NULL) return tree;

    return MIN(tree->left);
}

AVLTree *deleteMin(AVLTree *tree) {
    if (tree->left == NULL)
        return tree->right;
    tree->left = deleteMin(tree->left);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    return balance(tree);
}

AVLTree *deleteNode(AVLTree *tree, int data) {
    if (tree == NULL)
        return tree;
    else if (tree->data > data)
        tree->left = deleteNode(tree->left, data);
    else if (tree->data < data)
        tree->right = deleteNode(tree->right, data);

    else {
        if (tree->left == NULL) {
            return tree->right;
        }
        else if (tree->right == NULL) {
            return tree->left;
        }
        else {
            AVLTree *node = tree;
            tree = MIN(node->right);
            tree->right = deleteMin(node->right);
            tree->left = node->left;
        }
    }
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));

    return balance(tree);
}


void AVL_print_dot_null(int key, int nullcount, FILE *stream) {
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void AVL_print_dot_aux(AVLTree *node, FILE *stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->left->data);
        AVL_print_dot_aux(node->left, stream);
    }
    else
        AVL_print_dot_null(node->data, nullcount++, stream);

    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->right->data);
        AVL_print_dot_aux(node->right, stream);
    }
    else
        AVL_print_dot_null(node->data, nullcount++, stream);
}

void AVL_print_dot(AVLTree *tree, FILE *stream) {
    fprintf(stream, "digraph BSTTree {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->data);
    else
        AVL_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}


#endif //PROJECT1_TREES_AVL_H
