//
// Created by Moaz Alhabbal on 3/17/16.
//

#ifndef PROJECT1_TREES_AVL_H
#define PROJECT1_TREES_AVL_H

#include <stdio.h>

class AVL {
public:
    int data;
    AVL *left;
    AVL *right;
    int height;
    int number;

};

bool search_AVL(AVL *avl, int data) {

    if (avl == NULL)
        return false;
    else if (avl->data == data)
        return true;
    else if (avl->data > data)
        return search_AVL(avl->left, data);
    else
        return search_AVL(avl->right, data);
}

int size(AVL *tree) {
    if (tree == NULL)
        return 0;
    return tree->number;

}

int heightAVL(AVL *tree) {
    if (tree == NULL)
        return -1;

    return tree->height;
}

int isBalanced(AVL *tree) {
    return heightAVL(tree->left) - heightAVL(tree->right);
}

int MAX(int a, int b) {
    if (a > b)
        return a;
    else if (b > a)
        return b;
    else return a;
}

AVL *rotateRight(AVL *tree) {

    AVL *node = tree->left;
    tree->left = node->right;
    node->right = tree;
    node->number = tree->number;
    tree->number = 1 + size(tree->left) + size(tree->right);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    node->height = 1 + MAX(heightAVL(node->left), heightAVL(node->right));

    return node;
}

AVL *rotateLeft(AVL *tree) {

    AVL *node = tree->right;
    tree->right = node->left;
    node->left = tree;
    node->number = tree->number;
    tree->number = 1 + size(tree->left) + size(tree->right);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    node->height = 1 + MAX(heightAVL(node->left), heightAVL(node->right));

    return node;
}

AVL *balance(AVL *tree) {

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

AVL *createNode_AVL(int data) {

    AVL *node = new AVL();
    node->data = data;
    node->left = node->right = NULL;
    node->height = 0;
    node->number = 1;

    return node;
}

AVL *insert_AVL(AVL *tree, int data) {

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

    tree->number = 1 + size(tree->left) + size(tree->right);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));

    return balance(tree);
}

void traverse_AVL_INORDER(AVL *tree) {

    if (tree == NULL)
        return;

    traverse_AVL_INORDER(tree->left);
    printf("%d ", tree->data);
    traverse_AVL_INORDER(tree->right);
}

AVL *MIN(AVL *tree) {
    if (tree->left == NULL) return tree;

    return MIN(tree->left);
}

AVL *deleteMin(AVL *tree) {
    if (tree->left == NULL)
        return tree->right;
    tree->left = deleteMin(tree->left);
    tree->number = 1 + size(tree->left) + size(tree->right);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));
    return balance(tree);
}

AVL *deleteNode(AVL *tree, int data) {
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
            AVL *node = tree;
            tree = MIN(node->right);
            tree->right = deleteMin(node->right);
            tree->left = node->left;
        }
    }
    tree->number = 1 + size(tree->left) + size(tree->right);
    tree->height = 1 + MAX(heightAVL(tree->left), heightAVL(tree->right));

    return balance(tree);
}


void AVL_print_dot_null(int key, int nullcount, FILE *stream) {
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void AVL_print_dot_aux(AVL *node, FILE *stream) {
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

void AVL_print_dot(AVL *tree, FILE *stream) {
    fprintf(stream, "digraph BST {\n");
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
