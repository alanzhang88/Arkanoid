#ifndef FUNCTIONTIMER
#define FUNCTIONTIMER

#include <QTimer>

enum Drop_Func{RESET,ADDLIFE,STRETCH,SHRINK,REVERSE};

/** @class FunctionTimer
 * @brief this class is the timers for the drops
*/

class FunctionTimer:public QTimer{
public:
    FunctionTimer(Drop_Func drop_function,QObject* parent=0);
    Drop_Func get_function_type()const;
    void set_function_type(Drop_Func drop_function);

private:
    Drop_Func function;
};



#endif // FUNCTIONTIMER

