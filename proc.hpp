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
    int         arr_len; /* Длина массива */
    vector<int> array;   /* Указатель на массив */

    /* Конструктор по умолчанию */
    array_ns();
};

/**
 * Структура, представляющая пространсто строк
 */
struct string_ns {
    int    str_len; /* Длина строки */
    string str;     /* Обычная строчка */

    /* Конструктор по умолчанию */
    string_ns();
};

/**
 * Структура для описания пространста имён процесса, имеет два 
 * пространства имён: пространство массивов и пространство строк
 */
struct process_namespaces {
    array_ns  *ans; /* Пространство массивов */
    string_ns *sns; /* Пространство строк */
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
    int    process_id;   /* Идентификатор процесса */
    string process_name; /* Имя процесса */
    
    child_proc         *children;   /* Список дочерних процессов(детей) */
    process_namespaces *namespaces; /* Пространства имён процесса */

    void unshare(NAMESPACES ns);
    void setNewString(string str);
    void setNewArray(vector<int> arr);

    process *forkProcess(string new_process_name);
};

/**
 * Функция для создания init процесса
 */
process *CreateInitProcess(string new_process_name);

#endif /** PROCS_HPP */