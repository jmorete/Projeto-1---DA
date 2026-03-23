#include "output.h"
#include <id.h>
#include <fstream>
#include <iostream>

struct Assignment {
    int submissionId;
    int reviewerId;
    int domain;
};

struct failedSubmission {
    int submissionId;
    int domain;
    int missingReviews;
};

bool sortBySubmissionId(const Assignment &a, const Assignment &b) {
    return a.submissionId < b.submissionId;
}

bool sortByReviewerId(const Assignment &a, const Assignment &b) {
    return a.reviewerId < b.reviewerId;
}

void sortAssignments(std::vector<Assignment> &assignments, const std::string &sortBy) {
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

int getPrimaryDomain(int submissionId, const Data &data) {
    for (const auto &submission : data.getSubmissions()) {
        if (submission.id == submissionId) {
            return submission.primaryTopic;
        }
    }
    return -1; 
}

int getSecondaryDomain(int submissionId, const Data &data){
    for (const auto &submission : data.getSubmissions()) {
        if (submission.id == submissionId) {
            return submission.secondaryTopic;
        }
    }
    return -1; 
}
void writeOutput(const std::string &filename, Graph<int> *g, const Data &data) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    std::vector<Assignment> assignments;
    std::vector<failedSubmission> failedSubmissions;
    for (auto v : g->getVertexSet()) {
        int submissionId = v->getInfo();
        if (!(submissionId & REVIEWER_MASK)){
            if ((submissionId & PRIMARY_TOPIC_MASK) || (submissionId & SECONDARY_TOPIC_MASK)) { 
                for (auto e : v->getAdj()) {
                    if (e->getFlow() > 0) { 
                        if (submissionId & PRIMARY_TOPIC_MASK){
                            assignments.push_back({submissionId & ID_MASK, e->getDest()->getInfo() & ID_MASK, getPrimaryDomain(submissionId & ID_MASK, data)});
                        }
                        else {
                            assignments.push_back({submissionId & ID_MASK, e->getDest()->getInfo() & ID_MASK, getSecondaryDomain(submissionId & ID_MASK, data)});
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
                        failedSubmissions.push_back({submissionId & ID_MASK, getPrimaryDomain(submissionId & ID_MASK, data), requiredReviews - assignedReviews});
                    }
                }
            }
        }
    }

    if (!assignments.empty()) {
        out << "#SubmissionId,ReviewerId,Match" << std::endl;
        sortAssignments(assignments, "submission");
        for (const auto &a : assignments) {
            out << a.submissionId << ", " << a.reviewerId << ", " << a.domain << std::endl;
        }
        out << "#ReviewerId,SubmissionId,Match" << std::endl;
        sortAssignments(assignments, "reviewer");
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