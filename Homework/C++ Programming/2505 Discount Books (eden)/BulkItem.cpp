 // MegaShow
#include "BulkItem.h"

BulkItem::BulkItem(const string &bookName, double salesPrice,
         int qty, double salesDisc) : BookItem(bookName, salesPrice) {
    minQty_ = qty;
    discount_ = salesDisc;
}
/*
   * Return the total price of these books
   * If cnt is greater than minQty, total price: cnt * price * discount
   * else, total price: cnt * price
   */
double BulkItem::netPrice(int cnt) const {
    if(cnt > minQty_) {
        return cnt * price_ * discount_;
    }
    else {
        return cnt * price_;
    }
}
