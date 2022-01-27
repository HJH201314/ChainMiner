//
// Created by HJH201314 on 2022/1/27.
//
#include "pch.h"
#include "Utils.h"

string s_replace(string strSrc,
                 const string& oldStr, const string& newStr, int count) {
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