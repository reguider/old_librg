#include <Core.h>
#include "Manager.h"

#include <Utils/Filesystem.h>
#include <tinyxml2.h>
#include <vector>

using namespace tinyxml2;
using namespace Server::Resource;

// TODO(inlife): move to config.xml!
std::vector<std::string> resources = {
    "default2",
    // "default",
};

Manager::Manager()
{
    // try to create resources folder
    int result = fs::mkdir("resources");

    if (result != 0 && result != UV_EEXIST) {
        Core::Error(uv_strerror((int)result));
        return;
    }

    // iterate and try to load all provided resources
    for (auto resource : resources) {
        fs::read(fs::path("resources", resource, "meta.xml"), [resource] (fs::result_t* result) -> void {
			tinyxml2::XMLDocument doc;

            doc.Parse(result->content, result->length);
            XMLElement* meta = doc.FirstChildElement("meta");

            if (!meta) {
                Core::Error("There is no <meta> tag inside your %.*s file.", result->fplength, result->filepath);
                return;
            }

            XMLElement * element = meta->FirstChildElement("script");
            std::vector<script_t*> scripts;

            // iterate over each script and add to the array
            while (element != nullptr)
            {
                // read up script type, and skip if nothing is loaded
                const char * szScriptType = nullptr;
                szScriptType = element->Attribute("type");
                if (szScriptType == nullptr) continue;

                script_t* script = new script_t;

                // fill up data
                script->filename = new std::string(fs::path("resources", resource, std::string(element->GetText())));
                script->type = strncmp(szScriptType, "client", sizeof(char) * 6) ? tServer : tClient;

                scripts.push_back(script);

                // goto next item in list
                element = element->NextSiblingElement("script");
            }

            Manager::Instance()->Add(resource, new Resource(resource, scripts));
        });
    }
}

Manager::~Manager()
{
    for (auto resource : mResources) {
        resource.second->Unload();
    }
}
