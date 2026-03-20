#include "Data.h"

std::vector<> Data::getReviewers() const {
    return reviewers;
}

void Data::setReviewers(const std::vector<> &reviewers) {
    this->reviewers = reviewers;
}

void Data::addReviewer(const &reviewer) {
    this->reviewers.push_back(reviewer);
}

std::vector<> Data::getSubmissions() const {
    return submissions;
}

void Data::setSubmissions(const std::vector<> &submissions) {
    this->submissions = submissions;
}

void Data::addSubmission(const &submission) {
    this->submissions.push_back(submission);
}

int Data::getMinReviewersPerSubmission() const {
    return minReviewersPerSubmission;
}

void Data::setMinReviewersPerSubmission(int minReviewersPerSubmission) {
    this->minReviewersPerSubmission = minReviewersPerSubmission;
}

int Data::getMaxReviewersPerReviewer() const {
    return maxReviewersPerReviewer;
}

void Data::setMaxReviewersPerReviewer(int maxReviewersPerReviewer) {
    this->maxReviewersPerReviewer = maxReviewersPerReviewer;
}

int Data::getGenerateAssignments() const {
    return generateAssignments;
}

void Data::setGenerateAssignments(int generateAssignments) {
    this->generateAssignments = generateAssignments;
}

int Data::getRiskAnalysis() const {
    return riskAnalysis;
}

void Data::setRiskAnalysis(int riskAnalysis) {
    this->riskAnalysis = riskAnalysis;
}

const std::string Data::getOutputFileName() const {
    return outputFileName;
}

void Data::setOutputFileName(const std::string &outputFileName) {
    this->outputFileName = outputFileName;
}

