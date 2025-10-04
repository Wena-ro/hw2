#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;


Book::Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author) 
: Product("book", name, price, qty), isbn_(isbn), author_(author)
{

}

Book::~Book()
{

}


std::set<std::string> Book::keywords() const
{
  // Name, author, isbn are searchable keywords, make a set containing name-keywords
  std::set<std::string> wordSet = parseStringToWords(name_);
  // Make a set containing author-keywords
  std::set<std::string> addWord = parseStringToWords(author_);
  // Combine two sets
  wordSet.insert(addWord.begin(), addWord.end());
  // Add isbn
  wordSet.insert(isbn_);
  
  return wordSet;
}

std::string Book::displayString() const
{
  std::ostringstream output;
  output <<  name_ << endl;
  output << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  output << price_ << " " << qty_ << " left." << endl;

  return output.str();
}


void Book::dump(std::ostream& os) const
{
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << isbn_ << "\n" << author_<< endl;
}