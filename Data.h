#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct Submission {
    int id;
    std::string title;
    std::string author;
    std::string email;
    int primaryTopic;
    int secondaryTopic;
};

struct Reviewer {
    int id;
    std::string name;
    std::string email;
    int primaryExpertise;
    int secondaryExpertise;
};

class Data {
private:
    std::vector<Reviewer> reviewers;
    std::vector<Submission> submissions;
    int minReviewersPerSubmission;
    int maxReviewersPerReviewer;
    int generateAssignments;
    int riskAnalysis;
    std::string outputFileName;
public:
    std::vector<Reviewer> getReviewers() const;

    void setReviewers(const std::vector<Reviewer> &reviewers);

    void addReviewer(const Reviewer &reviewer);

    std::vector<Submission> getSubmissions() const;

    void setSubmissions(const std::vector<Submission> &submissions);

    void addSubmission(const Submission &submission);

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