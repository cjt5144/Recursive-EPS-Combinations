/*
The MIT License (MIT) Copyright (c) 2016 Christopher Thompson

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "polyfeatures.h"
#include <iostream>
#include <cassert>
/*
 * COMPILE WITH
 * ------------
 * clang++ -std=c++11 -o polyfeatures polyfeaturestest.cpp
 */

int main() {
	using std::cout;
	using std::endl;
	
	PTable ptable = powerTable(3, 2);
	ptable.print();
	cout << endl;
	
	PTable ptable2 = PTable();
	powerTable(3, 2, &ptable2);
	ptable2.print();
	
	cout << endl;
	cout << "assert ptable == ptable2...";
	assert(ptable==ptable2);
	cout << "OK" << endl;
	return 0;
}