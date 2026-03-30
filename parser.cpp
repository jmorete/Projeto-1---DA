#include <fstream>
#include <sstream>
#include <iostream>
#include "Data.h"
#include "parser.h"
#include "error.h"
#include <stdexcept>
#include <unordered_set>
#include <utility>

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \n\r\t");
    return str.substr(first, (last - first + 1));
}

void addLineError(std::string error, int line, std::vector<std::string> &errors){
    errors.push_back(error + " in line " + std::to_string(line));
}

void addInvalidParameterError(std::string parameter, std::vector<std::string> &errors){
    errors.push_back("Invalid " + parameter + " parameter");
}

void addMissingParameterError(std::string parameter, std::vector<std::string> &errors){
    errors.push_back("Missing " + parameter);
}

void addDuplicateIdError(std::string idType, int id, std::vector<std::string> &errors){
    errors.push_back("Duplicate " + idType + " id found: " + std::to_string(id));
}

void validateData(const Data &data, std::vector<std::string> &errors){
    std::unordered_set<int> submissionIds;
    std::unordered_set<int> reviewerIds;
    for (const Submission &s : data.getSubmissions()){
        if (!submissionIds.insert(s.id).second){
            addDuplicateIdError("submission", s.id, errors);
        }
    }
    for (const Reviewer &r : data.getReviewers()){
        if (!reviewerIds.insert(r.id).second){
            addDuplicateIdError("reviewer", r.id, errors);
        }
    }
    if (data.getMaxReviewsPerReviewer() <= 0){
        addInvalidParameterError("maxReviewsPerReviewer", errors);
    }
    if (data.getMinReviewsPerSubmission() <= 0){
        addInvalidParameterError("minReviewsPerSubmission", errors);
    }
    if (data.getGenerateAssignments() < 0 || data.getGenerateAssignments() > 3){
        addInvalidParameterError("generateAssignments", errors);
    }
    if (data.getRiskAnalysis() < 0){
        addInvalidParameterError("riskAnalysis", errors);
    }

    if (data.getSubmissions().empty()){
        addMissingParameterError("Submissions", errors);
    }
    if (data.getReviewers().empty()){
        addMissingParameterError("Reviewers", errors);
    }
    if (!data.maxReviewsPerReviewerIsSet()){
        addMissingParameterError("maxReviewsPerReviewer", errors);
    }
    if (!data.minReviewsPerSubmissionIsSet()){
        addMissingParameterError("minReviewsPerSubmission", errors);
    }
    if (!data.generateAssignmentsIsSet()){
        addMissingParameterError("generateAssignments", errors);
    }
    if (!data.riskAnalysisIsSet()){
        addMissingParameterError("riskAnalysis", errors);
    }
}

bool parse(const std::string &filename, Data &data) {
    Data tempData; // if errors occur → doesn't corrupt existing data
    std::ifstream file(filename);
    std::vector<std::string> errors;
    if (!file.is_open()) {
        printError("Error opening file: " + filename);
        return false;
    }
    int lineNum = 0;
    std::string line, section;
    while (std::getline(file, line)) {
        lineNum++;
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
        try {
            if (section == "reviewers"){
                if (attributes.size() != 4 && attributes.size() != 5){
                    addLineError("Invalid number of arguments", lineNum, errors);
                    continue;
                }
                Reviewer reviewer;
                reviewer.id = std::stoi(attributes[0]);
                reviewer.name = attributes[1];
                reviewer.email = attributes[2];
                reviewer.primaryExpertise = std::stoi(attributes[3]);
                if (attributes.size() > 4 && !attributes[4].empty()) {
                    reviewer.secondaryExpertise = std::stoi(attributes[4]);
                }
                tempData.addReviewer(reviewer);
            }
            else if (section == "submissions"){
                if (attributes.size() != 5 && attributes.size() != 6){
                    addLineError("Invalid number of arguments", lineNum, errors);
                    continue;
                }
                Submission submission;
                submission.id = std::stoi(attributes[0]);
                submission.title = attributes[1];
                submission.author = attributes[2];
                submission.email = attributes[3];
                submission.primaryTopic = std::stoi(attributes[4]);
                if (attributes.size() > 5 && !attributes[5].empty()) {
                    submission.secondaryTopic = std::stoi(attributes[5]);
                }
                tempData.addSubmission(submission);
            }
            else if (section == "parameters"){
                if (attributes.size() != 2){
                    addLineError("Invalid number of arguments", lineNum, errors);
                    continue;
                }
                if (attributes[0] == "MinReviewsPerSubmission") {
                    tempData.setMinReviewsPerSubmission(std::stoi(attributes[1]));
                }
                else if (attributes[0] == "MaxReviewsPerReviewer") {
                    tempData.setMaxReviewsPerReviewer(std::stoi(attributes[1]));
                }
            }
            else if (section == "control"){
                if (attributes.size() != 2){
                    addLineError("Invalid number of arguments", lineNum, errors);
                    continue;
                }
                if (attributes[0] == "GenerateAssignments") {
                    tempData.setGenerateAssignments(std::stoi(attributes[1]));
                }
                else if (attributes[0] == "RiskAnalysis") {
                    tempData.setRiskAnalysis(std::stoi(attributes[1]));
                }
                else if (attributes[0] == "OutputFileName") {
                    tempData.setOutputFileName(attributes[1].substr(1, attributes[1].length()-2));
                }
            }
        }
        catch (const std::invalid_argument &e){
            addLineError("Invalid argument", lineNum, errors);
        }
    }

    validateData(tempData, errors);

    if (!errors.empty()){
        std::string message = "File rejected. The following issues were encountered:\n";
        for (const std::string &error : errors){
            message += error + '\n';
        }
        printError(message);
        return false;
    }
    data = std::move(tempData);
    return true;
}
