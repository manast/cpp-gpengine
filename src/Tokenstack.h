

#ifndef _GP_TOKEN_STACK_H
#define _GP_TOKEN_STACK_H

#include <vector>
#include "Token.h"

using namespace std;

class TokenStack {

public:
	bool empty() const
		{return (c.empty()); }
	int size() const
		{return (c.size()); }
	Token* top()
		{return (c.back()); }
	const Token* top() const
		{return (c.back()); }
	void push(Token* x)
		{c.push_back(x); }
	void pop()
		{c.pop_back(); }
	bool operator==(const TokenStack& x) const
		{return (c == x.c); }
	bool operator!=(const TokenStack& x) const
		{return (!(*this == x)); }
	bool operator<(const TokenStack& x) const
		{return (c < x.c); }
	bool operator>(const TokenStack& x) const
		{return (x < *this); }
	bool operator<=(const TokenStack& x) const
		{return (!(x < *this)); }
	bool operator>=(const TokenStack& x) const
		{return (!(*this < x)); }

    vector <Token*> get_vector () 
        {return c;}
protected:
    vector <Token*> c;
};


#endif