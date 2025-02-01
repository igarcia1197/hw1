#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return (size_ == 0);
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::clear()
{
  Item* temp = head_;
  while(temp != NULL){
    Item* next = temp->next;
    delete temp;
    temp = next;
  }
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}


void ULListStr::push_back(const std::string& val)
{
  // If list is empty create a new node
  if(head_ == NULL) {
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;  // last is exclusive so 1 means one element used
    head_ = newItem;
    tail_ = newItem;
    size_ = 1;
    return;
  }

  // If there is space in the tail node
  if(tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }
  else {
    // Need a new node
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;
    // Link it into the list
    tail_->next = newItem;
    newItem->prev = tail_;
    tail_ = newItem;
    size_++;
  }
}

void ULListStr::pop_back()
{
  if(empty()) {
    // List is empty nothing to pop return nothing 
    return;
  }
  // tail_->last is exclusive index of last used element
  tail_->last--;
  size_--;

  // If the tail node becomes empty then weremove it
  if(tail_->first == tail_->last) {
    // If there is only one node
    if(head_ == tail_) {
      delete tail_;
      head_ = NULL;
      tail_ = NULL;
    }
    else {
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = NULL;
      delete temp;
    }
  }
}

void ULListStr::push_front(const std::string& val)
{
  // If list is empty create a new node
  if(head_ == NULL) {
    Item* newItem = new Item();
    newItem->val[0] = val;
    newItem->first = 0;
    newItem->last = 1;
    head_ = newItem;
    tail_ = newItem;
    size_ = 1;
    return;
  }

  // If there is space before head_->first we an use it 
  if(head_->first > 0) {
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  }
  else {
    // Allocate a new node at the front
    Item* newItem = new Item();
    // place the new value at the end of this new array chunk
    newItem->val[ARRSIZE-1] = val;
    newItem->first = ARRSIZE-1;
    newItem->last = ARRSIZE;
    // Link it together
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
    size_++;
  }
}

void ULListStr::pop_front()
{
  if(empty()) {
    // Nothing to pop
    return;
  }

  // The front item is at head_->first
  head_->first++;
  size_--;

  // If the head node becomes empty remove it
  if(head_->first == head_->last) {
    // If there is only one node
    if(head_ == tail_) {
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else {
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = NULL;
      delete temp;
    }
  }
}



std::string const & ULListStr::back() const
{
  if(empty()) {
    throw std::runtime_error("List is empty in back()");
  }
  // The back element is at tail_->val[tail_->last - 1]
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if(empty()) {
    throw std::runtime_error("List is empty in front()");
  }
  // The front element is at head_->val[head_->first]
  return head_->val[head_->first];
}



void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location in set()");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location in get()");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr =getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location in const get()");
  }
  return *ptr;
}


std::string* ULListStr::getValAtLoc(size_t loc) const
{
  // If out of range, return NULL
  if(loc >=size_) {
    return NULL;
  }
  // bo through the linked list until we find the chunk containing index loc
  Item* curr = head_;
  while(curr != NULL) {
    size_t numInNode = curr->last - curr->first; // how many elements in this node
    if(loc < numInNode) {
      // The element is in this current  node
      return &curr->val[curr->first +loc];
    }
    // skip this node and adjust loc
    loc -= numInNode;
    curr = curr->next;
  }
  return NULL; // Should not happen if loc < size_
}
