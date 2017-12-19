//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright © 2016年 lee. All rights reserved.
//

#include "Header.h"
#include "Header.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    int test[5];
    cin >> test[0]
    >> test[1]
    >> test[2]
    >> test[3]
    >> test[4];

    int max = MAX;
    int min = MIN;

    /*
     * test Object-like Macros
     */
    cout << max << endl;
    cout << min << endl;

    int result;
    /*
     * test Macro Arguments
     */
    // get large number
    result = max(test[0], test[1]);
    cout << test[0] << " and " << test[1] << ": "
    << result << " is large." << endl;

    result = max(test[0] + test[4], test[1]);
    cout << test[0] + test[4] << " and " << test[1] << ": "
    << result << " is large." << endl;

    result = max(test[0], test[1] + test[4]);
    cout << test[0] << " and " << test[1] + test[4] << ": "
    << result << " is large." << endl;

    // square a number
    result = square(test[2]);
    cout << test[2] << " square: " << result << endl;
    result = square(test[2] + test[3]);
    cout << test[2] + test[3] << " square: " << result << endl;

    /*
     * test Concatenation
     */
    // two argument, first is
    result = e(3, 4);
    cout << result << endl;

    /* 
     * test Stringification
     */
    // something to string
    string s;
    s = str(xixihaha);
    cout << s << endl;

    s = str(result);
    cout << s << endl;

    string t;
    t = mstr(MAX);
    cout << t << endl;

    int x = 0;
    WARN_IF(x == 0);
    WARN_IF(x != 0);

    return 0;
}
