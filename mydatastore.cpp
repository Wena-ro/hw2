#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include "util.h"

using namespace std;
MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
  for (size_t i = 0; i < products_.size(); ++i) {
    delete products_[i];
  }

  std::map<std::string, User*>::iterator it;
  for (it = users_.begin(); it != users_.end(); ++it) {
    delete it->second;
  }
}

struct ProductNameLess {
  bool operator()(Product* a, Product* b) const {
    return a->getName() < b->getName();
  }
};

void MyDataStore::addProduct(Product* p) {
  if(p == nullptr){
    return;
  }

  products_.push_back(p);

  std::set<std::string> keys = p->keywords();
  for(std::set<std::string>::iterator it = keys.begin(); it != keys.end(); ++it){
    std:: string word = convToLower(*it);
    keywordList_[word].insert(p);
  }

}

void MyDataStore::addUser(User* u){

  if(!u) return;
  std::string uname = convToLower(u->getName());
  users_[uname] = u;

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::vector<Product*> results;

  for(size_t i=0; i < terms.size(); i++){
    terms[i] = convToLower(terms[i]);
  }

  bool isFirstItem = true;
  std::set<Product*> prodSet;

  for(size_t i = 0; i < terms.size();i++){
    string word = terms[i];
    std::set<Product*> prodList;

    std::map<std::string, std::set<Product*>>::iterator it = keywordList_.find(word);
    if(it != keywordList_.end()){
      prodList = it -> second;
    }

    if(isFirstItem){
      prodSet = prodList;
      isFirstItem = false;
    }else{
      if(type == 0){
        prodSet = setIntersection(prodSet,prodList);
      }else if(type == 1){
        prodSet = setUnion(prodSet,prodList);
      }
    }

  }

  results.assign(prodSet.begin(),prodSet.end());

  std::sort(results.begin(), results.end(), ProductNameLess());

  prevHit_ = results;
  return results;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << endl;
  for(size_t i=0; i < products_.size(); i++){
    products_[i] -> dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;

  for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    it -> second -> dump(ofile);
  }

  ofile << "</users>" << endl; 
}


void MyDataStore::addToCart(const std::string& userName, int hitIndex){

  string uname = convToLower(userName);

  if(users_.find(uname) == users_.end()){
    cout << "Invalid request" << endl;
    return;
  }

  if(hitIndex < 1 || hitIndex > (int) prevHit_.size()){
    cout << "Invalid request" << endl;
    return;
  }

  Product* buyItem = prevHit_[hitIndex-1];
  carts_[uname].push_back(buyItem);
  
}

void MyDataStore::viewCart(const std::string& userName) const{
  string uname = convToLower(userName);

  if(users_.find(uname) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }

  std::map<std::string, std::vector<Product*>>::const_iterator it = carts_.find(uname);
  if(it == carts_.end() || it -> second.empty()){
    return;
  }

  const std::vector<Product*>& cartItem = it ->second;
  for(size_t i=0; i < cartItem.size(); i++){
    std::cout << "Item " << (i+1) << std::endl;
    std::cout << cartItem[i]->displayString() << endl;
  }

}

void MyDataStore::buyCart(const std::string& userName){
  string uname = convToLower(userName);

  if(users_.find(uname) == users_.end()){
    cout << "Invalid username" << endl;
    return;
  }


  User* user = users_.find(uname) -> second;
  std::vector<Product*>& cart = carts_[uname];
  std::vector<Product*> left;

  if(cart.empty()){
    return;
  }

  for(size_t i=0; i < cart.size(); i++){
    Product* p = cart[i];
    if(p -> getQty() >0 && user -> getBalance()>= p -> getPrice()){
      user ->deductAmount(p->getPrice());
      p ->subtractQty(1);
    }else{
      left.push_back(p);
    }
  }
  cart = left;
}
