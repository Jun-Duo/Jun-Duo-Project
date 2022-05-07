#ifndef __field_H__
#define __field_H__

#define NUM_FIELDS 2
#define MAX_LEN_FIELD_NAME 30

// enum of field
enum Field {
    PyeongBong_Field,
    Hiddink_Futsal_Field
};

// Array of field name strings
const char fieldName[NUM_FIELDS][MAX_LEN_FIELD_NAME] = {
    "평봉필드",
    "히딩크풋살장"};

#endif