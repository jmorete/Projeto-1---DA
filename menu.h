#ifndef MENU_H
#define MENU_H
#include <Graph.h>
#include <output.h>

class Menu {
private:
    std::string file;
    int state = 0;
    Data data = {};
    Output output = {};
public:
    int getState() const;
    void setState(int state);

    std::string getFile();
    void setFile(const std::string &file);

    Data getData();
    void setData(const Data &data);

    Output getOutput();
    void setOutput(const Output &out);

    bool hasFile() const;
    bool hasAssigned();

    static std::string getInput();

    void runAssignments();


    void run();
    void mainMenu();
    void loadFileMenu();
    void viewDataMenu();
    void manualMenu();
    void viewOutputMenu();
    void exportMenu();

    void printHeader() const;
    void display() const;
};



#endif //MENU_H
