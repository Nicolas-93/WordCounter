#include "test.h"
#include <string.h>
#include <stdio.h>

int test() {
    test_mot_normaliser();
    return 1;
}

int test_mot_normaliser() {
    char t1[] = "HelLo WORLd";
    char t2[] = "LicEnCE 1";
    char t3[] = "ù$*ùù Corr$^*ùm*pu";
    
    MOT_normaliser(t1);
    MOT_normaliser(t2);
    MOT_normaliser(t3);

    test_assert(STR_EQUALS(t1, "hello world"));
    test_assert(STR_EQUALS(t2, "licence 1"));
    test_assert(STR_EQUALS(t3, "ù$*ùù corr$^*ùm*pu"));

    return 1;
}        
