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

#ifndef _POLYFEATURES_H
#define _POLYFEATURES_H

#include <vector>
#include <iostream>

// Typedefs
typedef std::vector<unsigned> vtype;
typedef std::vector<vtype> ptableinnertype;

class PTable;

/*
 * FUNCTION PROTOTYPES
 */
void recur(unsigned &, const unsigned &, vtype *, PTable *);
PTable powerTable(unsigned, const unsigned &);
void powerTable(unsigned, const unsigned &, PTable *);

/*
 * PTable
 *
 * Object type for powerTable and recur functions.
 *
 * Members
 * -------
 * t ptableinnertype
 * 		Holds table
 *
 * Methods
 * -------
 * print
 * operator==
 * operator!=
 */
class PTable {
public:
	ptableinnertype t;
	void print() const;
	bool operator==(const PTable &) const;
	bool operator!=(const PTable &) const;
};

/*
 * Print PTable objects
 */
void PTable::print() const {
	for(unsigned l = 0; l < t.size(); l++) {
		for(unsigned m = 0; m < t[l].size(); m++) {
			std::cout << t[l][m] << " ";
		}
		std::cout << std::endl;
	}
}

/*
 * Is calling object equal to pass PTable
 */
bool PTable::operator==(const PTable & p) const {
	for(unsigned l = 0; l < t.size(); l++) {
		for(unsigned m = 0; m < t[l].size(); m++) {
			if(t[l][m] != p.t[l][m])
				return false;
		}
	}
	return true;
}

/*
 * Is calling object not equal to pass PTable
 */
bool PTable::operator!=(const PTable & p) const{
	return !(*this==p);
}

/*
 * powerTable function documented at http://thecjthompson.com/docs/published/polyfeatures.pdf
 * 
 * Args
 * ----
 * N unsigned
 * 		Number of features
 * Q unsigned
 *		Max power for EPS (defined in polyfeatures.pdf)
 * 
 * Returns
 * -------
 * PTable containing all combination of EPS from 1 to Q
 */
PTable powerTable(unsigned N, const unsigned & Q) {
    PTable pt = PTable();
    vtype v = vtype(N);
    unsigned N2;
    for(unsigned i = 0; i < N-1; i++)
        for(unsigned p = 1; p <= Q; p++) {
            v[i] = 1;
            v[N-1] = p - 1;
            pt.t.push_back(v);
            N2 = N-1;
            recur(N2, i, &v, &pt);
            v = vtype(N);
        }
    for(unsigned p = 1; p <= Q; p++) {
        v[N-1] += 1;
        pt.t.push_back(v);
    }
    return pt;
}

/*
 * Overloaded powerTable function listed above.
 * Passes PTable address for more efficiency.
 * 
 * Args
 * ----
 * See Above...
 * pt PTable Address
 *		Address of empty PTable
 */
void powerTable(unsigned N, const unsigned & Q, PTable * pt) {
    vtype v = vtype(N);
    unsigned N2;
    for(unsigned i = 0; i < N-1; i++)
        for(unsigned p = 1; p <= Q; p++) {
            v[i] = 1;
            v[N-1] = p - 1;
            pt->t.push_back(v);
            N2 = N-1;
            recur(N2, i, &v, pt);
            v = vtype(N);
        }
    for(unsigned p = 1; p <= Q; p++) {
        v[N-1] += 1;
        pt->t.push_back(v);
    }
}

/*
 * Recursive procedure for powerTable.
 * 
 * Args
 * ----
 * a unsigned
 * s unsigned
 * vec vtype Address
 * table PTable Address
 */
void recur(unsigned & a, const unsigned & s, vtype * vec, PTable * table) {
	if(a == s)
		return;
	if((*vec)[a] == 0) {
		--a;
		recur(a, s, vec, table);
	}
	else {
		(*vec)[a] -= 1;
		(*vec)[a-1] += 1;
		table->t.push_back(*vec);
		recur(a, s, vec, table);
	}
}

#endif
