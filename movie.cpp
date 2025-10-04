#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;


Movie::Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) 
: Product("movie", name, price, qty), genre_(genre),rating_(rating)
{

}

Movie::~Movie()
{

}


std::set<std::string> Movie::keywords() const
{
  // Name and Genre are searchable keywords, make a set containing name-keywords
  std::set<std::string> wordSet = parseStringToWords(name_);
  // Make a set containing genre-keywords
  std::set<std::string> addWord = parseStringToWords(genre_);
  // Combine two sets
  wordSet.insert(addWord.begin(), addWord.end());
  
  return wordSet;
}

std::string Movie::displayString() const{
  std::ostringstream output;
  output <<  name_ << endl;
  output << "Genre: " << genre_ << " Rating: " << rating_ << endl;
  output << price_ << " " << qty_ << " left." << endl;

  return output.str();
}

void Movie::dump(std::ostream& os) const
{
    os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<"\n" << genre_ << "\n" << rating_<< endl;
}
