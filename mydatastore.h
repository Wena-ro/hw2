#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iomanip>
#include "product.h"
#include "user.h"
#include "datastore.h"



class MyDataStore : public DataStore{
public:
    MyDataStore();
    virtual ~MyDataStore() override;

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    void addToCart(const std::string& userName, int hitIndex);

    void viewCart(const std::string& userName) const;

    void buyCart(const std::string& userName);

    private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::vector<Product*>> carts_;
    std::map<std::string, std::set<Product*>> keywordList_;
    std::vector<Product*> prevHit_;




};

#endif
