#include "output.h"
#include "id.h"
#include <fstream>
#include <iostream>

bool sortBySubmissionId(const Assignment &a, const Assignment &b) {
    return a.submissionId < b.submissionId;
}

bool sortByReviewerId(const Assignment &a, const Assignment &b) {
    return a.reviewerId < b.reviewerId;
}

std::vector<Assignment> Output::getAssignments() {
    return assignments;
}

void Output::setAssignments(const std::vector<Assignment> &assignments) {
    this->assignments = assignments;
}

std::vector<failedSubmission> Output::getFailedSubmissions() {
    return failedSubmissions;
}

void Output::setFailedSubmissions(const std::vector<failedSubmission> &failsub) {
    this->failedSubmissions = failsub;
}

const std::vector<int>& Output::getCriticalReviewers() const {
    return criticalReviewers;
}

void Output::setCriticalReviewers(const std::vector<int>& reviewers) {
    criticalReviewers = reviewers;
}

const bool Output::getRiskAnalysisDone() const {
    return riskAnalysisDone;
}

void Output::setRiskAnalysisDone(bool ra) {
    riskAnalysisDone = ra;
}

void Output::sortAssignments(const std::string &sortBy) {
    if (sortBy == "submission") {
        std::sort(assignments.begin(), assignments.end(), sortBySubmissionId);
    } 
    else if (sortBy == "reviewer") {
        std::sort(assignments.begin(), assignments.end(), sortByReviewerId);
    }
}

bool sortByFailedSubmissionId(const failedSubmission &a, const failedSubmission &b) {
    return a.submissionId < b.submissionId;
}

void Output::generateOutput(Graph<int> *g, Data &data) {
    for (auto v : g->getVertexSet()) {
        int submissionId = v->getInfo();
        if (!(submissionId & REVIEWER_MASK)){
            if ((submissionId & PRIMARY_TOPIC_MASK) || (submissionId & SECONDARY_TOPIC_MASK)) { 
                for (auto e : v->getAdj()) {
                    if (e->getFlow() > 0) { 
                        if (submissionId & PRIMARY_TOPIC_MASK){
                            assignments.push_back({submissionId & ID_MASK, e->getDest()->getInfo() & ID_MASK, data.getPrimaryDomain(submissionId & ID_MASK)});
                        }
                        else {
                            assignments.push_back({submissionId & ID_MASK, e->getDest()->getInfo() & ID_MASK, data.getSecondaryDomain(submissionId & ID_MASK)});
                        }
                    }
                }
            }
            if (submissionId & SOURCE_CONNECTED_MASK) {
                auto incoming = v->getIncoming();
                if (!incoming.empty()){
                int assignedReviews = incoming[0]->getFlow();
                int requiredReviews = incoming[0]->getWeight();
                    if (assignedReviews < requiredReviews) {
                        failedSubmissions.push_back({submissionId & ID_MASK, data.getPrimaryDomain(submissionId & ID_MASK), requiredReviews - assignedReviews});
                    }
                }
            }
        }
    }
}

void Output::writeAToFile(const std::string &filename) { 
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    if (!assignments.empty()) {
        out << "#SubmissionId,ReviewerId,Match" << std::endl;
        sortAssignments("submission");
        for (const auto &a : assignments) {
            out << a.submissionId << ", " << a.reviewerId << ", " << a.domain << std::endl;
        }
        out << "#ReviewerId,SubmissionId,Match" << std::endl;
        sortAssignments("reviewer");
        for (const auto &a : assignments) {
            out << a.reviewerId << ", " << a.submissionId << ", " << a.domain << std::endl;
        }
        out << "#Total: " << assignments.size() << std::endl;
    }

    if (!failedSubmissions.empty()) {
        out << "#SubmissionId,Domain,MissingReviews" << std::endl;
        std::sort(failedSubmissions.begin(), failedSubmissions.end(), sortByFailedSubmissionId);
        for (const auto &f : failedSubmissions) {
            out << f.submissionId << ", " << f.domain << ", " << f.missingReviews << std::endl;
        }
    }

    out.close(); // Close the output file
}

void Output::writeRAToFile(const std::string &filename) {
    std::ofstream out(filename);

    if (!criticalReviewers.empty()) {
        out << "#Risk Analysis: 1" << std::endl;
        std::sort(criticalReviewers.begin(), criticalReviewers.end());
        int i=0;
        for (const auto &r : criticalReviewers) {
            if (i==0) {out << r; i++;}
            else out << ", " << r;
        }
        out << std::endl;
    }

    out.close(); // Close the output file
}

void Output::printOutput() {
    if (!assignments.empty()) {
        std::cout << "\n=== Assignments ===\n\n";
        std::cout << "SubmissionId, ReviewerId, Match" << std::endl;
        sortAssignments("submission");
        for (const auto &a : assignments) {
            std::cout << a.submissionId << ", " << a.reviewerId << ", " << a.domain << std::endl;
        }
        std::cout << "ReviewerId,SubmissionId,Match" << std::endl;
        sortAssignments("reviewer");
        for (const auto &a : assignments) {
            std::cout << a.reviewerId << ", " << a.submissionId << ", " << a.domain << std::endl;
        }
        std::cout << "\nTotal: " << assignments.size() << std::endl;
    }

    if (!failedSubmissions.empty()) {
        std::cout << "\n=== Failed Submissions ===\n\n";
        std::cout << "SubmissionId,Domain,MissingReviews" << std::endl;
        std::sort(failedSubmissions.begin(), failedSubmissions.end(), sortByFailedSubmissionId);
        for (const auto &f : failedSubmissions) {
            std::cout << f.submissionId << ", " << f.domain << ", " << f.missingReviews << std::endl;
        }
    }
    std::cout << '\n';
}

void Output::printRiskAnalysis() {
    if (!criticalReviewers.empty()) {
        std::cout << "\n=== Risk Analysis ===\n\n";
        std::cout << "#Risk Analysis: 1" << std::endl;
        std::sort(criticalReviewers.begin(), criticalReviewers.end());
        int i=0;
        for (const auto &r : criticalReviewers) {
            if (i==0) {std::cout << r; i++;}
            else std::cout << ", " << r;
        }
        std::cout << "\n\n";
    }
}