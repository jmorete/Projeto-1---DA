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
    int secondaryTopic = -1; // default value indicating no secondary topic
};

struct Reviewer {
    int id;
    std::string name;
    std::string email;
    int primaryExpertise;
    int secondaryExpertise = -1; // default value indicating no secondary expertise
};

class Data {
private:
    std::vector<Reviewer> reviewers;
    std::vector<Submission> submissions;
    int minReviewsPerSubmission;
    bool minReviewsPerSubmissionSet = false;
    int maxReviewsPerReviewer;
    bool maxReviewsPerReviewerSet = false;
    int generateAssignments;
    bool generateAssignmentsSet = false;
    int riskAnalysis;
    bool riskAnalysisSet = false;
    std::string outputFileName = "output.csv"; // default filename
public:
    std::vector<Reviewer> getReviewers() const;

    void setReviewers(const std::vector<Reviewer> &reviewers);

    void addReviewer(const Reviewer &reviewer);

    void removeReviewer(const int &reviewer_id); //todo

    std::vector<Submission> getSubmissions() const;

    void setSubmissions(const std::vector<Submission> &submissions);

    void addSubmission(const Submission &submission);

    int getMinReviewsPerSubmission() const;

    void setMinReviewsPerSubmission(int minReviewsPerSubmission);

    bool minReviewsPerSubmissionIsSet() const;

    int getMaxReviewsPerReviewer() const;

    void setMaxReviewsPerReviewer(int maxReviewsPerReviewer);

    bool maxReviewsPerReviewerIsSet() const;

    int getGenerateAssignments() const;

    void setGenerateAssignments(int generateAssignments);

    bool generateAssignmentsIsSet() const;

    int getRiskAnalysis() const;

    void setRiskAnalysis(int riskAnalysis);

    bool riskAnalysisIsSet() const;

    const std::string getOutputFileName() const;

    void setOutputFileName(const std::string &outputFileName);

    int getPrimaryDomain(int submissionId);
    int getSecondaryDomain(int submissionId);

    void printSubmissions() const;
    void printReviewers() const;
    void printParameters() const;
};

#endif 