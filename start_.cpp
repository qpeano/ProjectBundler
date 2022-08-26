/* This is a PROOF OF CONCEPT for a project quick-start tool. It creates a new directory for the project
 * and creates 1 header for a class, 1 method definitions file, and a main file, as well as generating
 * the standard boiler-plate code for each file.
 *
 * Author: @qpeano [created: 2021-12-17 | last updated: 2021-12-18]
 */

#include <iostream>
#include <fstream>
#include <sys/stat.h>

using std::string;
using std::ofstream;

bool openDir(string* path); // names and creates new directory
string openFile(ofstream* file, string path, string ext); // used to name and create header file
void openFile(ofstream* file, string path, string ext, string name); // used to create main and definition files
void fillerFunc(ofstream* file, char indicator, string name); // fills all created files with code

int main() {

    string path; // path to folder and files
    bool continueFlag = openDir(&path); // attempts to create folder and returns if program should proceed or not

    if (continueFlag) {

        // files in created project
        ofstream headerFile;
        ofstream impFile;
        ofstream mainFile;

        // creates files
        string name = openFile(&headerFile, path, ".h");
        openFile(&impFile, path, ".cpp", name);
        openFile(&mainFile, path, ".cpp", "main");

        // fills all files with boiler-plate
        fillerFunc(&mainFile, 'm', name);
        fillerFunc(&impFile, 'i', name);
        fillerFunc(&headerFile, 'h', name);

        std::cout << "[project created successfully]\n"; // indicator (not really, more of a message to user)

        // closes file connection
        impFile.close();
        headerFile.close();
        mainFile.close();
    }
}

bool openDir(string* path) {

    string projectName;
    string dirPath;
    std::cout << "enter project name: ";
    std::cin >> projectName;

    dirPath = "/home/ubuntu/CPP/PROJECTS/" + projectName + "/";
    *path = dirPath;

    // if directory creation fails, program asks user if they want to try again
    while (mkdir(dirPath.c_str(), 0777) == -1) {

        char ans;
        std::cout << "directory could not be created, do you wish to try again? (y/n): ";
        std::cin >> ans;

        if (ans == 'y' || ans == 'Y') { // if yes, try creating directory again

            std::cout << "re-enter project name: ";
            std::cin >> projectName;

            dirPath = "/home/ubuntu/CPP/PROJECTS/" + projectName + "/";
            *path = dirPath;
        }
        else { // terminates loop by returning, return value also terminates whole program

            std::cout << "execution status: terminated\n";
            return false;
        }
    }

    // this is executed if/when creation is successful, proceeds with execution in main
    std::cout << "----------\n";
    return true;
}

string openFile(ofstream* file, string path, string ext) {

    string name;
    std::cout << "enter header file name: ";
    std::cin >> name;

    string newFile;
    newFile = path + name + ext;


    file->open(newFile);

    // if header creation fails, program asks user if they want to try again
    while (!file) {

        char ans;
        std::cout << "could not create header, do you wish to try again? (y/n): ";
        std::cin >> ans;

        if (ans == 'y' || ans == 'Y') { // if yes, retries creating header

            std::cout << "re-enter header file name: ";
            std::cin >> name;

            newFile = path + name + ext;
            file->clear();
            file->open(newFile);
        }
        else { // if not, returns garbage

            return "err";
        }
    }

    return name; // returns filename
}

void openFile(ofstream* file, string path, string ext, string name) {

    string newFile = path + name + ext; // ext = file extension
    file->open(newFile);
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
        for (auto & c: u_name) c = toupper(c); // this is for the #define preprocessor
        // stolen from https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case

        content = "#ifndef " + u_name + "_H\n";
        content += "#define " + u_name + "_H\n\n";
        content += "#include <iostream>\n\n";
        content += "class " + name + " {\n\n";
        content += "\tprivate:\n\n\tpublic:\n";
        content += "\t\t" + name + "(); //ctor\n";
        content += "\t\t~" + name + "(); // dtor\n";
        content += "};\n\n";
        content += "#endif";

    }

    *file << content << std::endl; // writes content to file
}
