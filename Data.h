#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

/**
 * @brief Represents an article submission.
 *
 * Stores details about a submission and its author.
 */
struct Submission {
    int id; /**< Unique identifier for the submission */
    std::string title; /**< Title of the submission */
    std::string author; /**< Name of the author */
    std::string email; /**< Email contact of the author */
    int primaryTopic; /**< Primary topic identifier */

    /**
     * @brief Secondary topic identifier (optional).
     *
     * Value is -1 when no topic is assigned.
     */
    int secondaryTopic = -1;
};

/**
 * @brief Represents a reviewer
 *
 * Stores data about them and their expertises, which will be used for assigning submissions with matching topics.
 */
struct Reviewer {
    int id; /**< Unique identifier for the reviewer */
    std::string name; /**< Name of the reviewer */
    std::string email; /**< Email contact of the reviewer */
    int primaryExpertise; /**< Primary expertise topic identifier */

    /**
     * @brief Secondary expertise topic identifier (optional).
     *
     * Value is -1 when no expertise is assigned.
     */
    int secondaryExpertise = -1;
};

/**
 * @brief Represents the data parsed from an input file.
 *
 * Stores all the information about the submissions, reviewers and all the parameters for the assignments.
 */
class Data {
private:
    std::vector<Reviewer> reviewers; /**< List of all reviwers */
    std::vector<Submission> submissions; /**< List all submissions */
    int minReviewsPerSubmission; /**< Minimum number of reviews required per submission */
    bool minReviewsPerSubmissionSet = false; /**< True if the minimum number of reviews per submission is defined, false otherwise */
    int maxReviewsPerReviewer; /**< Maximum number of reviews a reviewer can review */
    bool maxReviewsPerReviewerSet = false; /**< True if the maximum number of reviews per reviewer is defined, false otherwise */

    /**
     * @brief Controls the generation of an assignment of the submissions to reviewers.
     *
     * 0 means the assignment is still carried out but not reported.
     *
     * 1 means the assignment will exclusively consider the Primary Submission domains of the submissions
     * and the Primary Expertise domains of the experts.
     *
     * 2 means the assignment will consider the Primary and, whenever defined, the Secondary Submission domains
     * but exclusively the Primary Expertise domain of the reviewers.
     *
     * 3 means all Primary and whenever defined, Secondary domains of either the submissions or the reviewers
     * can be considered to meet the minimum number of reviews per submission
     * and the maximum number of reviews per reviewer.
     *
     */
    int generateAssignments;
    bool generateAssignmentsSet = false; /**< True if the assignment generation control is defined, false otherwise */

    /**
     * @brief Determines the type of risk analysis to be carried out.
     *
     * 0 means no risk analysis is carried out.
     *
     * 1 means risk analysis is carried out with 1 risky reviewer.
     *
     * K (K>1) means risk analysis is carried out with K risky reviewers. (Not Implemented)
     *
     */
    int riskAnalysis;
    bool riskAnalysisSet = false; /**< True if the type of risk analysis is defined, false otherwise */
    std::string outputFileName = "output.csv"; /**< File where results can be written */
public:
    /**
     * @brief Retrieves the list of reviewers.
     * @return Copy of the vector containing all the reviewers in the data.
     */
    std::vector<Reviewer> getReviewers() const;

    /**
     * @brief Updates the list of reviewers.
     * @param reviewers Updated list of reviewers
     */
    void setReviewers(const std::vector<Reviewer> &reviewers);

    /**
     * @brief Adds a reviewer to the list of reviewers.
     * @param reviewer Reviewer to add to the list
     */
    void addReviewer(const Reviewer &reviewer);

    /**
     * @brief Removes a reviewer from the list of reviewers.
     * @param reviewer_id Identifier for the reviewer to remove
     */
    void removeReviewer(const int &reviewer_id);

    /**
     * @brief Retrieves the list of submissions.
     * @return Copy of the vector containing all the submissions in the data.
     */
    std::vector<Submission> getSubmissions() const;

    /**
     * @brief Updates the list of submissions.
     * @param submissions Updated list of submissions
     */
    void setSubmissions(const std::vector<Submission> &submissions);

    /**
     * @brief Adds a submission to the list of submissions.
     * @param submission Submission to add to the list
     */
    void addSubmission(const Submission &submission);

    /**
     * @brief Retrieves the minimum number of reviews required per submission.
     * @return Minimum review count
     */
    int getMinReviewsPerSubmission() const;

    /**
     * @brief Updates the minimum number of reviews required per submission.
     * @param minReviewsPerSubmission Updated number
     */
    void setMinReviewsPerSubmission(int minReviewsPerSubmission);

    /**
     * @brief Checks if the minimum number of reviews required per submission is set.
     * @return True if the value is defined, false otherwise
     */
    bool minReviewsPerSubmissionIsSet() const;

    /**
     * @brief Retrieves the maximum number of reviews a reviewer can review.
     * @return Maximum review capacity
     */
    int getMaxReviewsPerReviewer() const;

    /**
     * @brief Updates the maximum number of reviews a reviewer can review.
     * @param maxReviewsPerReviewer Updated number
     */
    void setMaxReviewsPerReviewer(int maxReviewsPerReviewer);

    /**
     * @brief Checks if the maximum number of reviews a reviewer can review is set.
     * @return True if the capacity is defined, false otherwise
     */
    bool maxReviewsPerReviewerIsSet() const;

    /**
     * @brief Retrieves the control number for the assignment generation.
     * @return Control number
     */
    int getGenerateAssignments() const;

    /**
     * @brief Updates the control number for the assignment generation.
     * @param generateAssignments Updated number
     */
    void setGenerateAssignments(int generateAssignments);

    /**
     * @brief Checks if the control number for the assignment generation is set.
     * @return True if the control number is defined, false otherwise
     */
    bool generateAssignmentsIsSet() const;

    /**
     * @brief Retrieves the type of risk analysis to be carried out.
     * @return Type of risk analysis
     */
    int getRiskAnalysis() const;

    /**
     * @brief Updates the type of risk analysis to be carried out.
     * @param riskAnalysis Updated type
     */
    void setRiskAnalysis(int riskAnalysis);

    /**
     * @brief Checks if the type of risk analysis to be carried out is set.
     * @return True if the type of risk analysis is defined, false otherwise
     */
    bool riskAnalysisIsSet() const;

    /**
     * @brief Retrieves the name of the output file.
     * @return Name of the file
     */
    const std::string getOutputFileName() const;

    /**
     * @brief Updates the name of the output file.
     * @param outputFileName Updated name
     */
    void setOutputFileName(const std::string &outputFileName);

    /**
     * @brief Retrieves the primary domain identifier of a submission.
     * @param submissionId Identifier of the submission to get the domain from
     * @return Primary domain identifier of the submission or -1 if the submission isn't found
     */
    int getPrimaryDomain(int submissionId);
    /**
     * @brief Retrieves the secondary domain identifier of a submission.
     * @param submissionId Identifier of the submission to get the domain from
     * @return Secondary domain identifier of the submission or -1 if the submission isn't found
     */
    int getSecondaryDomain(int submissionId);

    /**
     * @brief Formats and displays the details of every submission in the console.
     */
    void printSubmissions() const;
    /**
     * @brief Formats and displays the details of every reviewer in the console.
     */
    void printReviewers() const;
    /**
     * @brief Displays the assignment generation parameters in the console.
     */
    void printParameters() const;
    /**
     * @brief Displays the file's configuration for generating assignments ans running risk analysis.
     */
    void printControls() const;
};

#endif 