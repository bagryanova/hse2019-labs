#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "str.h"

char s1[100] = "";
char s2[100] = "abacaba";
char s3[100] = "sjfndjvasdjkcasdafka";
char s4[100] = "";
char s5[100] = "abacaba";

int sign(int a) {
    if (a > 0) {
        return 1;
    }
    if (a < 0) {
        return -1;
    }
    return 0;
}


void test_strcpy() {
	char ans1[100] = "";
	char ans2[100] = "";
	int a = strcmp(strcpy(ans1, s1), my_strcpy(ans2, s1));
    assert(a == 0);

    a = strcmp(strcpy(ans1, s2), my_strcpy(ans2, s2));
    assert(a == 0);

    a = strcmp(strcpy(ans1, s3), my_strcpy(ans2, s3));
    assert(a == 0);
}


void test_strcmp() {
	int a = strcmp(s1, s1), b = my_strcmp(s1, s1);
    assert(sign(a) == sign(b));

    a = strcmp(s1, s4);
    b = my_strcmp(s1, s4);
    assert(sign(a) == sign(b));

    a = strcmp(s2, s5);
    b = my_strcmp(s2, s5);
    assert(sign(a) == sign(b));

    a = strcmp(s2, s3);
    b = my_strcmp(s2, s3);
    assert(sign(a) == sign(b));

    a = strcmp(s3, s2);
    b = my_strcmp(s3, s2);
    assert(sign(a) == sign(b));
}

void test_strlen() {
	size_t a = strlen(s1);
    size_t b = my_strlen(s1);
    assert(a == b);

    a = strlen(s2);
    b = my_strlen(s2);
    assert(a == b);

    a = strlen(s3);
    b = my_strlen(s3);
    assert(a == b);
}

void test_strcat() {
    char curs1[100] = "", curs2[100] = "", curs3[100] = "", curs4[100] = "";
    char* i1 = strcpy(curs1, s1);
    char* i2 = strcpy(curs2, s2);
    char* i3 = strcpy(curs3, s1);
    char* i4 = strcpy(curs4, s2);
    int a = strcmp(strcat(i1, i2), my_strcat(i3, i4));
    assert(a == 0);

    i1 = strcpy(curs1, s2);
    i2 = strcpy(curs2, s4);
    i3 = strcpy(curs3, s2);
    i4 = strcpy(curs4, s4);
    a = strcmp(strcat(i1, i2), my_strcat(i3, i4));
    assert(a == 0);

    i1 = strcpy(curs1, s2);
    i2 = strcpy(curs2, s3);
    i3 = strcpy(curs3, s2);
    i4 = strcpy(curs4, s3);
    a = strcmp(strcat(i1, i2), my_strcat(i3, i4));
    assert(a == 0);

    i1 = strcpy(curs1, s3);
    i2 = strcpy(curs2, s2);
    i3 = strcpy(curs3, s3);
    i4 = strcpy(curs4, s2);
    a = strcmp(strcat(i1, i2), my_strcat(i3, i4));
    assert(a == 0);

    i1 = strcpy(curs1, s1);
    i2 = strcpy(curs2, s4);
    i3 = strcpy(curs3, s1);
    i4 = strcpy(curs4, s4);
    a = strcmp(strcat(i1, i2), my_strcat(i3, i4));
    assert(a == 0);
}



