#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
: Product("clothing", name, price, qty), size_(size),brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
  // Name and brand are searchable keywords, make a set containing name-keywords
  std::set<std::string> wordSet = parseStringToWords(name_);
  // Make a set containing gbrand-keywords
  std::set<std::string> addWord = parseStringToWords(brand_);
  // Combine two sets
  wordSet.insert(addWord.begin(), addWord.end());
  
  return wordSet;
}

std::string Clothing::displayString() const
{
  std::ostringstream output;
  output <<  name_ << endl;
  output << "Size: " << size_ << " Brand: " << brand_ << endl;
  output << price_ << " " << qty_ << " left." << endl;

  return output.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << size_ << "\n" << brand_<< endl;
}

