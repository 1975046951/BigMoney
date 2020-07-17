#pragma once
#include <cassert>
#include <sstream>
#include <vector>

#define UPDATE_STATUS(format, ...) \
    do {\
        auto *buf = new std::vector<char>(255);\
        snprintf(buf->data(), buf->size(), (format), ##__VA_ARGS__);\
        PostMsg({kUpdateStatus, buf});\
    }while(0)


#define JSON_GET(type, key, v, json)\
    do {\
    auto itr = (json).FindMember(key);\
    if (itr != (json).MemberEnd()) {\
        if (itr->value.Is##type()) {\
            (v) = itr->value.Get##type();\
        } else {\
            assert(0 && "Type mismatch, get json value fail: "#key);\
        }\
    } else {\
        assert(0 && "Cannot find key, get json value fail: "#key);\
    }\
    }while (0)

#include <string>

std::string UTF8ToANSI(const std::string &str);


#define FUND_DATA_URL "http://fundgz.1234567.com.cn/js/"

inline std::string GenerateFundUrl(const std::string& code) {
    std::ostringstream os;
    os << FUND_DATA_URL << code << ".js";
    return os.str();
}

int StringWidth(const std::string &str) ;

int FloatWidth(float f);

inline bool IsNumber(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    for (auto ch : str) {
        if (ch > '9' || ch < '0') {
            return false;
        }
    }
    return true;
}