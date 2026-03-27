#include <fstream>
#include <sstream>
#include <iostream>
#include "Data.h"
#include "parser.h"

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \n\r\t");
    return str.substr(first, (last - first + 1));
}

Data parse(const std::string &filename) {
    Data data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    std::string line, section;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        if (line[0] == '#'){
            if (line == "#Reviewers") {
                section = "reviewers";
            } 
            else if (line == "#Submissions") {
                section = "submissions";
            } 
            else if (line == "#Parameters") {
                section = "parameters";
            } 
            else if (line == "#Control") {
                section = "control";
            }
            continue;
        }
        std::istringstream iss(line);
        std::string attribute;
        std::vector<std::string> attributes;
        while (std::getline(iss, attribute, ',')) {
            attribute = trim(attribute);
            attributes.push_back(attribute);
        }
        if (section == "reviewers"){
            Reviewer reviewer;
            reviewer.id = std::stoi(attributes[0]);
            reviewer.name = attributes[1];
            reviewer.email = attributes[2];
            reviewer.primaryExpertise = std::stoi(attributes[3]);
            if (attributes.size() > 4 && !attributes[4].empty()) {
                reviewer.secondaryExpertise = std::stoi(attributes[4]);
            }
            data.addReviewer(reviewer);
        }
        else if (section == "submissions"){
            Submission submission;
            submission.id = std::stoi(attributes[0]);
            submission.title = attributes[1];
            submission.author = attributes[2];
            submission.email = attributes[3];
            submission.primaryTopic = std::stoi(attributes[4]);
            if (attributes.size() > 5 && !attributes[5].empty()) {
                submission.secondaryTopic = std::stoi(attributes[5]);
            }
            data.addSubmission(submission);
        }
        else if (section == "parameters"){
            if (attributes[0] == "MinReviewsPerSubmission") {
                data.setMinReviewsPerSubmission(std::stoi(attributes[1]));
            }
            else if (attributes[0] == "MaxReviewsPerReviewer") {
                data.setMaxReviewsPerReviewer(std::stoi(attributes[1]));
            }
        }
        else if (section == "control"){
            if (attributes[0] == "GenerateAssignments") {
                data.setGenerateAssignments(std::stoi(attributes[1]));
            }
            else if (attributes[0] == "RiskAnalysis") {
                data.setRiskAnalysis(std::stoi(attributes[1]));
            }
            else if (attributes[0] == "OutputFileName") {
                data.setOutputFileName(attributes[1].substr(1,attributes[1].length()-2)); // remove as aspas
            }
        }
    }

    return data;
}
