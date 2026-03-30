#include <fstream>
#include <iostream>
#include "parser.h"
#include "Data.h"
#include "menu.h"

#include "build_graph.h"
#include "id.h"
#include "max_flow.h"
#include "output.h"

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
    setOutput({});
    writtenAssignments = false;
    writtenRiskAnalysis = false;
}

Output Menu::getOutput() {
    return this->output;
}

void Menu::setOutput(const Output &out) {
    this->output = out;
    //output.setCriticalReviewers({}); // reset risk analysis
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


bool Menu::hasRiskAnalysis() const {
    if (!output.getRiskAnalysisDone()) {
        cout << "[ERROR] No risk analysis found. Please run the risk analysis first.\n\n";
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
    Output out;
    Graph<int> *g = buildGraph(data);
    out.setMaxFlow(edmondsKarp(g, SOURCE_ID, SINK_ID));
    out.generateOutput(g,data);
    setOutput(out);
    delete g;

    cout << "[OK] Assignments successfully generated.\n\n";
    if (!output.getFailedSubmissions().empty()) cout << "[INFO] Not every submission could be assigned.\n\n";
}


void Menu::runRiskAnalysis() {
    std::vector<int> critical;
    int og_flow = output.getMaxFlow();

    for (Reviewer r : data.getReviewers()) {
        Data risk_data = data;
        risk_data.removeReviewer(r.id); // remove one reviewer at each iteration

        // get maxFlow of altered set of reviewers
        Graph<int> *risk_g = buildGraph(risk_data);
        int risk_flow = edmondsKarp(risk_g, SOURCE_ID, SINK_ID);
        delete risk_g;

        if (risk_flow < og_flow) {
            critical.push_back(r.id);
        }
    }
    output.setCriticalReviewers(critical);
    output.setRiskAnalysisDone(true);
    std::cout << "[OK] Risk Analysis complete.\n\n";
    if (!critical.empty()) cout << "[INFO] There is at least one critical reviewer.\n\n";

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
    if (i == "1") state = 1;
    else if (i == "2") state = 2;
    else if (i == "3") {
        if (!hasFile()) return;
        cout << "[INFO] Running using file configuration...\n\n";
        runAssignments();
        if (data.getGenerateAssignments()) {
            output.writeAToFile(data.getOutputFileName());
            cout << "[OK] Assignments successfully written to " << data.getOutputFileName() << ".\n\n";
        }
        if (data.getRiskAnalysis() == 1) { 
            runRiskAnalysis();
            output.writeRAToFile(data.getOutputFileName());
            cout << "[OK] Risk analysis successfully written to " << data.getOutputFileName() << ".\n\n";
        }
    }
    else if (i == "4") state = 4;
    else if (i == "5") state = 5;
    else if (i == "6") state = 6;
    else cout << "[ERROR] Invalid option.\n\n";
}

void Menu::loadFileMenu() {
    string i = getInput();
    if (i == "0") {
        state = 0;
        return;
    }
    cout << "[INFO] Parsing file...\n\n";
    Data d;
    if (!parse(i,d)) return;
    setData(d);
    file = i;
    state = 0;
    cout << "[OK] File loaded successfully.\n\n";
}

void Menu::viewDataMenu() {
    string i = getInput();
    if (i == "0") state = 0;
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
    else if (i == "4") {
        if (!hasFile()) return;
        data.printControls();
        waitForEnter();
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::manualMenu() {
    string i = getInput();
    if (i == "0") state = 0;
    else if (i == "1") {
        if (!hasFile()) return;
        cout << "[INFO] Generating assignments...\n\n";
        runAssignments();
    }
    else if (i == "2") {
        if (!hasFile() || !hasAssigned()) return;
        if (!output.getFailedSubmissions().empty()) {
            cout << "[ERROR] The assignment is incomplete.\n\n";
            return;
        }
        cout << "[INFO] Running Risk Analysis...\n\n";
        runRiskAnalysis();
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::viewOutputMenu() {
    string i = getInput();
    if (i == "0") state = 0;
    else if (i == "1") {
        if (!hasAssigned()) return;
        output.printOutput();
        waitForEnter();
    }
    else if (i == "2") {
        if (!hasRiskAnalysis()) return;
        output.printRiskAnalysis();
        waitForEnter();
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}

void Menu::exportMenu() {
    string i = getInput();
    if (i == "0") state = 0;
    else if (i == "1") {
        if (!hasAssigned()) return;
        if (writtenAssignments) {
            cout << "[ERROR] Assignments already exist in this file.\n\n";
            return;
        }
        output.writeAToFile(data.getOutputFileName());
        writtenAssignments = true;
        cout << "[OK] Assignments successfully written to " << data.getOutputFileName() << ".\n\n";
    }
    else if (i == "2") {
        if (!hasRiskAnalysis()) return;
        if (writtenRiskAnalysis) {
            cout << "[ERROR] Risk Analysis already exists in this file.\n\n";
            return;
        }
        output.writeRAToFile(data.getOutputFileName());
        writtenRiskAnalysis = true;
        cout << "[OK] Risk Analysis successfully written to " << data.getOutputFileName() << ".\n\n";
    }
    else cout << "[ERROR] Invalid option." << "\n\n";
}


void Menu::display() const {
    cout << "\n=======================================\n";
    cout << " Scientific Conference Assignment Tool\n";
    cout << "=======================================\n";
    cout << "Current file: " << (file.empty() ? "[none]" : file) << "\n\n";
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
        cout << "4. Show Controls\n";
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




