#ifndef OUTPUT_H
#define OUTPUT_H

#include "Graph.h"
#include "Data.h"

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

class Output {
private:
    std::vector<Assignment> assignments;
    std::vector<failedSubmission> failedSubmissions;
    std::vector<int> criticalReviewers;
    bool riskAnalysisDone = false;
    int maxFlow = -1;
public:
    std::vector<Assignment> getAssignments();
    void setAssignments(const std::vector<Assignment> &assignments);

    std::vector<failedSubmission> getFailedSubmissions();
    void setFailedSubmissions(const std::vector<failedSubmission> &failsub);

    void sortAssignments(const std::string &sortBy);

    void setCriticalReviewers(const std::vector<int>& reviewers);
    const std::vector<int>& getCriticalReviewers() const;

    void setRiskAnalysisDone(bool ra);
    const bool getRiskAnalysisDone() const;

    void setMaxFlow(int maxFlow);
    int getMaxFlow() const;

    void generateOutput(Graph<int> *g, Data &data);

    void writeAToFile(const std::string &filename);
    void writeRAToFile(const std::string &filename);

    void printOutput();
    void printRiskAnalysis();
};

bool sortBySubmissionId(const Assignment &a, const Assignment &b);
bool sortByReviewerId(const Assignment &a, const Assignment &b);

bool sortByFailedSubmissionId(const failedSubmission &a, const failedSubmission &b);



#endif