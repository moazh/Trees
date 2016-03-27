//
// Created by Moaz Alhabbal on 3/17/16.
//

#ifndef PROJECT1_TREES_REDBLACK_H
#define PROJECT1_TREES_REDBLACK_H

#include <stdio.h>


static bool RED = true;
static bool BLACK = false;

class RedBlack {
public:
    int data;
    RedBlack *left, *right;
    bool color;

};

bool search(RedBlack *tree, int data) {

    if (tree == NULL)
        return false;
    else if (tree->data == data)
        return true;
    else if (tree->data > data)
        return search(tree->right, data);
    else
        return search(tree->left, data);
}

void flipColors(RedBlack *tree) {

    tree->color = !tree->color;
    tree->left->color = !tree->left->color;
    tree->right->color = !tree->right->color;

}

RedBlack *rotateLeft(RedBlack *tree) {

    RedBlack *node = tree->right;
    tree->right = node->left;
    node->left = tree;
    node->color = node->left->color;
    node->left->color = true;

    return node;

}

RedBlack *rotateRight(RedBlack *tree) {

    RedBlack *node = tree->left;
    tree->left = node->right;
    node->right = tree;
    node->color = node->right->color;
    node->right->color = true;

    return node;
}

bool isRed(RedBlack *tree) {

    if (tree == NULL)
        return false;

    return tree->color;
}

RedBlack *createNode(int data) {

    RedBlack *node = new RedBlack();
    node->data = data;
    node->left = node->right = NULL;
    node->color = true;


    return node;
}

RedBlack *insert(RedBlack *tree, int data) {

    if (tree == NULL)
        tree = createNode(data);
    if (tree->data > data)
        tree->left = insert(tree->left, data);
    else if (tree->data < data)
        tree->right = insert(tree->right, data);
    else
        tree->data = data;

    if (isRed(tree->right) && (!isRed(tree->left)))
        tree = rotateLeft(tree);
    if (isRed(tree->left) && isRed(tree->left->left))
        tree = rotateRight(tree);
    if (isRed(tree->right) && isRed(tree->left))
        flipColors(tree);

    return tree;

}

void traverse_RedBlack_INORDER(RedBlack *tree) {

    if (tree == NULL)
        return;

    traverse_RedBlack_INORDER(tree->left);
    printf("%d ", tree->data);
    traverse_RedBlack_INORDER(tree->right);

}

void RB_print_dot_null(int key, int nullcount, FILE *stream) {
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", key, nullcount);
}

void RB_print_dot_aux(RedBlack *node, FILE *stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->left->data);
        RB_print_dot_aux(node->left, stream);
    }
    else
        RB_print_dot_null(node->data, nullcount++, stream);

    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->data, node->right->data);
        RB_print_dot_aux(node->right, stream);
    }
    else
        RB_print_dot_null(node->data, nullcount++, stream);
}

void RB_print_dot(RedBlack *tree, FILE *stream) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->data);
    else
        RB_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}


RedBlack *moveRedLeft(RedBlack *tree) {

    flipColors(tree);
    if (isRed(tree->right->left)) {
        tree->right = rotateRight(tree->right);
        tree = rotateLeft(tree);
        flipColors(tree);
    }
    return tree;
}

RedBlack *moveRedRight(RedBlack *tree) {
    flipColors(tree);
    if (isRed(tree->left->left)) {
        tree = rotateRight(tree);
        flipColors(tree);
    }
    return tree;
}

RedBlack *balance(RedBlack *tree) {

    if (tree == NULL)
        return NULL;
    else {
        if (isRed(tree->right))
            tree = rotateLeft(tree);
        if (isRed(tree->left) && isRed(tree->left->left))
            tree = rotateRight(tree);
        if (isRed(tree->left) && isRed(tree->right))
            flipColors(tree);
    }
    return tree;
}

RedBlack *deleteMin(RedBlack *tree) {
    if (tree->left == NULL)
        return NULL;

    if (!isRed(tree->left) && !isRed(tree->left->left))
        tree = moveRedLeft(tree);

    tree->left = deleteMin(tree->left);
    return balance(tree);
}

RedBlack *MIN(RedBlack *tree) {
    // assert x != null;
    if (tree->left == NULL)
        return tree;

    return MIN(tree->left);
}

RedBlack *deleteNode(RedBlack *tree, int data) {

    if (tree == NULL)
        return tree;
    else if (tree->data > data) {
        if (!isRed(tree->left) && !isRed(tree->left->left))
            tree = moveRedLeft(tree);
        tree->left = deleteNode(tree->left, data);
    }
    else {
        if (isRed(tree->left))
            tree = rotateRight(tree);
        if (tree->data == data && (tree->right == NULL))
            return NULL;
        if (!isRed(tree->right) && !isRed(tree->right->left))
            tree = moveRedRight(tree);
        if (tree->data == data) {
            RedBlack *node = MIN(tree->right);
            tree->data = node->data;
            tree->right = deleteMin(tree->right);
        } else tree->right = deleteNode(tree->right, data);
    }

    return balance(tree);
}


#endif //PROJECT1_TREES_REDBLACK_H