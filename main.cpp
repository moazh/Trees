#include <iostream>

#include "Timer.h"
#include "RedBlack_Tree/RedBlack.h"
#include "AVL_Tree/AVL.h"
#include "BST_Tree/BST.h"

#include <fstream>
#include <sstream>

using namespace std;

int main() {


    static bool insert_val, find_val, delete_val = false;
    static bool isLetter = true;
    static double time_RedBlack, time_AVL;

    Timer timer_RedBlack, timer_AVL;


    std::string line;
    std::ifstream infile("Tree.txt");
    ofstream myfile("Tree.txt");

    if (myfile.is_open()) {
        myfile << "i 1 i 2 i 4 i 7 i 9 i 600  i 230 \n i 111 \n i 222 i 309";

    }
    myfile.close();

    RedBlack *Red_tree;
    AVL *Avl_tree;
    BST *BST_tree;

    while (std::getline(infile, line))  // this does the checking!
    {
        std::istringstream iss(line);
        string c;

        while (iss >> c) {

            int value = atoi(c.c_str());

            if (isLetter) {

                if (c == "i") {
                    insert_val = true;
                    find_val, delete_val = false;
                }
                if (c == "f") {
                    find_val = true;
                    delete_val, insert_val = false;
                }
                if (c == "d") {
                    delete_val = true;
                    insert_val, find_val = false;
                }
                isLetter = false;
            }

            else {
                isLetter = true;

                if (insert_val) {

                    timer_RedBlack.reset();
                    Red_tree = insert(Red_tree, value);
                    time_RedBlack += timer_RedBlack.elapsed();


                    timer_AVL.reset();
                    Avl_tree = insert_AVL(Avl_tree, value);
                    time_AVL += timer_AVL.elapsed();

                    BST_tree = insert(BST_tree, value);

                    insert_val = false;
                }
                if (find_val) {

                    timer_RedBlack.reset();
                    search(Red_tree, value);
                    time_RedBlack += timer_RedBlack.elapsed();

                    timer_AVL.reset();
                    search_AVL(Avl_tree, value);
                    time_AVL += timer_AVL.elapsed();

                    find_val = false;
                }
                if (delete_val) {

                    timer_RedBlack.reset();
                    Red_tree = deleteNode(Red_tree, value);
                    time_RedBlack += timer_RedBlack.elapsed();

                    timer_AVL.reset();
                    Avl_tree = deleteNode(Avl_tree, value);
                    time_AVL += timer_AVL.elapsed();


                    delete_val = false;
                }
            }
        }
    }
    infile.close();

    cout << "\n";
    cout << "\n";
    traverse_RedBlack_INORDER(Red_tree);

    cout << "\n";

    traverse_AVL_INORDER(Avl_tree);

    cout << "\n";
    cout << "\n";
    cout << "\n";

    cout << "RBTree " << time_RedBlack;

    cout << "\n";
    cout << "\n";

    cout << "AVLTree " << time_AVL;

    cout << "\n";
    cout << "\n";


    FILE *file1, *file2, *file3;
    file1 = fopen("RBtree_dot.txt", "w");
    file2 = fopen("AVLtree_.txt", "w");
    file3 = fopen("BSTtree_dot.txt", "w");

    RB_print_dot(Red_tree, file1);
    AVL_print_dot(Avl_tree, file2);
    BST_print_dot(BST_tree, file3);


    fclose(file1);
    fclose(file2);
    fclose(file3);


    //debug
    int tt = 0;

    return 0;
}
