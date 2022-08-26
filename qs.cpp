/* This is version 1 of a project quick-start tool that generates a class, implementations file and a main
 * file. It also generates standard boilerplate for each file and places project in the right directory.
 * The programonly relies on 1 command-line argument from user
 * which will act as the name for the project and class.
 *
 * qs = (q)uick (s)tart
 *
 * Author @qpeano [created: 2021-12-18 | last updated: 2021-12-18]
 */

#include <iostream>
#include <fstream>
#include <sys/stat.h>

using std::string;
using std::ofstream;

int openFile(ofstream *file, string path, string ext, string name);
bool openDir(string *path, string name);
void fillerFunc(ofstream* file, char indicator, string name);

int main(int argc, char **argv) {

    if (argc == 2) {

        string path;
        string name(argv[1]);
        bool flag = openDir(&path, name);

        if (flag) {

            ofstream headerFile;
            ofstream impFile;
            ofstream mainFile;

            int i1 = openFile(&impFile, path, ".cpp", name);
            int i2 = openFile(&mainFile, path, ".cpp", "main");
            int i3 = openFile(&headerFile, path, ".h", name);
            int sum = i1 + i2 + i3;

            if (sum == 0) {

                fillerFunc(&mainFile, 'm', name);
                fillerFunc(&impFile, 'i', name);
                fillerFunc(&headerFile, 'h', name);

                std::cout << "[project created successfully]\n";
            }
            else {

                std::cout << "[ERROR: creation of files failed]\n";
            }
        }
        else {

            std::cout << "[ERROR: creation of directory failed]\n";
        }
    }
    else {

        std::cout << "[ERROR: wrong number of arguments provided]\n";
    }
}

bool openDir(string *path, string name) {

    string dirPath = "/home/ubuntu/CPP/PROJECTS/SMALL/" + name + "/";
    *path = dirPath;

    if (mkdir(dirPath.c_str(), 0777) == -1) {

        return false;
    }
    return true;
}

int openFile(ofstream* file, string path, string ext, string name) {

    string newFile = path + name + ext; // ext = file extension
    file->open(newFile);

    if (!*file) {

        return 1;
    }
    return 0;
}

void fillerFunc(ofstream* file, char indicator, string name) {

    string content; // content is what is being written into the file

    if (indicator == 'm') { // if indicator says it's a main file, let content be this

        content = "#include <iostream>\n";
        content += "#include \"" + name + ".h\"\n";
        content += "\nint main() {\n\n\t//main\n}";
    }
    else if (indicator == 'i') { // else if it says its a definitions file, let content be this

        content = "#include <iostream>\n";
        content += "#include \"" + name + ".h\"\n";
        // constructor
        content += "\n" + name + "::" + name + "() {\n\n\t//ctor\n}\n";
         // destructor
        content += "\n" + name + "::~" + name + "() {\n\n\t//dtor\n}\n";
         // copy constructor
        content += "\n" + name + "::" + name + "(const " + name + " &obj) {\n\n\t//cctor\n}\n";
        // assignment operator
        content += "\n" + name + "& " + name + "::operator=(const " + name + " &obj) {\n\n\t//a-operator\n}\n";
    }
    else { // else, (it just has to be header) ley content be this

        string u_name = name;
        for (auto& c: u_name) c = toupper(c); // this is for the #define preprocessor
        // stolen from https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case

        content = "#ifndef " + u_name + "_H\n";
        content += "#define " + u_name + "_H\n\n";
        content += "#include <iostream>\n\n";
        content += "class " + name + " {\n\n";
        content += "\tprivate:\n\n\tpublic:\n\n";
        content += "\t\t" + name + "(); //ctor\n";
        content += "\t\t~" + name + "(); // dtor\n";
        content += "\t\t" + name + "(const " + name + " &obj); // cctor\n";
        content += "\t\t" + name + "& " + "operator=(const " + name + " &obj); // a-operator\n";
        content += "};\n\n";
        content += "#endif";
    }

    *file << content << std::endl; // writes content to file
}
