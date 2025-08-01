#ifndef PROCS_HPP
#define PROCS_HPP

#include <vector>
#include <iostream>

using namespace std;

enum NAMESPACES {
    ARRAY_NS,
    STRING_NS
};

/**
 * Структура, представляющая пространсто массивов
 */
struct array_ns {
    int         arr_len; /* длина массива */
    vector<int> array;   /* указатель на массив */

    /* конструктор по умолчанию */
    array_ns();
};

/**
 * Структура, представляющая пространсто строк
 */
struct string_ns {
    int    str_len; /* длина строки */
    string str;     /* обычная строчка */

    /* конструктор по умолчанию */
    string_ns();
};

/**
 * Структура для описания пространста имён процесса, имеет два 
 * пространства имён: пространсто массивов и пространсто строк
 */
struct process_namespaces {
    array_ns  *ans; /* пространсто массивов  */
    string_ns *sns; /* пространсто строк */
};

struct process;

struct child_proc {
    process* proc;
    child_proc* next;
};

/**
 * Структура, представляющая процесс
 */
struct process {
    int    process_id;
    string process_name;
    
    child_proc         *children;
    process_namespaces *namespaces;

    void unshare(NAMESPACES ns);
    process *forkProcess(string new_process_name);
    
    void setNewString(string str);
    void setNewArray(vector<int> arr);
};

/**
 * Функция для создания init процесса
 */
process *CreateInitProcess(string new_process_name);

#endif /** PROCS_HPP */