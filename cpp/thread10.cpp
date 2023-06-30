#include "..\header\thread10.h"

thread10::thread10()
{

}
void thread10::run()
{
    int i=0;
    while(true)
    {
        i++;
        if(i==1000)
            i=0;
    }
}
