#ifndef BE_CONFIG_H
#define BE_CONFIG_H


#include "Config.h"


using ipworks::Config;

class AUSFConfig
{
public:
    static AUSFConfig* getInstance();
    static void destroy();

    bool loadConfig();


private:
    AUSFConfig();
    virtual ~AUSFConfig();

    bool loadConfigFile();

    static AUSFConfig* _pInstance;
};

#endif

