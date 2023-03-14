#include "test.h"
#include <string.h>
#include <stdio.h>

int test_mot_normaliser() {
    char* t1 = "HelLo WORLd";
    char* t2 = "LicEnCE 1";
    
    MOT_normaliser(t1);
    MOT_normaliser(t2);

    if(strcmp(t1, "hello world") != 0 || strcmp(t2, "LicEnCE 1") != 0)
        return 0;
    return 1;
}        
