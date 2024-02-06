/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    if (subRoot == nullptr){
        return;
    }

    //typename BinaryTree<T>::
    Node* temp = nullptr;

    temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;

    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    return isOrdered(root, nullptr, nullptr);
}

template <typename T>
bool BinaryTree<T>::isOrdered(Node* subRoot, Node* temp_left, Node* temp_right) const
{
    if (subRoot != nullptr){
        bool retval = true;
    
        // four conditions for a certain subRoot to be ordered
        if ((temp_left != nullptr) && (subRoot->left != nullptr)){
            retval = retval && (subRoot->left->elem >= temp_left->elem);
        }

        if ((temp_right != nullptr) && (subRoot->right != nullptr)){
            retval = retval && (subRoot->right->elem <= temp_right->elem);
        }

        if (subRoot->left != nullptr){
            retval = retval && (subRoot->left->elem <= subRoot->elem);
        }

        if (subRoot->right != nullptr){
            retval = retval && (subRoot->right->elem >= subRoot->elem);
        }

        return (retval && isOrdered(subRoot->left, temp_left, subRoot) && isOrdered(subRoot->right, subRoot, temp_right));

    }

    return true;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> temp;
    printPaths(paths, root, temp);
}

template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, Node* subRoot, vector<T> temp) const
{
    if (subRoot->left != nullptr && subRoot->right != nullptr){
        temp.push_back(subRoot->elem);
        printPaths(paths, subRoot->left, temp);
        printPaths(paths, subRoot->right, temp);
    }

    if (subRoot->left == nullptr && subRoot->right == nullptr){
        temp.push_back(subRoot->elem);
        paths.push_back(temp);
    }

    if (subRoot->left == nullptr && subRoot->right != nullptr){
        temp.push_back(subRoot->elem);
        printPaths(paths, subRoot->right, temp);
    }

    if (subRoot->left != nullptr && subRoot->right == nullptr){
        temp.push_back(subRoot->elem);
        printPaths(paths, subRoot->left, temp);
    }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    int curr = -1;
    return sumDistances(root, sum, curr);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* subRoot, int& sum, int curr) const
{
    if (subRoot == nullptr) {
        return 0;
    }

    curr++;

    if (subRoot->left == nullptr && subRoot->right == nullptr) {
        return curr;
    } else {
        return (sum + curr + sumDistances(subRoot->left, sum, curr) + sumDistances(subRoot->right, sum, curr));
    }
}
