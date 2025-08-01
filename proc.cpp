#include "proc.hpp"

/* Счётчик процессов */
unsigned int process_count = 1; 

/**
 * Релизация контсруткора по умолчанию для array_ns
 */
array_ns::array_ns() {
    this->array = {1, 2, 3, 4, 5};
    this->arr_len = 5;
}

/**
 * Релизация контсруткора по умолчанию для string_ns
 */
string_ns::string_ns() {
    this->str = "Hello, Habr!";
    this->str_len = 12;
}

/**
 * Релизация функции forkProcess для process
 */
process *process::forkProcess(string new_process_name) {
        
    /* Выделение памяти под новый процесс */
    process *new_proc = new process;

    new_proc->process_id = process_count;
    new_proc->process_name = new_process_name;

    /* Установка родительских пространств имён */
    new_proc->namespaces = this->namespaces;

    process_count += 1;

    /* Новый процесс становится ребёнком того процесса,
       через который был вызван метод forkProcess */

    child_proc* new_child = new child_proc;
    new_child->proc = new_proc;
    new_child->next = nullptr;

    /* Если детей нет, то просто добавляем первого */
    if (this->children == nullptr) {
        this->children = new_child;
    /* Иначе идём по указателям next до последнего
       ребёнка и добавляем в конец списка */
    } else {
        child_proc* curr_child = this->children;
        while (curr_child->next) {
            curr_child = curr_child->next;
        }
        curr_child->next = new_child;
    }

    new_proc->children = nullptr;

    return new_proc;
}

/**
 * Релизация функции unshare для process
 */
void process::unshare(NAMESPACES ns) {
    process_namespaces *new_namespace = new process_namespaces;
    switch (ns) {
    /* Хотим получить новое протснвсто мвссивов  */
    case NAMESPACES::ARRAY_NS: {
        /* Cоздаём новое протснвсто мвссивов  */
        array_ns* new_ans = new array_ns;
        new_namespace->ans = new_ans;
        new_namespace->sns = this->namespaces->sns;

        this->namespaces = new_namespace;
        break;
    }
    /* Хотим получить новое протснвсто строк  */
    case NAMESPACES::STRING_NS: {
        /* Cоздаём новое протснвсто строк  */
        string_ns* new_sns = new string_ns;
        new_namespace->sns = new_sns;
        new_namespace->ans = this->namespaces->ans;

        this->namespaces = new_namespace;
        break;
    }
    }
}

/**
 * Релизация функции setNewString для process
 */
void process::setNewString(string str) {
    this->namespaces->sns->str = str;
    this->namespaces->sns->str_len = str.size();
}

/**
 * Релизация функции setNewArray для process
 */
void process::setNewArray(vector<int> arr) {
    this->namespaces->ans->array = arr;
    this->namespaces->ans->arr_len = arr.size();
}

/**
 * Релизация функции для создания init процесса
 */
process *CreateInitProcess(string init_process_name) {

    /* Выделение памяти под init процесс */
    process *init_proc = new process;

    init_proc->process_id = process_count;
    init_proc->process_name = init_process_name;

    /* Выделение памяти под пространства имён init процесса */
    process_namespaces *init_ns = new process_namespaces;

    /* Выделение памяти под базовые пространста имён */
    array_ns* init_ans = new array_ns;
    string_ns* init_sns = new string_ns;

    init_ns->ans = init_ans;
    init_ns->sns = init_sns;

    /* Инициализация пространства имён init процесса */
    init_proc->namespaces = init_ns;

    process_count += 1;
    init_proc->children = nullptr;

    return init_proc;
}