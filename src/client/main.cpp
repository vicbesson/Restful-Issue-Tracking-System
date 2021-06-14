#include <restbed>
#include <memory>
#include <string>
#include <future>//NOLINT
#include <cstdio>
#include <map>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "nlohmann/json.hpp"
#include "../../include/service/Issue.h"

// constants
const char* HOST = "localhost";
const int PORT = 1234;
std::vector<int> issueIDCache;

/**
 * Creates the request object to send to the server
 * @param service the service to call
 * @param params map of query parameters for the get request
 */
std::string create_get_request(const char* service,
const std::map<std::string, std::string>& params) {
    std::string uri = "http://";
    uri.append(HOST);
    uri.append(":");
    uri.append(std::to_string(PORT));
    uri.append("/");
    uri.append(service);

    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("GET");

    for (auto it = params.begin(); it != params.end(); ++it) {
        std::string key = it->first;
        std::string value = it->second;
        request->set_query_parameter(key, value);
    }

    auto response = restbed::Http::sync(request);
    int status_code = response->get_status_code();
    auto length = response->get_header("Content-Length", 0);
    restbed::Http::fetch(length, response);
    std::string responseStr(reinterpret_cast<char*>(response
         ->get_body().data()), length);

    return responseStr;
}

/**
 * Call after each cin
 */
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

/**
 * Check before calling an ID from the server
 */
bool issueIDExistsInCache(int id) {
    for (int i : issueIDCache) {
        if (i == id)
            return true;
    }
    return false;
}

/**
 * Priority numbers
 */
void listIssuePriorities() {
    std::cout << Issue::Priority::Low << ". Low\n";
    std::cout << Issue::Priority::Medium << ". Medium\n";
    std::cout << Issue::Priority::High << ". High\n";
    std::cout << Issue::Priority::Top << ". Top\n";
}

/**
 * Issue status numbers
 */
void listIssueStatuses() {
    std::cout << Issue::Status::New << ". New\n";
    std::cout << Issue::Status::Assigned << ". Assigned\n";
    std::cout << Issue::Status::WontFix << ". Won't Fix\n";
}

/**
 * Lists all the issues in the system
 */
void viewAllIssues() {
    std::map<std::string, std::string> params;
    std::string responseStr = create_get_request("issue/getall", params);

    issueIDCache = std::vector<int>();
    std::cout << "All Issues:\n";
    nlohmann::json issues = nlohmann::json::parse(responseStr)["issues"];
    for (auto it = issues.begin(); it != issues.end(); ++it) {
        std::cout << "ID: " << (*it)["id"] << " | ";
        std::cout << "Title: " << (*it)["title"] << " | ";
        std::cout << "Priority: " << (*it)["priority"] << " | ";
        std::cout << "Status: " << (*it)["status"] << "\n";
        issueIDCache.push_back((*it)["id"]);
    }
    std::cout << "\n";
}

/**
 * Gets an issue by ID (checks if the ID exists in the cache first)
 */
void getIssue() {
    std::cout << "Select an issue ID number: ";
    int selection = -1;
    try {
        std::string input;
        std::cin >> input;
        selection = std::stoi(input, nullptr);
    } catch (std::invalid_argument e) {}
    clearInputBuffer();
    if (!issueIDExistsInCache(selection)) {
        std::cout << "Invalid selection.\n";
        return;
    }
    std::map<std::string, std::string> params;
    params["id"] = std::to_string(selection);
    std::string responseStr = create_get_request("issue/get", params);

    nlohmann::json issue = nlohmann::json::parse(responseStr)["issue"];
    std::cout << "\nIssue at ID " << issue["id"] << ":\n";
    std::cout << "Title: " << issue["title"] << "\n";
    std::cout << "Description: " << issue["description"] << "\n";
    std::cout << "Priority: " << issue["priority"] << "\n";
    std::cout << "Status: " << issue["status"] << "\n";
}

/**
 * Adds an issue to the server
 * TODO: fix inability to have spaces in any attributes
 */
void addIssue() {
    std::string title, desc, status, priority;
    while (title.size() < 1) {
        std::cout << "Enter a title for the issue: ";
        std::cin >> title;
        clearInputBuffer();
    }
    std::cout << "Enter a description for the issue:\n";
    std::cin >> desc;
    clearInputBuffer();
    int statusnum = -1, priornum = -1;
    while (priornum < 0 || priornum > 3) {
        std::cout << "Select a priority from the list:\n";
        listIssuePriorities();
        std::cout << "Select an option number: ";
        try {
            std::string input;
            std::cin >> input;
            priornum = std::stoi(input, nullptr);
        } catch (std::invalid_argument e) {}
        clearInputBuffer();
    }
    priority = std::to_string(priornum);
    while (statusnum < 0 || statusnum > 2) {
        std::cout << "Select a status from the list:\n";
        listIssueStatuses();
        std::cout << "Select an option number: ";
        try {
            std::string input;
            std::cin >> input;
            statusnum = std::stoi(input, nullptr);
        } catch (std::invalid_argument e) {}
        clearInputBuffer();
    }
    status = std::to_string(statusnum);

    std::map<std::string, std::string> params;
    params["title"] = title;
    params["description"] = desc;
    params["priority"] = priority;
    params["status"] = status;
    std::string responseStr = create_get_request("issue/create", params);
    int resp = nlohmann::json::parse(responseStr)["id"];
    std::cout << "Issue created with ID of " << resp << ".\n";
}

/**
 * Edits an issue by ID given the new attributes
 */
void editIssue() {
    std::cout << "Select an issue ID number: ";
    int selection = -1;
    try {
        std::string input;
        std::cin >> input;
        selection = std::stoi(input, nullptr);
    } catch (std::invalid_argument e) {}
    clearInputBuffer();
    if (!issueIDExistsInCache(selection)) {
        std::cout << "Invalid selection.\n";
        return;
    }
    std::map<std::string, std::string> params;
    params["id"] = std::to_string(selection);
    std::string responseStr = create_get_request("issue/get", params);

    nlohmann::json issue = nlohmann::json::parse(responseStr)["issue"];
    std::cout << "\nEdit issue at ID " << issue["id"] << ":\n";
    std::string title, desc, priority, status;

    std::cout << "Current title: " << issue["title"] << "\n";
    std::cout << "Enter a new title: ";
    std::cin >> title;
    clearInputBuffer();

    std::cout << "Current description: " << issue["description"] << "\n";
    std::cout << "Enter a new description: ";
    std::cin >> desc;
    clearInputBuffer();

    int statusnum = -1, priornum = -1;
    std::cout << "Current priority: " << issue["priority"] << "\n";
    while (priornum < 0 || priornum > 3) {
        std::cout << "Select a priority from the list:\n";
        listIssuePriorities();
        std::cout << "Select an option number: ";
        try {
            std::string input;
            std::cin >> input;
            priornum = std::stoi(input, nullptr);
        } catch (std::invalid_argument e) {}
        clearInputBuffer();
    }
    priority = std::to_string(priornum);

    std::cout << "Current status: " << issue["status"] << "\n";
    while (statusnum < 0 || statusnum > 2) {
        std::cout << "Select a status from the list:\n";
        listIssueStatuses();
        std::cout << "Select an option number: ";
        try {
            std::string input;
            std::cin >> input;
            statusnum = std::stoi(input, nullptr);
        } catch (std::invalid_argument e) {}
        clearInputBuffer();
    }
    status = std::to_string(statusnum);

    std::map<std::string, std::string> newparams;
    newparams["id"] = std::to_string(selection);
    if (title.size() > 0) newparams["title"] = title;
    if (desc.size() > 0) newparams["description"] = desc;
    newparams["priority"] = priority;
    newparams["status"] = status;
    std::string newresponse = create_get_request("issue/edit", newparams);
    auto resp = nlohmann::json::parse(newresponse);
    std::cout << "Edited issue with ID of " << resp["id"] << ".\n";
}

/** 
 * Deletes an issue by the ID
 */
void deleteIssue() {
    std::cout << "Select an issue ID number to delete: ";
    int selection = -1;
    try {
        std::string input;
        std::cin >> input;
        selection = std::stoi(input, nullptr);
    } catch (std::invalid_argument e) {}
    clearInputBuffer();
    if (!issueIDExistsInCache(selection)) {
        std::cout << "Invalid selection.\n";
        return;
    }
    std::map<std::string, std::string> params;
    params["id"] = std::to_string(selection);
    std::string responseStr = create_get_request("issue/delete", params);
    std::string resp = nlohmann::json::parse(responseStr)["delete"];
    std::cout << "Deletion of issue with ID of " << selection << " status: "
        << resp << "\n";
}

/**
 * Issue selection options
 */
void issueMenu() {
    int selection = -1;
    while (selection < 0 || selection > 4) {
        std::cout << "\nIssues Menu\n";
        viewAllIssues();
        std::cout << "Make a selection:\n1. Get Issue Info by ID\n"
            << "2. Add Issue"
            << "\n3. Edit Issue\n4. Delete Issue by ID\n"
            << "0. Return to main\n";
        int selection = -1;
        while (selection < 0 || selection > 4) {
            std::cout << "Select an option number: ";
            try {
                std::string input;
                std::cin >> input;
                selection = std::stoi(input, nullptr);
            } catch (std::invalid_argument e) {}
            clearInputBuffer();
        }
        switch (selection) {
            case 1:
                getIssue();
                break;
            case 2:
                addIssue();
                break;
            case 3:
                editIssue();
                break;
            case 4:
                deleteIssue();
                break;
            case 0:
                return;
                break;
        }
    }
}

void commentMenu() {
    std::cout << "Not implemented.\n";
}

void userMenu() {
    std::cout << "Not implemented.\n";
}

/**
 * Main menu
 * @return 0 to exit, 1 for issue, 2 for comments, 3 for users
 */
int mainMenu() {
    int toReturn = -1;
    while (toReturn < 0 || toReturn > 3) {
        std::cout << "\nPlease select a category:\n";
        std::cout << "1. Issues\n2. Comments\n3. Users\n0. Exit\n";
        try {
            std::cout << "Select an option number: ";
            std::string input;
            std::cin >> input;
            toReturn = std::stoi(input, nullptr);
        } catch (std::invalid_argument e) {}
        clearInputBuffer();
    }
    return toReturn;
}

int main() {
    int mainMenuSelection = 0;
    do {
        mainMenuSelection = mainMenu();
        switch (mainMenuSelection) {
            case 1:
                issueMenu();
                break;
            case 2:
                commentMenu();
                break;
            case 3:
                userMenu();
                break;
        }
    } while (mainMenuSelection != 0);
}
