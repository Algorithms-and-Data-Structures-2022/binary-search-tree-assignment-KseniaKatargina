#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key,value,root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key,root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key,root_);
    if(node != nullptr){
      return (*node).value;
    } else {
      return std::nullopt;
    }
  }

  bool BinarySearchTree::Contains(int key) const {
    if(Find(key) == std::nullopt) {
      return false;
    }
    return true;
  }

  bool BinarySearchTree::IsEmpty() const {
    return (root_ == nullptr);
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if(root_ == nullptr) {
      return std::nullopt;
    }
    return find_min(root_)->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if(root_ == nullptr) {
      return std::nullopt;
    }
    return find_max(root_)->value;
  }

  Node* BinarySearchTree::root() const {
    if(root_ == nullptr) {
      return nullptr;
    }
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if(node == nullptr){
      Node* n = new Node(key, value);
      node = n;
      (*node).right = nullptr;
      (*node).left = nullptr;
    }
    if(key > (*node).key){
      if((*node).right == nullptr){
        (*node).right = new Node(key, value);
      } else {
        insert(key, value, (*node).right);
      }
    }
    if(key < (*node).key){
      if((*node).left == nullptr){
        (*node).left = new Node(key, value);
      } else {
        insert(key, value, (*node).left);
      }
    }
    if(key == (*node).key){
      (*node).value = value;
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if(node == nullptr){
      return false;
    }
    if(!Contains(key)){
      return false;
    }
    if(key > (*node).key) {
      remove(key, (*node).right);
    } else if (key < (*node).key) {
      remove(key,(*node).left);
    } else {
      if((*node).left == nullptr && (*node).right == nullptr){
        delete node;
        node = nullptr;
        return true;
      } else if ((*node).left == nullptr){
        node = (*node).right;
        (*node).right = nullptr;
        return true;
      } else if((*node).right == nullptr){
        node = (*node).left;
        (*node).left = nullptr;
        return true;
      } else if ((*node).left != nullptr && (*node).right != nullptr){
        Node* min = find_min((*node).right);
        (*node).key = (*min).key;
        (*node).value = (*min).value;
        return remove((*min).key,(*node).right);
      }
    }

  }

  void BinarySearchTree::clear(Node* node) {
    if(node == nullptr){
      return;
    }
    clear((*node).left);
    clear((*node).right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if(node == nullptr) {
      return nullptr;
    } else if( key < (*node).key){
      return find(key,(*node).left);
    } else if(key > (*node).key){
      return find(key, (*node).right);
    }else if(key == (*node).key){
      return node;
    }
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if(node == nullptr) {
      return nullptr;
    }
    if((*node).left == nullptr){
      return node;
    }
    return find_min((*node).left);
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if(node == nullptr) {
      return nullptr;
    }
    if((*node).right == nullptr){
      return node;
    }
    return find_max((*node).right);
  }

}  // namespace assignment