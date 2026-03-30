#ifndef OUTPUT_H
#define OUTPUT_H

#include "Graph.h"
#include "Data.h"

/**
 * @brief Represents an assignment.
 *
 * Stores the identifiers a submission, its assigned reviewer and the matching domain.
 */
struct Assignment {
    int submissionId; /**< Unique identifier for the submission */
    int reviewerId; /**< Unique identifier for the reviewer */
    int domain; /**< Topic matched identifier */
};

/**
 * @brief Represents a submission that didn't get enough reviews.
 *
 * Stores the submission identifier, its domain, and the
 * number of reviews that still needed to get.
 */
struct failedSubmission {
    int submissionId; /**< Unique identifier for the submission */
    int domain; /**< Topic identifier */
    int missingReviews; /** Number of reviews that still needed to get */
};

/**
 * @brief Represents the data formatted to be outputted.
 *
 * Stores all the information about the generated assignments and risk analysis.
 */
class Output {
private:
    std::vector<Assignment> assignments; /**< List of all assignments */
    std::vector<failedSubmission> failedSubmissions; /**< List of all failed submissions */
    std::vector<int> criticalReviewers; /**< List of all reviewers that are necessary to guarantee assignments */
    bool riskAnalysisDone = false; /**< True if risk analysis has been performed */
    int maxFlow = -1; /**< Maximum flow of the flow network. It's set to -1 if no generation has been run */
public:
    /**
     * @brief Retrieves the list of assignments.
     * @return Copy of the vector containing all the assignments generated.
     */
    std::vector<Assignment> getAssignments();
    /**
     * @brief Updates the list of assignments.
     * @param assignments Updated list of assignments
     */
    void setAssignments(const std::vector<Assignment> &assignments);

    /**
     * @brief Retrieves the list of failed submissions.
     * @return Copy of the vector containing all the failed submissions found.
     */
    std::vector<failedSubmission> getFailedSubmissions();
    /**
     * @brief Updates the list of failed submissions.
     * @param failsub Updated list of failed submissions
     */
    void setFailedSubmissions(const std::vector<failedSubmission> &failsub);

    /**
     * @brief Sorts the list of assignments by an attribute.
     * @param sortBy Name of the attribute
     */
    void sortAssignments(const std::string &sortBy);

    /**
     * @brief Updates the list of critical reviewers.
     * @param reviewers Updated list of critical reviewers
     */
    void setCriticalReviewers(const std::vector<int>& reviewers);
    /**
     * @brief Retrieves the list of critical reviewers.
     * @return Copy of the vector containing all the critical reviewers found.
     */
    const std::vector<int>& getCriticalReviewers() const;

    /**
     * @brief Updates the flag about whether risk analysis has been done or not.
     * @param ra True if risk analysis has been done
     */
    void setRiskAnalysisDone(bool ra);
    /**
     * @brief Checks whether risk analysis has been done or not.
     * @return True if risk analysis has been done
     */
    const bool getRiskAnalysisDone() const;

    /**
     * @brief Updates the maximum flow of the flow network.
     * @param maxFlow Updated maximum flow
     */
    void setMaxFlow(int maxFlow);
    /**
     * @brief Retrieves the maximum flow of the flow network
     * @return Maximum flow
     */
    int getMaxFlow() const;

    /**
     * @brief Generates assignment and failure reports from the computed flow graph.
     *
     * Traverses the flow network after execution of the max-flow algorithm
     * and extracts meaningful results, including successful assignments
     * and submissions that did not receive the required number of reviews.
     *
     * Results are stored internally.
     */
    void generateOutput(Graph<int> *g, Data &data);

    /**
     * @brief Formats and writes assignment related data to an external file.
     * @param filename Name of the file to write to
     */
    void writeAToFile(const std::string &filename);
    /**
     * @brief Formats and writes risk analysis related data to an external file.
     * @param filename Name of the file to write to
     */
    void writeRAToFile(const std::string &filename);

    /**
     * @brief Formats and displays assignment related data in the console.
     */
    void printOutput();
    /**
     * @brief Formats and displays risk analysis related data in the console.
     */
    void printRiskAnalysis();
};

/**
 * @brief Compares two assignments by their submission identifier.
 * @param a First assignment
 * @param b Second assignment
 * @return True if the identifier of the first assignment is larger
 * than the identifier of the second.
 */
bool sortBySubmissionId(const Assignment &a, const Assignment &b);
/**
 * @brief Compares two assignments by their reviewer identifier.
 * @param a First assignment
 * @param b Second assignment
 * @return True if the identifier of the first assignment is larger
 * than the identifier of the second.
 */
bool sortByReviewerId(const Assignment &a, const Assignment &b);

/**
 * @brief Compares two failed submissions by their identifier.
 * @param a First failed submission
 * @param b Second failed submission
 * @return True if the identifier of the first failed submission is larger
 * than the identifier of the second.
 */
bool sortByFailedSubmissionId(const failedSubmission &a, const failedSubmission &b);



#endif