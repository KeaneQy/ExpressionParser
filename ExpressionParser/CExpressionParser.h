#pragma once

#define MY_DEBUG

#include <stdlib.h>

#include <stack>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using std::stack;
using std::string;
using std::vector;
using std::map;
using std::shared_ptr;
using std::make_shared;
using std::find;

#ifdef MY_DEBUG

#include <iostream>
using std::cout;
using std::endl;

#endif // DEBUG

namespace CParser
{
	enum class error
	{
		SUCCESS = 1,
		ILLEGAL_EXP = -1,
		EMPTY_EXP = -2,
		UNKNOWN = -3,
		DIVIDE_BY_ZERO = -4
	};

	enum class elementType
	{
		FUNC = 1,
		NUM,
		OPERTOR,
		POINT,
		NONE
	};

	enum class funcList
	{
		POW = 1,
		SQRT,
		SIN,
		COS,
		TAN,
		NONE
	};

	typedef struct _Node
	{
		string _ele;
		elementType _type;
	}Node;
	typedef shared_ptr<Node> PNode;
	typedef shared_ptr<vector<PNode>> PNodeVec;
	typedef vector<PNode> NodeVec;

	class CExpressionParser
	{
	private:
		string _str_expression;
		PNodeVec _vec_postfix_ptr;
		PNodeVec _vec_infix_ptr;
		map<string, int> _priority = { { "+", 1 },{ "-", 1 },{ "*", 2 },{ "/", 2 },{ "(", 3 },{ ")", 3 } };
		error _error_msg = error::SUCCESS;
	public:
		CExpressionParser();					//constructor
		bool preprocess(string exp);
		void itop();
		double calc_exp_by_postfix();
#ifdef MY_DEBUG
		string getExp();
		void showStack();
#endif // DEBUG
	protected:
		elementType get_element_type(char c);
		double calc_with_operator(double x, double y, char op);
		bool isLegal(string exp);
		bool isParenthesis_left(string ele);
		bool isParenthesis_right(string ele);
		bool isLessEqual(string source, string target);
		bool getElements();
	};
}