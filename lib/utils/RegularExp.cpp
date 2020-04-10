/*
 * RegularExp.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: echgchi
 */

#include "RegularExp.h"
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

RegularExp* RegularExp::_instance = NULL;

RegularExp* RegularExp::instance()
{
    if (_instance == NULL)
    {
        _instance = new RegularExp();
    }

    return _instance;
}

void RegularExp::destroy()
{
    if (_instance != NULL)
    {
        delete _instance;
        _instance = NULL;
    }
}

RegularExp::RegularExp()
{
    // TODO Auto-generated constructor stub

}

RegularExp::~RegularExp()
{
    // TODO Auto-generated destructor stub
}

bool RegularExp::initRegexCmp(const char * pattern)
{

    int ret;
    int i;
    //REG_EXTENDED 以功能更加强大的扩展正则表达式的方式进行匹配。
    //REG_ICASE 匹配字母时忽略大小写。
    //REG_NOSUB 不用存储匹配后的结果。
    //REG_NEWLINE 识别换行符，这样'$'就可以从行尾开始匹配，'^'就可以从行的开头开始匹配。

    //ret = regcomp(&_reg, pattern, REG_EXTENDED);
    ret = regcomp(&_reg, pattern, REG_EXTENDED | REG_NOSUB);
    if (0 != ret)
    {

        size_t length = regerror(ret, &_reg, NULL, 0);
        char *buffer = (char *) malloc(length);

        if (!buffer)
            return false;

        (void) regerror(ret, &_reg, buffer, length);

        if (buffer)
        {
            printf("generate regcomp failed, err code= %d , err message= %s", ret, buffer);
            free(buffer);
        }

        return false;
    }

    return true;
}

void RegularExp::destroyRegex()
{
    regfree(&_reg);
}

bool RegularExp::isMatch(const char* str)
{
    int ret;

    regmatch_t *subexprs = (regmatch_t *) malloc((_reg.re_nsub + 1) * sizeof(regmatch_t));

    //REG_NOERROR REG_NOERROR = 0
    //	if (REG_NOERROR != (ret = regexec(&_reg, str, _reg.re_nsub + 1, subexprs, 0))) {
    if (REG_NOERROR != (ret = regexec(&_reg, str, _reg.re_nsub + 1, NULL, 0)))
    {
        size_t length = regerror(ret, &_reg, NULL, 0);
        char *buffer = (char *) malloc(length);

        if (!buffer)
        {
            free(subexprs);
            return false;
        }

        (void) regerror(ret, &_reg, buffer, length);

        if (buffer)
        {
            printf("try to match regexp failed, err code= %d , err message= %s\n", ret, buffer);
            free(buffer);
        }

        return false;
    }

    printf("is matched\n");
    return true;

    bool result = false;

    for (unsigned int i = 0; i < _reg.re_nsub; i++)
    {
        if (subexprs[i].rm_so == subexprs[i].rm_eo)
        {
            printf("EMPTY SUBEXPR on %d item.\n", i);

        }
        else if (subexprs[i].rm_so == -1 || subexprs[i].rm_eo == -1)
        {
            printf("NO SUBEXPR on %d item.\n", i);
        }
        else
        {
            result = true;

            unsigned int subExprLength = subexprs[i].rm_eo - subexprs[i].rm_so;
            char *subExpr = new char[subExprLength + 1];
            strncpy(subExpr, str + subexprs[i].rm_so, subExprLength);
            subExpr[subExprLength] = '\0';

            printf("FIND SUBEXPR on %d item, String is %s\n", i, subExpr);

            delete[] subExpr;

        }
    }

    return result;
}
