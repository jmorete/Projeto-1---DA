#include "Data.h"

#include <iostream>

using namespace std;

vector<Reviewer> Data::getReviewers() const {
    return reviewers;
}

void Data::setReviewers(const vector<Reviewer> &reviewers) {
    this->reviewers = reviewers;
}

void Data::addReviewer(const Reviewer &reviewer) {
    this->reviewers.push_back(reviewer);
}

vector<Submission> Data::getSubmissions() const {
    return submissions;
}

void Data::setSubmissions(const vector<Submission> &submissions) {
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
}

int Data::getMaxReviewsPerReviewer() const {
    return maxReviewsPerReviewer;
}

void Data::setMaxReviewsPerReviewer(int maxReviewsPerReviewer) {
    this->maxReviewsPerReviewer = maxReviewsPerReviewer;
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

const string Data::getOutputFileName() const {
    return outputFileName;
}

void Data::setOutputFileName(const string &outputFileName) {
    this->outputFileName = outputFileName;
}

int Data::getPrimaryDomain(const int submissionId) {
    for (const auto &submission : submissions) {
        if (submission.id == submissionId) {
            return submission.primaryTopic;
        }
    }
    return -1;
}

int Data::getSecondaryDomain(const int submissionId){
    for (const auto &submission : submissions) {
        if (submission.id == submissionId) {
            return submission.secondaryTopic;
        }
    }
    return -1;
}

void Data::printSubmissions() const {
    cout << "\n=== Submissions ===\n\n";
    cout << "Id, Title, Authors, E-mail, Primary Topic, Secondary Topic\n";
    for (const auto& sub : getSubmissions()) {
        cout << sub.id << ", " << sub.title << ", " << sub.author << ", " << sub.email << ", " << sub.primaryTopic;
        if (sub.secondaryTopic != -1) cout << ", " << sub.secondaryTopic;
        cout << '\n';
    }
    cout << '\n';
}

void Data::printReviewers() const {
    cout << "\n=== Reviewers ===\n\n";
    cout << "Id, Name, E-mail, Primary Expertise, Secondary Expertise\n";
    for (const auto& rev : getReviewers()) {
        cout << '-' << rev.id << ", " << rev.name << ", " << rev.email << ", " << rev.primaryExpertise;
        if (rev.secondaryExpertise != -1) cout << ", " << rev.secondaryExpertise;
        cout << '\n';
    }
    cout << '\n';
}

void Data::printParameters() const {
    cout << "\n=== Parameters ===\n\n";
    cout << "Min Reviews per Submission: " << getMinReviewsPerSubmission() << '\n';
    cout << "Max Reviews per Reviewer: " << getMaxReviewsPerReviewer() << '\n';
    cout << '\n';
}

