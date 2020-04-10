
#include "AUSFConfig.h"

AUSFConfig* AUSFConfig::_pInstance = NULL;

AUSFConfig::AUSFConfig()
{

}

AUSFConfig::~AUSFConfig()
{

}

AUSFConfig* AUSFConfig::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new AUSFConfig();
    }

    return _pInstance;
}

void AUSFConfig::destroy()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

bool AUSFConfig::loadConfig()
{

    return loadConfigFile();
}


#define CONF_KEY_BEINSTANCE_NUM "Backend.Wlan.NumOfBEInstance"
#define DEFAULT_BEINSTANCE_NUM  1


bool AUSFConfig::loadConfigFile()
{
    char confFileName[] = "ausf.conf";

    Config configuration;
    // load the config file
    if(configuration.load_ini_file(confFileName) == false)
    {
        return false;
    }

    int threadnum = configuration.get(CONF_KEY_BEINSTANCE_NUM, DEFAULT_BEINSTANCE_NUM);

    return true;
}


