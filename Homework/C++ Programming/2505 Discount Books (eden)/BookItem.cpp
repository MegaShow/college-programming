 // MegaShow
#include <string>
#include "BookItem.h"

BookItem::BookItem(const string &bookName, double salesPrice) {
    name_ = bookName;
    price_ = salesPrice;
}

/* Return the name of the book */
string BookItem::getName() const {
    return name_;
}

/* 
   * Return the total price of these books
   * total price: cnt * price
   */
double BookItem::netPrice(int cnt) const {
    return cnt * price_;
}