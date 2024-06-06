# include <string>
# include "VisitorExpr.h"
# include "VisitorStmt.h"
# include "Expr.h"
# include "Binary.h"
# include "Literal.h"
# include "Unary.h"
# include "Grouping.h"
# include <vector>
# include "TokenType.h"
# include "Double.h"
# include "Boolean.h"
# include "String.h"
# include "Lox.h"
# include "Block.h"
# include "If.h"
# include "While.h"
# include "Logical.h"
# include <iostream>
# include "Environment.h"
# include "Interpreter.h"
# include "LoxCallable.h"
# include "TimeNative.h"
# include "LoxFunction.h"
# include "Return.h"
# include "Class.h"
# include "Call.h"
# include "Get.h"
# include "Set.h"
# include "This.h"
# include "Super.h"
# include "LoxClass.h"
# include "LoxInstance.h"
using namespace std;


Interpreter::Interpreter() {
    globals->define("clock", new TimeNative());
}


void Interpreter::execute (Stmt* stmt) {
    stmt -> accept(*this);
}

void Interpreter::resolve (Expr *expr, int depth) {
    /*if (Variable *v1 = dynamic_cast<Variable*>(expr)) {
            cout << v1->getname()->getLexeme() << "\n";
    }*/
    //cout << locals.size() << "A\n";
    locals[expr] = depth;
    //cout << locals.size() << "A\n";

}

void Interpreter::interpret (vector<Stmt*> statements) {
    try {
        //Object *value = evaluate(expression);
        //cout << stringify(value);
        for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
            execute(*itr);
        }
    } catch (Interpreter::RuntimeError error) {
        /* TO-DO: UNDERSTAND WHY DOES NOT FIND LOX */
        //Lox::runtimeError(error);
    }
}

Object* Interpreter::visitVariableExpr (Variable& expr) {
    //return environment -> get(expr.getname());
    return lookUpVariable(expr.getname(), &expr);
}

Object* Interpreter::lookUpVariable (Token *name, Expr *expr) {
    /*for (map<Expr*, int>::iterator itr = locals.begin(); itr != locals.end(); ++itr) {
        if (Variable *v1 = dynamic_cast<Variable*>(itr->first)) {
            cout << v1->getname()->getLexeme() << "\n";
        }
    }*/

    /*if (Variable *v1 = dynamic_cast<Variable*>(expr)) {
            cout << v1->getname()->getLexeme() << "\n";
    }*/

    //cout << locals.size() << "B\n";

    if (locals.find(expr) != locals.end()) {
        int distance = locals[expr];
        //cout << environment->getValues().size() << "\n";
        return environment->getAt(distance, name->getLexeme());
    } else {
        return globals->get(name);
    }
}

void Interpreter::visitVarStmt (Var& stmt) {
    Object* value = NULL;
    if (stmt.getinitializer() != NULL) {
        value = evaluate(stmt.getinitializer());
    }
    environment -> define(stmt.getToken()->getLexeme(), value);
}

void Interpreter::visitExpressionStmt (Expression& stmt) {
    evaluate(stmt.getexpression());
}

void Interpreter::visitPrintStmt (Print& stmt) {
    Object *value = evaluate(stmt.getexpression());
    cout << stringify(value);
}

void Interpreter::visitBlockStmt (Block& stmt) {
    executeBlock(stmt.getstatements(), new Environment(environment));
}

void Interpreter::visitIfStmt (If& stmt) {
    if (isTruthy(evaluate(stmt.getexpression()))) {
        execute(stmt.getThenBranch());
    } else if (stmt.getElseBranch() != NULL) {
        execute(stmt.getElseBranch());
    }
}

void Interpreter::visitWhileStmt (While& stmt) {
    while (isTruthy(evaluate(stmt.getexpression()))) {
        execute(stmt.getstmt());
    }
}

void Interpreter::visitFunctionStmt (Function& stmt) {
    LoxFunction *function = new LoxFunction(&stmt, environment, false);
    environment->define(stmt.getname()->getLexeme(), function);
}

void Interpreter::visitReturnStmt (Return& stmt) {
    Object* value = NULL;
    if (stmt.getvalue() != NULL) value = evaluate(stmt.getvalue());

    throw new Interpreter::ReturnEx(value);
}

void Interpreter::visitClassStmt (Class& stmt) {
    Object *superclass = NULL;
    if (stmt.getsuperclass() != NULL) {
        superclass = evaluate(stmt.getsuperclass());
        LoxClass* lc = dynamic_cast<LoxClass*>(superclass);
        if (!(lc)) {
            throw new RuntimeError (stmt.getsuperclass()->getname(), "Superclass must be a class.");
        }
    }
    environment->define(stmt.getname()->getLexeme(), NULL);
    //LoxClass *klass = new LoxClass(stmt.getname().getLexeme());
    //environment->assign(stmt.getname(), klass);

    if (stmt.getsuperclass() != NULL) {
        environment = new Environment(environment);
        environment->define("super", superclass);
    }

    map<string, LoxFunction*> methods;

    for (vector<Stmt*>::const_iterator itr = stmt.getmethods().begin(); itr != stmt.getmethods().end(); ++itr) {
        Function *fun = dynamic_cast<Function*>((*itr));
        bool isInit = fun ->getname()->getLexeme() == "init" ? true : false;
        LoxFunction *function = new LoxFunction(fun, environment, isInit);
        methods[fun->getname()->getLexeme()] = function;
    }

    LoxClass *klass = new LoxClass (stmt.getname()->getLexeme(), dynamic_cast<LoxClass*>(superclass), methods);

    if (superclass != NULL) {
        environment = environment->getEnclosing();
    }
    environment->assign(stmt.getname(), klass);
}

void Interpreter::executeBlock (vector<Stmt*> statements, Environment *environment) {
    Environment *previous = this -> environment;
    this -> environment = environment;
    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        execute(*itr);
    }
    this -> environment = previous;
}

Object* Interpreter::visitCallExpr (Call& expr) {
    Object *callee = evaluate(expr.getcallee());

    vector<Object*> arguments;
    for (vector<Expr*>::const_iterator itr = expr.getarguments().begin(); itr != expr.getarguments().end(); ++itr) {
        arguments.push_back(evaluate(*itr));
    }

    LoxCallable* lc = dynamic_cast<LoxCallable*>(callee);
    if (!lc) {
        throw new Interpreter::RuntimeError(expr.getparen(),
            "Can only call functions and classes.");
    }

    LoxCallable *function = dynamic_cast<LoxCallable*>(callee);

    if (arguments.size() != function-> arity()) {
        throw new Interpreter::RuntimeError (expr.getparen(), "Expected " + to_string(function -> arity()) + " arguments but got " + to_string(arguments.size()) + ".");
    }

    return function -> call(*this, arguments);
}

Object* Interpreter::visitAssignExpr (Assign& expr) {
    
    Object* value = evaluate(expr.getvalue());

    if (locals.find(&expr) != locals.end()) {
        int distance = locals[&expr];
        environment->assignAt(distance, expr.getname(), value);
    } else {
        globals->assign(expr.getname(), value);
    }
    
    //environment -> assign(expr.getname(), value);
    return value;
}

Object* Interpreter::visitBinaryExpr (Binary& expr) {
    Object *left = evaluate(expr.getleft());
    Object *right = evaluate(expr.getright());

    switch (expr.getop()->getType()) {
        case GREATER:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() > dynamic_cast<Double*>(right) -> getValue());
        case GREATER_EQUAL:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() >= dynamic_cast<Double*>(right) -> getValue());
        case LESS:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() < dynamic_cast<Double*>(right) -> getValue());
        case LESS_EQUAL:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() <= dynamic_cast<Double*>(right) -> getValue());
        case MINUS:
            checkNumberOperand(expr.getop(), right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() - dynamic_cast<Double*>(right) -> getValue());
        case BANG_EQUAL:
            return new Boolean(!isEqual(left, right));
        case EQUAL_EQUAL:
            return new Boolean(isEqual(left, right));
        case PLUS:
            if (Double* d1 = dynamic_cast<Double*>(left)) {
                if (Double* d2 = dynamic_cast<Double*>(right))
                    return new Double(d1 -> getValue() + d2 -> getValue());
            }
            if (String* s1 = dynamic_cast<String*>(left)) {
                if (String* s2 = dynamic_cast<String*>(right))
                    return new String(s1 -> getValue() + s2 -> getValue());
            }
            throw new Interpreter::RuntimeError(expr.getop(), "Operands must be two numbers or two strings.");
        case SLASH:
            checkNumberOperands(expr.getop(), left, right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() / dynamic_cast<Double*>(right) -> getValue());
        case STAR:
            checkNumberOperands(expr.getop(), left, right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() * dynamic_cast<Double*>(right) -> getValue());
    }

    /* should be unreachable */
    return NULL;
}

Object* Interpreter::visitLogicalExpr (Logical& expr) {
    Object *left = evaluate(expr.getleft());

    if (expr.getop()->getType() == TokenType::OR) {
        if (isTruthy(left)) return left;
    } else { /* if AND expr and left part is false */
        if (!isTruthy(left)) return left;
    }

    return evaluate(expr.getright());
}

Object* Interpreter::visitGroupingExpr (Grouping& expr) {
    return evaluate(expr.getexpression());
}

Object* Interpreter::visitLiteralExpr (Literal& expr) {
    if (expr.getvalue() == NULL) return new String("nil");
    return expr.getvalue();
}

/* post order traversal of the unary expression syntax tree */
Object* Interpreter::visitUnaryExpr (Unary& expr) {
    Object *right = evaluate(expr.getright());
    switch (expr.getop()->getType()) {
        case BANG:
            return new Boolean(!isTruthy(right));
        case MINUS:
            return new Double(-(dynamic_cast<Double*>(right) -> getValue()));
    }

    /* unreachable */
    return NULL;
}

Object* Interpreter::visitGetExpr (Get& expr) {
    Object *object = evaluate(expr.getobject());
    if (Object* o1 = dynamic_cast<Object*>(object)) {
        return dynamic_cast<LoxInstance*>(object)->get(expr.getname());
    }

    throw new Interpreter::RuntimeError (expr.getname(), "Only instances have properties.");
}

Object* Interpreter::visitSetExpr (Set& expr) {
    Object *object = evaluate(expr.getobject());
    LoxInstance *o1 = dynamic_cast<LoxInstance*>(object);
    if (!o1) {
        throw new Interpreter::RuntimeError (expr.getname(), "Only instances have fields.");
    }
    Object *value = evaluate(expr.getvalue());
    dynamic_cast<LoxInstance*>(object)->set(expr.getname(), value);
    return value;

}

Object* Interpreter::visitThisExpr (This& expr) {
    return lookUpVariable(expr.getname(), &expr);
}

Object* Interpreter::visitSuperExpr (Super& expr) {
    int distance = locals[&expr];
    LoxClass *superclass = dynamic_cast<LoxClass*>(environment->getAt(distance, "super"));

    LoxInstance *object = dynamic_cast<LoxInstance*>(environment->getAt(distance - 1, "this"));

    LoxFunction *method = superclass->findMethod(expr.getmethod()->getLexeme());

    if (method == NULL) {
        throw new Interpreter::RuntimeError (expr.getmethod(), "undefined property '" + expr.getmethod()->getLexeme() + "'.");
    }
    return method->bind(object);
}

bool Interpreter::isEqual (Object *a, Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL) return false;
    /* check if point to same memory region for equality */
    return a == b;
}

bool Interpreter::isTruthy (Object *object) {
    if (object == NULL) return false;
    if (Boolean* b = dynamic_cast<Boolean*>(object)) return b -> getValue();
}

Object* Interpreter::evaluate (Expr* expr) {
    return any_cast<Object*>(expr -> accept(*this));
}

void Interpreter::checkNumberOperand (Token *op, Object *operand) {
    if (Double* d = dynamic_cast<Double*>(operand)) return;
    throw new Interpreter::RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkNumberOperands (Token *op, Object *operand1, Object *operand2) {
    if (Double* d1 = dynamic_cast<Double*>(operand1)) {
        if (Double* d2 = dynamic_cast<Double*>(operand2))
            return;
    }
    throw new Interpreter::RuntimeError(op, "Operands must be numbers.");
}

/* CHECK AGAIN IF IT IS CORRECT (chapter Hooking Up the Interpreter)*/
string Interpreter::stringify (Object *object) {
    if (object == NULL) return "nil";
    return object -> toString();
}