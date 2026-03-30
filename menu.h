#ifndef MENU_H
#define MENU_H
#include "Graph.h"
#include "output.h"

/**
 * @brief Provides a console-based user interface for interacting with the program.
 *
 * Handles user input and displays menu options, allowing the user to load data,
 * configure parameters, trigger assignment generation, and view results.
 * Acts as the main interaction layer between the user and the underlying logic.
 */
class Menu {
private:
    std::string file; /**< Name of the input file that the data that is in use was parsed from */
    int state = 0; /**< Current state of the menu. Used to switch between sub-menus */
    Data data = {}; /**< Data that has been loaded and can be used. Is empty if no file has been loaded yet */
    Output output = {}; /**< Output that has been generated and can be used. Is empty if no generation has been performed yet */
    bool writtenAssignments = false; /**< True if the results of an assignment generation have already been written to the output file, false otherwise */
    bool writtenRiskAnalysis = false; /**< True if the results of a risk analysis have already been written to the output file, false otherwise */
public:
    /**
     * @brief Retrieves the state identifier used to identify sub-menus.
     * @return State identifier
     */
    int getState() const;
    /**
     * @brief Updates the state identifier used to identify sub-menus.
     * @param state Updated state identifier
     */
    void setState(int state);

    /**
     * @brief Retrieves the name of the input file that the data that is in use was parsed from.
     * @return Name of the file
     */
    std::string getFile();
    /**
     * @brief Updates the name of the input file that the data that is in use was parsed from.
     * @param file Updated file name
     */
    void setFile(const std::string &file);

    /**
     * @brief Retrieves the data that is currently loaded.
     * @return Currently loaded data
     */
    Data getData();
    /**
     * @brief Updates the data that is currently loaded.
     *
     * Changes the currently loaded data to a new one and resets the output to avoid storing outdated data.
     *
     * @param data Updated data
     */
    void setData(const Data &data);

    /**
     * @brief Retrieves the current output related data.
     * @return Output data
     */
    Output getOutput();
    /**
     * @brief Updates the current output related data.
     * @param out Updated output data
     */
    void setOutput(const Output &out);

    /**
     * @brief Checks if a file is loaded and prints an error message if it isn't.
     * @return True if a file is loaded, false otherwise
     */
    bool hasFile() const;
    /**
     * @brief Checks if assignments have been generated and prints an error message if they haven't.
     * @return True if assignments have been generated, false otherwise
     */
    bool hasAssigned();
    /**
     * @brief Checks if risk analysis has been run and prints an error message if it hasn't.
     * @return True if risk analysis has been run, false otherwise
     */
    bool hasRiskAnalysis() const;

    /**
     * @brief Shows the user they can input text, waits until they do to and retrieves it.
     * @return Inputted string
     */
    static std::string getInput();
    /**
     * @brief Tells the user they can press Enter to continue and waits until they do.
     */
    static void waitForEnter();

    /**
     * @brief Executes the full assignment generation pipeline.
     *
     * Builds the flow network from the input data, computes the maximum flow
     * using the Edmonds-Karp algorithm, generates the final assignment output,
     * and stores the resulting output data.
     *
     * Also prints a status message indicating success and reports if some
     * submissions could not be assigned.
     *
     * Complexity: O(V * E^2), where V is the number of vertices and E is the number of edges
     */
    void runAssignments();
    /**
     * @brief Performs risk analysis of the flow network with respect to reviewers.
     *
     * Computes the baseline maximum flow, then iteratively removes each reviewer
     * and recomputes the flow to determine its impact on system capacity.
     *
     * Reviewers whose removal decreases the maximum flow are classified as
     * critical, as they act as bottlenecks in the assignment network.
     *
     * Results are stored in the output data.
     * Also prints a status message indicating success and reports if
     * there are any critical reviewers.
     *
     * Complexity: O(R * V * E^2), where R is the number of reviewers, V is the number of vertices and E is the number of edges
     */
    void runRiskAnalysis();

    /**
     * @brief Runs the main interactive menu loop.
     *
     * Continuously displays the menu and dispatches execution to the appropriate
     * submenu based on the current application state. The loop terminates when
     * the state is set to -1.
     */
    void run();
    /**
     * @brief Handles the main menu interface.
     *
     * Allows navigation to all major system functionalities such as
     * loading input data, viewing stored information, generating assignments,
     * performing analysis, and exporting results.
     * It also allows the user to run the full file's pipeline automatically.
     *
     * Updates the menu state based on user selection and reports
     * errors or successful operations to the console.
     */
    void mainMenu();
    /**
     * @brief Provides options for loading input data files.
     *
     * Allows the user to load and parse external data files containing
     * submissions, reviewers, and configuration parameters.
     *
    * Updates the internal data model upon successful loading and reports
     * errors or successful operations to the console.
     */
    void loadFileMenu();
    /**
     * @brief Displays and allows inspection of loaded input data.
     *
     * Provides options to view reviewers, submissions, parameters and
     * configuration controls currently stored in the system while also reporting
     * errors or successful operations to the console.
     */
    void viewDataMenu();
    /**
     * @brief Allows the user to run operations manually.
     *
     * Provides the option to run assignment generation and risk analysis manually
     * even if the configuration says it isn't going to.
     *
     * Updates the output data and reports errors or
     * successful operations to the console.
     */
    void manualMenu();
    /**
     * @brief Displays and allows inspection of generated output data.
     *
     * Provides options to view the assignments and risk analysis currently stored
     * in the system while also reporting errors or successful operations to the console.
     */
    void viewOutputMenu();
    /**
     * @brief Handles exporting results to an external file.
     *
     * Allows the user to save computed assignments and analysis results
     * to an output file. It also reports errors or successful operations to the console.
     */
    void exportMenu();

    /**
     * @brief Displays the user interface for the current menu state.
     *
     * Acts as the presentation layer of the console interface, printing
     * the available options associated with the active state to standard output.
     */
    void display() const;
};



#endif //MENU_H
