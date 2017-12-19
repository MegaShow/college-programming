#ifndef _BOOKITEM_H_
#define _BOOKITEM_H_
 #include <iostream>
using std::string;
 class BookItem {
 public:
  BookItem(const string& bookName, double salesPrice);
   /* Return the name of the book */
  string getName() const;
   /* 
   * Return the total price of these books
   * total price: cnt * price
   */
  double netPrice(int cnt) const;
  protected:
  double price_;  // The price of the book
  private:
  string name_;  // The name of the book
};
 #endif  // _BOOKITEM_H_
 