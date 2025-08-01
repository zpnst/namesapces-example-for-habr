#include "proc.hpp"
#include "utils.hpp"

int main(void) {
    /** Создание init_proc, процесса с Process ID(PID) = 1 */
    process *init_proc = CreateInitProcess("init_proc");
    
    /** Создание дочерних для init_proc процессов */
    process *floppa_cat_proc = init_proc->forkProcess("floppa_cat_proc");
    process *ploob_cat_proc = init_proc->forkProcess("ploob_cat_proc");

    /** Создание дочерних для floppa_cat_proc процессов */
    process *komaru_cat_proc = floppa_cat_proc->forkProcess("komaru_cat_proc");
    process *zigmund_cat_proc = floppa_cat_proc->forkProcess("zigmund_cat_proc");

    /** Создание дочерних для zigmund_cat_proc процессов */
    process *barsik_cat_proc = zigmund_cat_proc->forkProcess("barsik_cat_proc");
    process *murzik_cat_proc = zigmund_cat_proc->forkProcess("murzik_cat_proc");

    /** Отображаем дерево процессов */
    DrawProcessesTree(init_proc);

    cout << colorfyString("INFO", "32") << " :: Processes resources before all manipulations\n" << endl;

    /** Смотрим на ресурсы процесса init_proc, komaru_cat_proc и murzik_cat_proc */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(komaru_cat_proc);
    DumpProccessInfo(murzik_cat_proc);

    /** Устанавлиаем через процесс 7 новую строчку*/
    murzik_cat_proc->setNewString("Hello, New string in init string Namespace!");

    cout << colorfyString("ACTION", "33") << " :: murzik_cat_proc changes a string" << endl;
    cout << colorfyString("INFO", "32") << " :: Processes resources after changing a string by murzik_cat_proc in init string Namespace\n" << endl;

    /** Смотрим на ресурсы процесса init_proc, komaru_cat_proc и murzik_cat_proc */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(komaru_cat_proc);
    DumpProccessInfo(murzik_cat_proc);

    komaru_cat_proc->unshare(NAMESPACES::STRING_NS);
    cout << colorfyString("ACTION", "33") << " :: komaru_cat_proc was unshared, new string Namesapce ";
    
    komaru_cat_proc->setNewString("I am from a new Namesapce, unshared by komaru_cat_proc");
    cout << colorfyString("ACTION", "33") << " :: komaru_cat_proc changes a string in a new string Namespace";
    komaru_cat_proc->setNewArray({123, 345, 789, 101112, 131415});
    cout << colorfyString("ACTION", "33") << " :: komaru_cat_proc changes an array in init array Namespace" << endl;

    cout << colorfyString("INFO", "32") << " :: Processes resources after changing a string by komaru_cat_proc in new string Namesapce\n" << endl;

    /** Смотрим на ресурсы процесса init_proc, komaru_cat_proc и murzik_cat_proc */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(komaru_cat_proc);
    DumpProccessInfo(murzik_cat_proc);

    murzik_cat_proc->unshare(NAMESPACES::STRING_NS);
    cout << colorfyString("ACTION", "33") << " :: murzik_cat_proc was unshared, new string Namesapce ";
    murzik_cat_proc->setNewString("I am from a new Namesapce, unshared by murzik_cat_proc");
    cout << colorfyString("ACTION", "33") << " :: murzik_cat_proc changes a string" << endl;

    murzik_cat_proc->unshare(NAMESPACES::ARRAY_NS);
    cout << colorfyString("ACTION", "33") << " :: murzik_cat_proc was unshared, new array Namesapce ";
    murzik_cat_proc->setNewArray({42, 137, 314, 271, 161});
    cout << colorfyString("ACTION", "33") << " :: murzik_cat_proc changes an array" << endl;

    cout << colorfyString("INFO", "32") << " :: Processes resources after changing string and array by murzik_cat_proc in new string Namesapce and Array Namespaces\n" << endl;

    /** Смотрим на ресурсы процесса init, 4 и 7 */
    DumpProccessInfo(init_proc);
    DumpProccessInfo(komaru_cat_proc);
    DumpProccessInfo(murzik_cat_proc);

    return 0;
} 
