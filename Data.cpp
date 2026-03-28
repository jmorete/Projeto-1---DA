#include "Data.h"

std::vector<Reviewer> Data::getReviewers() const {
    return reviewers;
}

void Data::setReviewers(const std::vector<Reviewer> &reviewers) {
    this->reviewers = reviewers;
}

void Data::addReviewer(const Reviewer &reviewer) {
    this->reviewers.push_back(reviewer);
}

std::vector<Submission> Data::getSubmissions() const {
    return submissions;
}

void Data::setSubmissions(const std::vector<Submission> &submissions) {
    this->submissions = submissions;
}

void Data::addSubmission(const Submission &submission) {
    this->submissions.push_back(submission);
}

int Data::getMinReviewsPerSubmission() const {
    return minReviewsPerSubmission;
}

void Data::setMinReviewsPerSubmission(int minReviewsPerSubmission) {
    this->minReviewsPerSubmission = minReviewsPerSubmission;
    minReviewsPerSubmissionSet = true;
}

bool Data::minReviewsPerSubmissionIsSet() const {
    return minReviewsPerSubmissionSet;
}

int Data::getMaxReviewsPerReviewer() const {
    return maxReviewsPerReviewer;
}

void Data::setMaxReviewsPerReviewer(int maxReviewsPerReviewer) {
    this->maxReviewsPerReviewer = maxReviewsPerReviewer;
    maxReviewsPerReviewerSet = true;
}

bool Data::maxReviewsPerReviewerIsSet() const {
    return maxReviewsPerReviewerSet;
}

int Data::getGenerateAssignments() const {
    return generateAssignments;
}

void Data::setGenerateAssignments(int generateAssignments) {
    this->generateAssignments = generateAssignments;
    generateAssignmentsSet = true;
}

bool Data::generateAssignmentsIsSet() const {
    return generateAssignmentsSet;
}

int Data::getRiskAnalysis() const {
    return riskAnalysis;
}

void Data::setRiskAnalysis(int riskAnalysis) {
    this->riskAnalysis = riskAnalysis;
    riskAnalysisSet = true;
}

bool Data::riskAnalysisIsSet() const {
    return riskAnalysisSet;
}

const std::string Data::getOutputFileName() const {
    return outputFileName;
}

void Data::setOutputFileName(const std::string &outputFileName) {
    this->outputFileName = outputFileName;
}

