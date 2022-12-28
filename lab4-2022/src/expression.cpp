#include "expression.hh"

using namespace std;

string Expression::asPrefix()
{
    string res;
    BST<int, Component>::PrefixIterator it = tree_.prefixBegin();
    while (it) {
        res += (*it).str() + " ";
        ++it;
    }
    return res;
}

string Expression::asInfix()
{
    BST<int, Component>::InfixIterator it = tree_.infixBegin();
    return asInfixHelper(it);
}

string Expression::asPostfix()
{
    string res;
    BST<int, Component>::PostfixIterator it = tree_.postfixBegin();
    while (it) {
        res += (*it).str() + " ";
        ++it;
    }
    return res;
}

string Expression::asInfixHelper(BST<int, Component>::InfixIterator sub)
{
    Component c = *sub;
    if (c.getType() != Component::kOperator)
        return c.str();
    ++sub;
    string res;
    bool enclosed = false;
    if ((*sub).getType() == Component::kOperator
        && (*sub).getPriority() > c.getPriority()) {
        res += "(";
        enclosed = true;
    }
    res += asInfixHelper(sub);
    if (enclosed) {
        res += ")";
        enclosed = false;
    }
    res += " " + c.str() + " ";
    ++sub;
    if ((*sub).getType() == Component::kOperator
        && (*sub).getPriority() >= c.getPriority()) {
        res += "(";
        enclosed = true;
    }
    res += asInfixHelper(sub);
    if (enclosed) {
        res += ")";
        enclosed = false;
    }
}
