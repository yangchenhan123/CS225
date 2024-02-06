/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/** * This function compares first point to second point to see if first point is smaller in current dimension **/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim >= Dim || curDim < 0){return false;}
    if(first[curDim] < second[curDim]){return true;}
    else if(first[curDim] == second[curDim]){return (first < second);}
    else{return false;}
}

/** * This function calculate the distance of currentBest and potential to the target, if potential is smaller, return true **/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
  double dist1 = 0;
  double dist2 = 0;
  for(int i = 0; i < Dim; i++){
    dist1 += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
    dist2 += (target[i] - potential[i]) * (target[i] - potential[i]);
  }
  if(dist1 == dist2){return (potential < currentBest);}
  return dist1 > dist2;
}

/** * This function quickly find the n-th smallest int in the vector and put it to pivot place **/
template <int Dim>
void KDTree<Dim>::quick_select(int left, int right, int pivot, int curDim){
  while(left != right){
    swap_(points, right, pivot);
    int store = left;
    for(int i = left; i < right; i++){
      if(smallerDimVal(points[i], points[right], curDim)){
        swap_(points, i, store);
        store++;
      }
    }
    swap_(points, store, right);
    if(store == pivot){return;}
    else if(store < pivot){left = store + 1;}  
    else{right = store - 1;}
  }
}

/** * This function swap a-th and b-th element in a vector **/
template <int Dim>
void KDTree<Dim>::swap_(vector<Point<Dim>> &vec, int a, int b){
  Point<Dim> temp = vec[a];
  vec[a] = vec[b];
  vec[b] = temp;
}

/** * This function is a helper functions for constructor, which will help to build a tree from the root node **/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int left, int right, int curDim){
  if(left > right){return nullptr;}
  int pivot = (left + right) / 2;
  quick_select(left, right, pivot, curDim);
  KDTreeNode* node = new KDTreeNode(points[pivot]);
  node->left = buildTree(left, pivot - 1, (curDim + 1) % Dim);
  node->right = buildTree(pivot + 1, right, (curDim + 1) % Dim);
  return node;
}

/** * This function returns size of a KDtree **/
template <int Dim>
size_t KDTree<Dim>::getSize() const{
  return size;
}

/** * This function returns points of a KDtree **/
template <int Dim>
vector<Point<Dim>> KDTree<Dim>::getPoints() const{
  return points;
}

/** * This function is a helper function for copy constructor **/
template <int Dim>
void KDTree<Dim>::copy_(const KDTree<Dim> & other){
  //points = other.getPoints();
  points = other.points;
  //size = other.getSize();
  size = other.size;
  root = buildTree(0, points.size() - 1, 0);
}

/** * This function is a helper function for destructor, it tear down the tree **/
template <int Dim>
void KDTree<Dim>::delete_tree(KDTree<Dim>::KDTreeNode* curr){
  if(curr != nullptr){
    delete_tree(curr->left);
    delete_tree(curr->right);
    delete curr;
    curr = nullptr;
  }
}

/** * another helper function for destructor function, tear down a tree, and clean the vector point **/
template <int Dim>
void KDTree<Dim>::delete_(){
  delete_tree(root);
  points.clear();
  size = 0;

}

/** * This function builds a new KDtree based on the newPoints set **/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  points = newPoints;
  root = buildTree(0, points.size() - 1, 0);
  size = points.size();
}

/** * copy constructor **/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  copy_(other);
}

/** * operator overload function **/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if (*this != rhs){
    delete_();
    copy_(rhs);
  }
  return *this;
}

/** * destructor **/
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete_();
}

/** * This function finds the nearest neighbor to query that's in the KDtree **/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor_helper(query, root, 0);
}
/** * This function calculate the distance of one node in the tree to another node in the tree **/
template <int Dim>
double KDTree<Dim>::dist(const Point<Dim>& p1, const Point<Dim>& p2) const{
  double dist = 0;
  for(int i = 0; i < Dim; i++){dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);}
  return dist;
}

/** * This function  is a helper function for findNearestNeighbor, it is called recursively to traversal all the nodes along the path **/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_helper(const Point<Dim>& query, typename KDTree<Dim>::KDTreeNode* curr, int curDim) const{
  if(curr->left == nullptr && curr->right == nullptr){return curr->point;}
  Point<Dim> current = curr->point;
  Point<Dim> next = curr->point;
  bool store = smallerDimVal(query, curr->point, (curDim % Dim));
  if(!smallerDimVal(query, current, (curDim % Dim)) && curr->right != nullptr){
    next = findNearestNeighbor_helper(query, curr->right, (curDim + 1) % Dim);
    if(shouldReplace(query, current, next)){current = next;}
  }else if(smallerDimVal(query, current, (curDim % Dim)) && curr->left != nullptr){
    next = findNearestNeighbor_helper(query, curr->left, (curDim + 1) % Dim);
    if(shouldReplace(query, current, next)){current = next;}
  }
  if(dist(query, current) >= ((query[curDim] - curr->point[curDim]) * (query[curDim] - curr->point[curDim]))){
    if(!store && curr->left != nullptr){
      next = findNearestNeighbor_helper(query, curr->left, (curDim + 1) % Dim);
      if(shouldReplace(query, current, next)){current = next;}
    }else if(store && curr->right != nullptr){
      next = findNearestNeighbor_helper(query, curr->right, (curDim + 1) % Dim);
      if(shouldReplace(query, current, next)){current = next;}
    }
  }
  return current;
}