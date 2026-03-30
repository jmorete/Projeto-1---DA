#ifndef PARSER_H
#define PARSER_H

#include "Data.h"

/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * Trims whitespace characters (spaces, tabs, and newline characters)
 * from both ends of the input string.
 *
 * @param str Input string to trim
 * @return A new string with leading and trailing whitespace removed
 */
std::string trim(const std::string &str);

/**
 * @brief Adds a line specific error message to a list of error messages.
 * @param error Type of error
 * @param line Line where the error occurred
 * @param errors Vector where validation error messages are stored
 */
void addLineError(std::string error, int line, std::vector<std::string> &errors);
/**
 * @brief Adds an invalid parameter error message to a list of error messages.
 * @param parameter Invalid parameter
 * @param errors Vector where validation error messages are stored
 */
void addInvalidParameterError(std::string parameter, std::vector<std::string> &errors);
/**
 * @brief Adds an missing parameter error message to a list of error messages.
 * @param parameter Missing parameter
 * @param errors Vector where validation error messages are stored
 */
void addMissingParameterError(std::string parameter, std::vector<std::string> &errors);
/**
 * @brief Adds a duplicate id error message to a list of error messages.
 * @param idType Type of identifier
 * @param id Duplicated identifier
 * @param errors Vector where validation error messages are stored
 */
void addDuplicateIdError(std::string idType, int id, std::vector<std::string> &errors);

/**
 * @brief Validates the integrity and consistency of input data.
 *
 * Checks for duplicate identifiers, invalid parameter values,
 * and missing required data fields. Any detected issues are
 * recorded in the provided error list.
 *
 * @param data Input data to validate
 * @param errors Vector where validation error messages are stored
 */
void validateData(const Data &data, std::vector<std::string> &errors);

/**
 * @brief Parses, validates, and loads input data from a file.
 *
 * Processes a structured input file that is read line by line and parsed
 * into a temporary data model.
 *
 * All parsing and validation errors are collected and reported without
 * modifying the existing data. The input data is only committed to the
 * provided Data object if no errors are detected.
 *
 * @param filename Path to the input file
 * @param data Data object to populate on successful parsing
 * @return True if parsing and validation complete successfully; false otherwise
 */
bool parse(const std::string &filename, Data &data);

#endif



