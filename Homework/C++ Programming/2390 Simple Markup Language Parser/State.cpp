// MegaShow
#include "Parser.hpp"
#include "State.hpp"

State *DataState::_instance = NULL;

State *DataState::getInstance() {
    if(_instance == NULL) {
        _instance = new DataState();
    }
    return _instance;
}

void DataState::destroyInstance() {
    if(_instance != NULL) {
        delete _instance;
        _instance = NULL;
    }
}

void DataState::handleOneChar(Parser *parser, char ch) {
    if(ch == '<') {
        parser->setState(TagNameState::getInstance());
        std::string::iterator it = _cache.end();
        it--;
        while(_cache.size() && (*it) == ' ') {
            _cache.erase(it);
            it--;
        }
        if(_cache.size()) {
            emit(parser->getBulider());
        }
    }
    else if(_cache.size() || ch != ' ') {
        _cache += ch;
    }
}

void DataState::emit(Bulider *dest) {
    Token t;
    t.type = "DATA";
    t.content = _cache;
    dest->handleOneToken(t);
    _cache.clear();
}



State *TagNameState::_instance = NULL;

State *TagNameState::getInstance() {
    if(_instance == NULL) {
        _instance = new TagNameState();
    }
    return _instance;
}

void TagNameState::destroyInstance() {
    if(_instance != NULL) {
        delete _instance;
        _instance = NULL;
    }
}

void TagNameState::handleOneChar(Parser *parser, char ch) {
    if(ch == '>') {
        parser->setState(DataState::getInstance());
        if(_cache.size()) {
            emit(parser->getBulider());
        }
    }
    else {
        _cache += ch;
    }
}

void TagNameState::emit(Bulider *dest) {
    Token t;
    if(_cache[0] == '/') {
        _cache.erase(_cache.begin());
        t.type = "CLOSE_TAG";
        t.content = _cache;
    }
    else {
        t.type = "OPEN_TAG";
        t.content = _cache;
    }
    if(_cache.size()) {
        dest->handleOneToken(t);
        _cache.clear();
    }
}