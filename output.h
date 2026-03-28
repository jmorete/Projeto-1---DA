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
public:
    std::vector<Assignment> getAssignments();
    void setAssignments(const std::vector<Assignment> &assignments);

    std::vector<failedSubmission> getFailedSubmissions();
    void setFailedSubmissions(const std::vector<failedSubmission> &failsub);

    void sortAssignments(const std::string &sortBy);

    void generateOutput(Graph<int> *g, Data &data);

    void writeToFile(const std::string &filename);
    void printOutput();
};

bool sortBySubmissionId(const Assignment &a, const Assignment &b);
bool sortByReviewerId(const Assignment &a, const Assignment &b);

bool sortByFailedSubmissionId(const failedSubmission &a, const failedSubmission &b);



#endif