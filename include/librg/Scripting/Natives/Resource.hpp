#ifndef __scripting_resource
#define __scripting_resource

#include <librg/Resource/Manager.h>

namespace Server    {
namespace Scripting {


namespace Resource
{
    /**
     * Public api
     * check wether or not particular resource has been loaded
     * @param  resourceName
     * @return
     */
    inline static bool resourceLoaded(const char* resourceName)
    {
        return Server::Resource::Manager::Instance()->Exist(resourceName);
    }

    /**
     * Registry method
     * @param native
     */
    inline static void Install(Sqrat::Table& native)
    {
        native.Func("resourceLoaded", &resourceLoaded);
    }
}



} // Scripting
} // Server

#endif // __scripting_resource
