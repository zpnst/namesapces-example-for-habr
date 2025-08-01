#include "utils.hpp"

void DrawProcessesTreeHelper(process* proc, string prefix = "") {
    if (!proc) return;

    cout << prefix << "├── " << proc->process_name << " (PID: " << proc->process_id << ")" << endl;

    child_proc* curr_child = proc->children;
    while (curr_child) {
        string new_prefix = prefix;
        new_prefix += "    ";
        DrawProcessesTreeHelper(curr_child->proc, new_prefix);
        curr_child = curr_child->next;
    }
}

void DrawProcessesTree(process* proc) {
    if (!proc) return;
   
    cout <<  colorfyString("[Processes Tree]", "35") + " :: ------------------------------------------" << endl;
    cout << "." << endl;
    DrawProcessesTreeHelper(proc);
}

void DumpProccessInfo(process *proc) {
    cout << colorfyString("[" + proc->process_name + "]", "35") + " :: ------------------------------------------" << endl;
    cout << "PID: " << proc->process_id << endl;

    cout << "Namespaces: " << endl;
    cout << "Array NS: " << endl;
    cout << "\tArray Len: " << proc->namespaces->ans->arr_len << endl;
    cout << "\tArray: " << getStringArray(proc->namespaces->ans->array) << endl;

    cout << "String NS: " << endl;
    cout << "\tString Len: " << proc->namespaces->sns->str_len << endl;
    cout << "\tString: " << proc->namespaces->sns->str  << endl;
}


string getStringArray(vector<int> arr) {
    string stringArr = "[";
    for (int elem : arr) {
        stringArr += to_string(elem) + " ";
    }
    stringArr += "]";
    return stringArr;
}

string colorfyString(string str, string code) {
    return "\033[1;" + code + "m\n" + str  +"\033[0m";
}