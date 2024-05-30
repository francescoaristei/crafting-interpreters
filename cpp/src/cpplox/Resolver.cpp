# include "Resolver.h"
# include "Block.h"
# include "Stmt.h"
# include "Expr.h"
# include "Var.h"
# include "Token.h"
# include "Variable.h"
# include "Lox.h"
# include "Assign.h"
# include "Function.h"
# include "Expression.h"
# include "If.h"
# include "Print.h"
# include "Return.h"
# include "While.h"
# include "Binary.h"
# include "Call.h"
# include "Grouping.h"
# include "Literal.h"
# include "Logical.h"
# include "Unary.h"
# include <vector>
# include <map>
# include <stack>
# include <string>
# include <list>


Resolver::Resolver (Interpreter interpreter) {
    this -> interpreter = interpreter;
}


void Resolver::resolve (Stmt *stmt) {
    stmt->accept(*this);
}

void Resolver::resolve (Expr *expr) {
    expr->accept(*this);
}

void Resolver::resolve (vector<Stmt*> statements) {
    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        resolve(*itr);
    }
}

void Resolver::resolveLocal (Expr *expr, Token name) {
    list<map<string, bool>> templist;
    int i = scopes.size() - 1;
    bool exit = false;
    while (!scopes.empty()) {
        map<string, bool> tempmap;
        tempmap = scopes.top();
        for (map<string, bool>::iterator itr = tempmap.begin(); itr != tempmap.end(); ++itr) {
            if (tempmap.find(itr->first) != tempmap.end()) {
                interpreter.resolve(expr, scopes.size() - 1 - i);
                exit = true;
                break;
            }
        }
        if (exit) break;
        templist.push_back(scopes.top());
        scopes.pop();
        i--;
    }

    while (!templist.empty()) {
        scopes.push(*templist.begin());
        templist.pop_front();
    }
}

void Resolver::resolveFunction (Function *function, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;
    beginScope();
    for (vector<Token>::iterator itr = function->getparams().begin(); itr != function->getparams().end(); ++itr) {
        declare(*itr);
        define(*itr);
    }
    resolve(function->getbody());
    endScope();
    currentFunction = enclosingFunction;
}

void Resolver::endScope () {
    scopes.pop();
}

void Resolver::beginScope () {
    map<string, bool> scope;
    scopes.push(scope);
}

void Resolver::declare (Token name) {
    if (scopes.empty()) return;

    map<string, bool> scope = scopes.top();
    if (scope.find(name.getLexeme()) != scope.end()) {
        // STILL ERROR WITH LOX
        //Lox.error(name, "Already variable with this name in this scope");
    }
    scope[name.getLexeme()] = false;
}

void Resolver::define (Token name) {
    if (scopes.empty()) return;
    scopes.top()[name.getLexeme()] = true;
}

void Resolver::visitBlockStmt (Block& stmt) {
    beginScope();
    resolve(stmt.getstatements());
    endScope();
}

void Resolver::visitVarStmt (Var& stmt) {
    declare(stmt.getToken());
    if (stmt.getinitializer() != NULL) {
        resolve(stmt.getinitializer());
    }
    define(stmt.getToken());
}

void Resolver::visitFunctionStmt (Function& stmt) {
    declare(stmt.getname());
    define(stmt.getname());
    resolveFunction(&stmt, FunctionType::FUNCTION);
}


void Resolver::visitExpressionStmt (Expression& stmt) {
    resolve(stmt.getexpression());
}

void Resolver::visitIfStmt (If& stmt) {
    resolve(stmt.getexpression());
    resolve(stmt.getThenBranch());
    if (stmt.getElseBranch() != NULL) resolve(stmt.getElseBranch());
}

void Resolver::visitPrintStmt (Print& stmt) {
    resolve(stmt.getexpression());
}

void Resolver::visitReturnStmt (Return& stmt) {
    if (currentFunction == FunctionType::NONE) {
        // LOX ERRRO TO FIX
        //Lox.error(stmt.getKeyword(), "Can't return from top-level code");
    }
    if (stmt.getvalue() != NULL) {
        resolve(stmt.getvalue());
    }
}

void Resolver::visitWhileStmt (While& stmt) {
    resolve(stmt.getexpression());
    resolve(stmt.getstmt());
}

void Resolver::visitVariableExpr (Variable& expr) {
    if (!scopes.empty() &&
        scopes.top()[expr.getname().getLexeme()] == false) {
            // STILL ERROR WITH LOX
            //Lox.error(expr.getname(), "Can't read local variable in its own initializer");
        }
        resolveLocal (&expr, expr.getname());
}

void Resolver::visitAssignExpr (Assign& expr) {
    resolve(expr.getvalue());
    resolveLocal(&expr, expr.getname());
}

void Resolver::visitBinaryExpr (Binary& expr) {
    resolve(expr.getleft());
    resolve(expr.getright());
}

void Resolver::visitCallExpr (Call& expr) {
    resolve(expr.getcallee());
    for (vector<Expr*>::iterator itr = expr.getarguments().begin(); itr != expr.getarguments().end(); ++itr) {
        resolve(*itr);
    }
}

void Resolver::visitGroupingExpr (Grouping& expr) {
    resolve(expr.getexpression());
}

void Resolver::visitLiteralExpr (Literal& expr) {
    /* do nothing */
}

void Resolver::visitLogicalExpr (Logical& expr) {
    resolve(expr.getleft());
    resolve(expr.getright());
}

void Resolver::visitUnaryExpr (Unary& expr) {
    resolve(expr.getright());
}