
#ifndef _GP_SYMBOL_STACK_H
#define _GP_SYMBOL_STACK_H

#include <vector>
#include "Symbol.h"

using namespace std;

class SymbolStack {

public:
	bool empty() const
		{return (c.empty()); }
	int size() const
		{return (c.size()); }
	Symbol* top()
		{return (c.back()); }
	const Symbol* top() const
		{return (c.back()); }
	void push(Symbol* x)
		{c.push_back(x); }
	void pop()
		{c.pop_back(); }
	bool operator==(const SymbolStack& x) const
		{return (c == x.c); }
	bool operator!=(const SymbolStack& x) const
		{return (!(*this == x)); }
	bool operator<(const SymbolStack& x) const
		{return (c < x.c); }
	bool operator>(const SymbolStack& x) const
		{return (x < *this); }
	bool operator<=(const SymbolStack& x) const
		{return (!(x < *this)); }
	bool operator>=(const SymbolStack& x) const
		{return (!(*this < x)); }

    vector <Symbol*> get_vector () 
        {return c;}
protected:
    vector <Symbol*> c;
};

#endif

