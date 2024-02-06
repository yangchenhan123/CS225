/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    //children of t is changed, so update its height
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->left = t;
    //children of temp is changed, so update its height
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    //children of t is changed, so update its height
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->right = t;
    //children of temp is changed, so update its height
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == nullptr){return;}

    int diff = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if (diff == 2){
        int diff_left = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
        if (diff_left >= 0){rotateRight(subtree);}
        else {rotateLeftRight(subtree);}
    }

    if (diff == -2){
        int diff_right = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
        if (diff_right > 0){rotateRightLeft(subtree);}
        else {rotateLeft(subtree);}
    }

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == nullptr){
        subtree = new Node(key, value);
        return;
    }

    else if(key < subtree->key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    }else{
        insert(subtree->right, key, value);
        rebalance(subtree);
    }

    subtree->height = 1 + ((heightOrNeg1(subtree->left) > heightOrNeg1(subtree->right)) ? heightOrNeg1(subtree->left) : heightOrNeg1(subtree->right));//可放入第一个if中
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == nullptr)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            //delete subtree;
            subtree = nullptr;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while (iop->right != nullptr){
                iop = iop->right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* rem = (subtree->left != nullptr) ? subtree->left : subtree->right;
            swap(subtree, rem);
            subtree->left = subtree->right = nullptr;
            subtree->height = 0;
            delete rem;
            rem = NULL;
        }
        // your code here
    }
}
