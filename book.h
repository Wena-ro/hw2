#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book: public Product {
public:
    Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);
    ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;


private:
    std::string isbn_;
    std::string author_;
};
#endif
