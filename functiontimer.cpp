#include "functiontimer.h"

/** This is the constructor of FucntionTimer
 * @param drop_function is the function that the drop performs
 * @param parent is the parent pointer of timer
*/
FunctionTimer::FunctionTimer(Drop_Func drop_function, QObject *parent):function(drop_function),QTimer(parent)
{

}
/** This function access the function of the drop taken care by the timer
 * @returns the function in the timer
*/
Drop_Func FunctionTimer::get_function_type() const
{
    return function;
}

/** This function set the drop function type of the timer
 * @param drop_function is the drop_functino taken care by the timer
*/
void FunctionTimer::set_function_type(Drop_Func drop_function)
{
    function=drop_function;
}
