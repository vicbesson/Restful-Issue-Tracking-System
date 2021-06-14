#include <restbed>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include "nlohmann/json.hpp"
#include "../../include/service/KnickKnacker.h"
#include "../../include/service/Issue.h"

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

/**
* Handle a GET request in the issue resource for a single issue
* @param session The request session.
*/
void issue_get_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    if (request->has_query_parameter("id")) {
        try {
            KnickKnacker* kk = new KnickKnacker();
            unsigned int id = std::stoi(request->get_query_parameter("id"),
                nullptr);
            Issue i = kk->getIssueByID(id);
            delete kk;
            nlohmann::json object;
            object["id"] = i.getID();
            object["title"] = i.getTitle();
            object["status"] = i.getStatus();
            object["priority"] = i.getPriority();
            object["description"] = i.getDescription();
            object["os"] = i.getOS();
            resultJSON["issue"] = object;
        } catch (std::invalid_argument e) {}
    }

    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a GET request for all issues
* @param session The request session.
*/
void issue_getall_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    KnickKnacker* kk = new KnickKnacker();
    nlohmann::json issues = nlohmann::json::array();
    std::vector<Issue> issuelist = kk->getAllIssues();
    delete kk;
    for (Issue i : issuelist) {
        nlohmann::json object;
        object["id"] = i.getID();
        object["title"] = i.getTitle();
        object["status"] = i.getStatus();
        object["priority"] = i.getPriority();
        object["description"] = i.getDescription();
        object["os"] = i.getOS();
        issues.push_back(object);
    }

    resultJSON["issues"] = issues;
    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a request to create an issue
* @param session The request session.
*/
void issue_create_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    KnickKnacker* kk = new KnickKnacker();
    std::string title;
    std::string desc;
    Issue::Status status;
    Issue::Priority priority;

    if (request->has_query_parameter("title")) {
        title = request->get_query_parameter("title");
    }
    if (request->has_query_parameter("description")) {
        desc = request->get_query_parameter("description");
    }
    if (request->has_query_parameter("status")) {
        try {
            status = (Issue::Status) std::stoi(
                request->get_query_parameter("status"), nullptr);
        } catch (std::invalid_argument e) {}
    }
    if (request->has_query_parameter("priority")) {
        try {
            priority = (Issue::Priority) std::stoi(
                request->get_query_parameter("priority"), nullptr);
        } catch (std::invalid_argument e) {}
    }

    unsigned int id = kk->createIssue(title, desc, status, priority);
    delete kk;
    resultJSON["id"] = id;

    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a request to edit an issue
* @param session The request session.
*/
void issue_edit_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    KnickKnacker* kk = new KnickKnacker();
    std::string title;
    std::string desc;
    Issue::Status status;
    Issue::Priority priority;
    Issue issue;

    if (request->has_query_parameter("id")) {
        try {
            unsigned int id = std::stoi(
                request->get_query_parameter("id"), nullptr);
            issue = kk->getIssueByID(id);
            status = issue.getStatusEnum();
            priority = issue.getPriorityEnum();
        } catch (std::invalid_argument e) {}
    }
    if (request->has_query_parameter("title")) {
        title = request->get_query_parameter("title");
    }
    if (request->has_query_parameter("description")) {
        desc = request->get_query_parameter("description");
    }
    if (request->has_query_parameter("status")) {
        try {
            status = (Issue::Status) std::stoi(
                request->get_query_parameter("status"), nullptr);
        } catch (std::invalid_argument e) {}
    }
    if (request->has_query_parameter("priority")) {
        try {
            priority = (Issue::Priority) std::stoi(
                request->get_query_parameter("priority"), nullptr);
        } catch (std::invalid_argument e) {}
    }

    kk->updateIssue(issue.getID(), title, desc, status, priority);
    delete kk;
    resultJSON["id"] = issue.getID();

    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a request to delete an issue
* @param session The request session.
*/
void issue_delete_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    bool deleteissue;
    if (request->has_query_parameter("id")) {
        try {
            KnickKnacker* kk = new KnickKnacker();
            unsigned int id = std::stoi(request->get_query_parameter("id"),
                nullptr);
            deleteissue = kk->deleteIssueByID(id);
            delete kk;
        } catch (std::invalid_argument e) {}
    }
    resultJSON["delete"] = deleteissue ? "success" : "fail";
    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a GET request in the comment resource
* @param session The request session.
*/
void comment_get_method_handler(
    const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();

    nlohmann::json resultJSON;
    resultJSON["code"] = 10;
    resultJSON["type"] = "comment";
    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

/**
* Handle a GET request in the user resource
* @param session The request session.
*/
void user_get_method_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    nlohmann::json resultJSON;
    resultJSON["code"] = 10;
    resultJSON["type"] = "user";
    std::string response = resultJSON.dump();

    session->close(restbed::OK,
    response, {
    { "Content-Length", std::to_string(response.length()) },
    CLOSE_CONNECTION });
}

int main(const int, const char**) {
    // Setup service and request handlers
    auto issue_resource_getall = std::make_shared<restbed::Resource>();
    issue_resource_getall->set_path("/issue/getall");
    issue_resource_getall->set_method_handler("GET",
        issue_getall_method_handler);

    auto issue_resource_create = std::make_shared<restbed::Resource>();
    issue_resource_create->set_path("/issue/create");
    issue_resource_create->set_method_handler("GET",
        issue_create_method_handler);

    auto issue_resource_get = std::make_shared<restbed::Resource>();
    issue_resource_get->set_path("/issue/get");
    issue_resource_get->set_method_handler("GET",
        issue_get_method_handler);

    auto issue_resource_edit = std::make_shared<restbed::Resource>();
    issue_resource_edit->set_path("/issue/edit");
    issue_resource_edit->set_method_handler("GET",
        issue_edit_method_handler);

    auto issue_resource_delete = std::make_shared<restbed::Resource>();
    issue_resource_delete->set_path("/issue/delete");
    issue_resource_delete->set_method_handler("GET",
        issue_delete_method_handler);

    auto comment_resource = std::make_shared<restbed::Resource>();
    comment_resource->set_path("/comment");
    comment_resource->set_method_handler("GET",
        comment_get_method_handler);

    auto user_resource = std::make_shared<restbed::Resource>();
    user_resource->set_path("/user");
    user_resource->set_method_handler("GET",
        user_get_method_handler);

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);
    settings->set_default_header("Access-Control-Allow-Origin", "*");

    // Publish and start service
    restbed::Service service;
    service.publish(issue_resource_getall);
    service.publish(issue_resource_create);
    service.publish(issue_resource_get);
    service.publish(issue_resource_delete);
    service.publish(issue_resource_edit);
    service.publish(comment_resource);
    service.publish(user_resource);

    service.start(settings);
    return EXIT_SUCCESS;
}
