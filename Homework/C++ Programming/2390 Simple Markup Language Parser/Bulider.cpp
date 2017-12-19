// MegaShow
#include <iostream>
#include "Bulider.hpp"

Bulider* Bulider::_instance = NULL;

Bulider *Bulider::getInstance() {
    if(_instance == NULL) {
        _instance = new Bulider();
    }
    return _instance;
}

void Bulider::destroyInstance() {
    if(_instance != NULL) {
        delete _instance;
        _instance = NULL;
    }
}

// check the token's validity in current nesting structure
// if valid, record it in _tokens, if not, set _error true
void Bulider::handleOneToken(Token token) {
    if(token.type == "CLOSE_TAG") {
        if(_stack.size() && _stack.top().content == token.content) {
            _stack.pop();
        }
        else {
            _error = true;
        }
    }
    else if(token.type == "OPEN_TAG") {
        token.depth = _stack.size();
        _stack.push(token);
        _tokens.push_back(token);
    }
    else {
        token.depth = _stack.size();
        _tokens.push_back(token);
    }
}

void Bulider::display() {
    if(_error || _stack.size() != 0) {
        std::cout << "INVALID INPUT" << std::endl;
        return;
    }
    for(int i = 0; i < _tokens.size(); i++) {
        for(int j = 0; j < _tokens[i].depth; j++) {
            std::cout << "  ";
        }
        if(_tokens[i].type == "OPEN_TAG") {
            std::cout << _tokens[i].content << ":" << std::endl;
        }
        else {
            std::cout << _tokens[i].content << std::endl;
        }
    }
}