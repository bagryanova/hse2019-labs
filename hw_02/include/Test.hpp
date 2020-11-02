#pragma once

#define DO_CHECK(EXPR) Test::check(EXPR, __func__, __FILE__, __LINE__);

#include <cstring>

class Test {
protected:
    static int failedNum;
    static int totalNum;
                                                                
    static void check(bool expr, const char *func, const char *filename, size_t lineNum); 

public:
    static bool show_final_result();
    
    virtual void run_all_tests() = 0;
};