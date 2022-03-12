#pragma once
#include "pch.h"

#ifndef CHAINMINER_UTILS_HPP
#define CHAINMINER_UTILS_HPP

inline string s_replace(string strSrc,
                 const string& oldStr, const string& newStr, int count = -1) {
    string strRet = strSrc;
    size_t pos = 0;
    int l_count = 0;
    if (-1 == count)
        count = strRet.size();
    while ((pos = strRet.find(oldStr, pos)) != string::npos)
    {
        strRet.replace(pos, oldStr.size(), newStr);
        if (++l_count >= count) break;
        pos += newStr.size();
    }
    return strRet;
}

template <typename T>
inline bool v_contains(vector<T>& v, const T f) {
    for (auto it = v.begin(); it != v.end(); it++) {
        if (*it == f) return true;
    }
    return false;
}

#endif //CHAINMINER_UTILS_HPP