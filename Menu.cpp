#include <fstream>
#include <iostream>
#include "parser.h"
#include "Data.h"
#include "menu.h"

#include <build_graph.h>
#include <id.h>
#include <max_flow.h>
#include <output.h>

#include <limits>

using namespace std;

int Menu::getState() const {
    return this->state;
}

void Menu::setState(const int state) {
    this->state = state;
}

std::string Menu::getFile() {
    return this->file;
}

void Menu::setFile(const std::string &file) {
    this->file = file;
}

Data Menu::getData() {
    return this->data;
}

void Menu::setData(const Data &data) {
    this->data = data;
}

Output Menu::getOutput() {
    return this->output;
}

void Menu::setOutput(const Output &out) {
    this->output = out;
}

bool Menu::hasFile() const {
    if (file.empty()) {
        cout << "[ERROR] No file selected. Please load a file first.\n\n";
        return false;
    }
    return true;
}

bool Menu::hasAssigned() {
    if (output.getAssignments().empty() && output.getFailedSubmissions().empty()) {
        cout << "[ERROR] No assignments found. Please generate the assignments first.\n\n";
        return false;
    }
    return true;
}


std::string Menu::getInput() {
    string s;
    cout << ">>  ";
    cin >> s;
    return s;
}



void Menu::waitForEnter() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


void Menu::runAssignments() {
    Graph<int> *g = buildGraph(data);
    edmondsKarp(g, SOURCE_ID, SINK_ID);
    Output out;
    out.generateOutput(g,data);
    setOutput(out);
    cout << "[OK] Assignments successfully generated.\n\n";
    if (!output.getFailedSubmissions().empty()) cout << "[INFO] Not every submission could be assigned.\n\n";
}


void Menu::run() {
    while (true) {
        if (state == -1) return;
        display();
        switch (state) {
            case 0: mainMenu(); break;
            case 1: loadFileMenu(); break;
            case 2: viewDataMenu(); break;
            case 4: manualMenu(); break;
            case 5: viewOutputMenu(); break;
            case 6: exportMenu(); break;
        }
    }
}

void Menu::mainMenu() {
    string i = getInput();
    if (i == "0") {
        cout << "[INFO] Exiting...\n\n";
        setState(-1);
        return;
    }
    if (i == "1") setState(1);
    else if (i == "2") setState(2);
    else if (i == "3") {
        if (!hasFile()) return;
        cout << "[INFO] Running using file configuration...\n\n";
        runAssignments();
        if (data.getGenerateAssignments()) {
            output.writeToFile(data.getOutputFileName());
            cout << "[OK] Output successfully written to " << data.getOutputFileName() << ".\n\n";
        }
        //risk analysis?
    }
    else if (i == "4") setState(4);
    else if (i == "5") setState(5);
    else if (i == "6") setState(6);
    else cout << "[ERROR] Invalid option.\n\n";
}

void Menu::loadFileMenu() {
    string i = getInput();
    if (i == "0") {
        setState(0);
        return;
    }
    if (ifstream f(i); !f.is_open()) {
        cout << "[ERROR] " << i << " doesn't exist. Please enter a valid name.\n\n";
        return;
    }
    cout << "[INFO] Parsing file...\n\n";
    Data d;
    if (!parse(i,d)) return;
    setData(d);
    setFile(i);
    setOutput({});
    setState(0);
    cout << "[OK] File loaded successfully.\n\n";
}

void Menu::viewDataMenu() {
    string i = getInput();
    if (i == "0") setState(0);
    else if (i == "1") {
        if (!hasFile()) return;
        data.printSubmissions();
        waitForEnter();
    }
    else if (i == "2") {
        if (!hasFile()) return;
        data.printReviewers();
        waitForEnter();
    }
    else if (i == "3") {
        if (!hasFile()) return;
        data.printParameters();
        waitForEnter();
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::manualMenu() {
    string i = getInput();
    if (i == "0") setState(0);
    else if (i == "1") {
        if (!hasFile()) return;
        cout << "[INFO] Generating assignments...\n\n";
        runAssignments();
    }
    else if (i == "2") {
        if (!hasFile()) return;
        //risk analysis
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::viewOutputMenu() {
    string i = getInput();
    if (i == "0") setState(0);
    else if (i == "1") {
        if (!hasAssigned()) return;
        output.printOutput();
        waitForEnter();
    }
    else if (i == "2") {
        if (!hasAssigned()) return;
        //print risk analysis
        waitForEnter();
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::exportMenu() {
    string i = getInput();
    if (i == "0") setState(0);
    else if (i == "1") {
        if (!hasAssigned()) return;
        output.writeToFile(data.getOutputFileName());
        cout << "[OK] Output successfully written to " << data.getOutputFileName() << ".\n\n";
    }
    else if (i == "2") {
        if (!hasAssigned()) return;
        //export risk analysis
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}


void Menu::printHeader() const {
    cout << "\n=======================================\n";
    cout << " Scientific Conference Assignment Tool\n";
    cout << "========================================\n";
    cout << "Current file: " << (file.empty() ? "[none]" : file) << "\n\n";
}


void Menu::display() const {
    printHeader();
    if (state == 0) {
        cout << "[DATA]\n";
        cout << "   1. Load Input File\n";
        cout << "   2. View Data\n\n";
        cout << "[EXECUTION]\n";
        cout << "   3. Run Using File Configuration\n";
        cout << "   4. Manual Operations\n\n";
        cout << "[RESULTS]\n";
        cout << "   5. View Results\n";
        cout << "   6. Export Results\n\n";
        cout << "0. Exit\n\n";
    }
    if (state == 1) {
        cout << "#. Enter the name of the file.\n";
        cout << "0. Go Back\n\n";
    }
    if (state == 2) {
        cout << "1. List Submissions\n";
        cout << "2. List Reviewers\n";
        cout << "3. Show Parameters\n";
        cout << "0. Go Back\n\n";
    }
    if (state == 4) {
        cout << "1. Generate Assignments\n";
        cout << "2. Run Risk Analysis\n";
        cout << "0. Go Back\n\n";
    }
    if (state == 5) {
        cout << "1. Show Assignments\n";
        cout << "2. Show Risk Analysis\n";
        cout << "0. Go Back\n\n";
    }
    if (state == 6) {
        cout << "1. Export Assignments\n";
        cout << "2. Export Risk Analysis\n";
        cout << "0. Go Back\n\n";
    }
}




