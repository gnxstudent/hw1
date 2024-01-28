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
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  if (tail_ == nullptr || tail_->last == ARRSIZE) {
    // Create a new item and set it as the tail
    Item* newItem = new Item();
    if (tail_ == nullptr) {
      head_ = newItem;
    } else {
      tail_->next = newItem;
      newItem->prev = tail_;
    }
    tail_ = newItem;
  }
  
  // Add the value to the current tail item
  tail_->val[tail_->last] = val;
  ++tail_->last;
  ++size_;
}

void ULListStr::pop_back()
{
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  
  if (tail_->last == 0) {
    // If the current tail is empty, remove it
    Item* temp = tail_;
    tail_ = tail_->prev;
    if (tail_ == nullptr) {
      head_ = nullptr;
    } else {
      tail_->next = nullptr;
    }
    delete temp;
  } else {
    // Simply decrement the last index to remove the last value
    --tail_->last;
  }
  --size_;
}

void ULListStr::pop_front()
{
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  
  if (head_->first == ARRSIZE - 1) {
    // If the current head is fully occupied, remove it
    Item* temp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
      tail_ = nullptr;
    } else {
      head_->prev = nullptr;
    }
    delete temp;
  } else {
    // Simply increment the first index to remove the first value
    ++head_->first;
  }
  --size_;
}

std::string const & ULListStr::back() const
{
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_) {
    return nullptr;
  }
  
  // Traverse the list to find the item containing the desired location
  Item* current = head_;
  while (loc >= (current->last - current->first)) {
    loc -= (current->last - current->first);
    current = current->next;
  }
  
  // Return a pointer to the element at the specified location
  return &(current->val[current->first + loc]);
}

void ULListStr::push_front(const std::string& val)
{
  if (head_ == nullptr || head_->first == 0) {
    // Create a new item and set it as the head
    Item* newItem = new Item();
    if (head_ == nullptr) {
      tail_ = newItem;
    } else {
      head_->prev = newItem;
      newItem->next = head_;
    }
    head_ = newItem;
  }
  
  // Add the value to the current head item
  --head_->first;
  head_->val[head_->first] = val;
  ++size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
