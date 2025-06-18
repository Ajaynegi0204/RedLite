//
// Created by ajay on 18/6/25.
//
#include <include/RedisCommandHandler.h>
#include<bits/stdc++.h>
using namespace std;

void convertToUpperCase(string &str) {
    for (char &c : str) {
        if (c>='a' and c<='z') {
            c = (c-'a'+'A');
        }
    }
}

vector<string> parseRespCommand(const string &input) {
    vector<string> tokens;
    if (input.empty()) return tokens;

    if (input[0]!='*') {
        std::istringstream iss(input);
        string token;
        while (iss>>token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    size_t pos = 0;
    if (input[pos]!='*') return tokens;
    pos++;
    size_t crlf = input.find("\r\n", pos);
    if (crlf==string::npos) return tokens;
    int numTokens = stoi(input.substr(pos, crlf-pos));
    pos = crlf + 2;

    for (int i=0;i<numTokens;i++) {
        if (pos>= input.size() or input[pos]!='$') break;
        pos++;

        crlf = input.find("\r\n", pos);
        if (crlf == string::npos) break;
        int len = stoi(input.substr(pos, crlf - pos));
        pos = crlf+2 // crlf -> length 2;
        if (pos + len > input.size()) break;
        string token = input.substr(pos, len);
        tokens.push_back(token);
        pos+= (len+2);
    }
    return tokens;
}


RedisCommandHandler::RedisCommandHandler() {}



string RedisCommandHandler::processCommand(const string &command) {
    vector<string> tokens = parseRespCommand(command);
    if (tokens.empty()) return "-Error: Empty Command\r\n";

    string cmd = tokens[0];
    // convert to upperCase;
    convertToUpperCase(cmd);
    std::ostringstream response;
    // more codes;


    return response.str();

}