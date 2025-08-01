#include "proc.hpp"
#include "utils.hpp"

int main(void) {
    /** Создание init процесса с Process ID(PID) = 1 */
    process *init_proc = CreateInitProcess("init");
    
    process *proc_2 = init_proc->forkProcess("floppa_cat_proc");
    process *proc_3 = init_proc->forkProcess("ploob_cat_proc");

    process *proc_4 = proc_2->forkProcess("komaru_cat_proc");
    process *proc_5 = proc_2->forkProcess("zigmund_cat_proc");

    process *proc_6 = proc_5->forkProcess("barsik_cat_proc");
    process *proc_7 = proc_5->forkProcess("murzik_cat_proc");

    /** Отображаем дерево процессов */
    DrawProcessesTree(init_proc);

    cout << colorfyString("INFO", "32") << " :: Processes resources before all manipulations\n" << endl;

    /** Смотрим на ресурсы процесса init, 4 и 7 */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(proc_4);
    DumpProccessInfo(proc_7);

    /** Устанавлиаем через процесс 7 новую строчку*/
    proc_7->setNewString("Hello, New string in init string Namespace!");

    cout << colorfyString("ACTION", "33") << " :: proc_7 changes a string" << endl;
    cout << colorfyString("INFO", "32") << " :: Processes resources after changing a string by proc_7 in init string Namespace\n" << endl;

    /** Смотрим на ресурсы процесса init, 4 и 7 */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(proc_4);
    DumpProccessInfo(proc_7);

    proc_4->unshare(NAMESPACES::STRING_NS);
    cout << colorfyString("ACTION", "33") << " :: proc_4 was unshared, new string Namesapce ";
    
    proc_4->setNewString("I am from a new Namesapce, unshared by proc_4");
    cout << colorfyString("ACTION", "33") << " :: proc_4 changes a string" << endl;
    cout << colorfyString("INFO", "32") << " :: Processes resources after changing a string by proc_4 in new string Namesapce\n" << endl;

    /** Смотрим на ресурсы процесса init, 4 и 7 */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(proc_4);
    DumpProccessInfo(proc_7);

    proc_7->unshare(NAMESPACES::STRING_NS);
    cout << colorfyString("ACTION", "33") << " :: proc_7 was unshared, new string Namesapce ";
    proc_7->setNewString("I am from a new Namesapce, unshared by proc_7");
    cout << colorfyString("ACTION", "33") << " :: proc_7 changes a string" << endl;

    proc_7->unshare(NAMESPACES::ARRAY_NS);
    cout << colorfyString("ACTION", "33") << " :: proc_7 was unshared, new array Namesapce ";
    proc_7->setNewArray({42, 137, 314, 271, 161});
    cout << colorfyString("ACTION", "33") << " :: proc_7 changes an array" << endl;

    cout << colorfyString("INFO", "32") << " :: Processes resources after changing string and array by proc_7 in new string Namesapce and Array Namespaces\n" << endl;

    /** Смотрим на ресурсы процесса init, 4 и 7 */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(proc_4);
    DumpProccessInfo(proc_7);

    return 0;
} 
