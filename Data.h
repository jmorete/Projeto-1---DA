#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
private:
    std::vector<> reviewers;
    std::vector<> submissions;
    int minReviewersPerSubmission;
    int maxReviewersPerReviewer;
    int generateAssignments;
    int riskAnalysis;
    std::string outputFileName;
public:
    std::vector<> getReviewers() const;

    void setReviewers(const std::vector<> &reviewers);

    void addReviewer(const &reviewer);

    std::vector<> getSubmissions() const;

    void setSubmissions(const std::vector<> &submissions);

    void addSubmission(const &submission);

    int getMinReviewersPerSubmission() const;

    void setMinReviewersPerSubmission(int minReviewersPerSubmission);

    int getMaxReviewersPerReviewer() const;

    void setMaxReviewersPerReviewer(int maxReviewersPerReviewer);

    int getGenerateAssignments() const;

    void setGenerateAssignments(int generateAssignments);

    int getRiskAnalysis() const;

    void setRiskAnalysis(int riskAnalysis);

    const std::string getOutputFileName() const;

    void setOutputFileName(const std::string &outputFileName);
};

#endif 