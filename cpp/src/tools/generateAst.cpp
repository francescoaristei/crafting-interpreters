# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>
# include <cctype>
# include <sstream>

using namespace std;

/* Utility file to generate the different expression classes, tokens in the AST. Visitor Design Pattern. */

/* trim from start */
void ltrim (string &s) { /* pass by reference */
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

/* trim from end */
void rtrim (string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

/* create subclass for each subclass */
void defineType (string outputdir, string basename, string classname, string fields) {
    string path_header = outputdir + "/" + classname + ".h";
    ofstream file_header(path_header, ios::app);
    if (!file_header.is_open()) {
        cerr << "Could not open the file_header, exiting...\n";
        exit(64);
    }

    string upperName = classname;
    transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    file_header << "# ifndef " << upperName << "\n";
    file_header << "# define " << upperName << "\n";

    /* to iterate over the fields separating by char */
    stringstream each_class(fields);
    string class_seg;
    vector<string> classList;
    while (getline(each_class, class_seg, ',')) {
        /* remove leading space */
        ltrim(class_seg);
        size_t index = class_seg.find(' ');
        classList.push_back(class_seg.substr(0, index));
    }

    /* include sublcasses that make up attribute list */
    for (vector<string>::iterator itr = classList.begin(); itr != classList.end(); ++itr) {
        file_header << "# include " << "\"" << *itr <<".h" << "\"" << "\n";
    }

    if (fields.find("Expr") == string::npos) {
        file_header << "# include " << "\"" << basename << ".h" << "\"" << "\n";
    }

    file_header << "# include " << "\"" << "Visitor.h" << "\"" << "\n";

    file_header << "\n";
    file_header << "class " << classname << ": public " << basename << " {" << "\n";
    file_header << "   public: " << "\n";
    file_header << "       " + classname << " (" + fields + ");" + "\n";

    /* template function accept */
    file_header << "       " << "template <typename R>\n";
    file_header << "       " << "R accept (Visitor<R> visitor);\n";


    /* extract single fields */
    stringstream each_field(fields);
    string segment;
    vector<string> segList;
    while (getline(each_field, segment, ','))
        segList.push_back(segment);

    file_header << "   private: " << "\n";
    for (vector<string>::iterator itr = segList.begin(); itr != segList.end(); ++itr) {
        ltrim(*itr);
        file_header << "       " << *itr << ";" << "\n";
    }

    file_header << "};" << "\n";
    file_header << "# endif";
    file_header.close();

    string path_cpp = outputdir + "/" + classname + ".cpp";

    ofstream file_cpp(path_cpp, ios::app);
    if (!file_cpp.is_open()) {
        cerr << "Could not open the file header, exiting...\n";
        exit(64);
    }

    file_cpp << "# include " << "\"" << classname << ".h" << "\"" << "\n";

    /* include sublcasses that make up attribute list */
    for (vector<string>::iterator itr = classList.begin(); itr != classList.end(); ++itr) {
        file_cpp << "# include " << "\"" << *itr << ".h" << "\"" << "\n";
    }

    file_cpp << "# include " << "\"" << "Visitor.h" << "\"" << "\n";

    file_cpp << "\n";

    /* to iterate over the fields separating by char */
    stringstream each_attr(fields);
    string attr_seg;
    vector<string> attrList;
    while (getline(each_attr, attr_seg, ',')) {
        /* remove leading space */
        ltrim(attr_seg);
        size_t index = attr_seg.find(' ');
        attrList.push_back(attr_seg.substr(index, attr_seg.length() - index));
    }

    file_cpp << classname << "::" << classname << " (" << fields << ") {" << "\n";
    for (vector<string>::iterator itr = attrList.begin(); itr != attrList.end(); ++itr) {
        file_cpp << "    " << "this -> " << *itr << " = " << *itr << ";" << "\n";
    }

    file_cpp << "};\n";
    file_cpp << "template <typename R>\n";
    file_cpp << "R " <<  classname << "::" << "accept (Visitor<R> visitor) {\n";
    file_cpp << "   return visitor.visit()\n";
    file_cpp << "}\n";

    file_cpp.close();


}

void defineVisitor (string outputdir, string basename, vector<string> expressions) {
    string path = outputdir + "/" + "Visitor.h";
    ofstream file (path, ios::app);
    if (!file.is_open()) {
        cout << "Error opening the file, exiting...\n";
        exit(64);
    }

    for (vector<string>::iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
        size_t index = itr -> find(':');
        string type = itr -> substr(0, index);
        rtrim(type);
        file << "# include " << "\"" << type << ".h" << "\"" << "\n"; 
    }
    file << "\n";
    
    string baseToLower = basename;
    transform(baseToLower.begin(), baseToLower.end(), baseToLower.begin(), ::tolower);
    file << "template <typename R>\n";
    file << "class Visitor {\n";
    file << "   public:\n";
    for (vector<string>::iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
        size_t index = itr -> find(":");
        string type = itr -> substr(0, index);
        rtrim(type);
        /* define pure virtual methods */
        file << "       virtual R visit" << type << basename + " (" << type << " " << baseToLower << ")"; 
        file << " = " << "0;" << "\n";
    }

    file << "};";
}


void defineAst (string outputdir, string basename, vector<string> expressions) {
    string path = outputdir + "/" + basename + ".h";
    ofstream file(path, ios::app);
    if (!file.is_open()) {
        cerr << "Could not open the file, exiting...\n";
        exit(64);
    }

    file << "# include " << "\"" << "Visitor.h" << "\"" << "\n";
    file << "class " << basename << " {";
    file << "\n";
    file << "   template <typename R>\n";
    file << "   R accept (Visitor<R> visitor);\n";
    file << "};";
    file.close();

    defineVisitor(outputdir, basename, expressions);

    for (vector<string>::iterator itr = expressions.begin(); itr != expressions.end(); ++itr) {
        size_t index = itr -> find(':');
        string classname = itr -> substr(0, index);
        string fields = itr -> substr(index + 2, itr -> length() - index);
        ltrim(classname);
        rtrim(classname);
        ltrim(fields);
        rtrim(fields);
        defineType(outputdir, basename, classname, fields);
    }
}


int main (int argc, char *argv[]) {
    /* name of the file + output dir */
    if (argc < 2) {
        cerr << "Usage: generate_ast <output directory>";
        exit(64);
    }

    string outputdir = argv[1];
    vector<string> expressions;
    expressions.push_back("Binary   : Expr left, Token op, Expr right");
    expressions.push_back("Grouping : Expr expression");
    expressions.push_back("Literal  : Object value");
    expressions.push_back("Unary    : Token op, Expr right");
    defineAst(outputdir, "Expr", expressions);
}