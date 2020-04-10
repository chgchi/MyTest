// File: Config.cpp
//
// Responsible Workarea: CBC - Shanghai
//
// This is an unpublished Document the copyright in which vests in
// Telefonaktiebolaget LM Ericsson. All rights reserved. (c) 2009
//
// The information contained herein is confidential and the property of
// Telefonaktiebolaget LM Ericsson and is supplied without liability for
// errors or omissions. No part may be reproduced, disclosed or used except
// as authorised by contract or other written permission. The copyright and
// the foregoing restriction on reproduction and use extend to all media in
// which the information may be embodied.

// A configuration object, to load and store user defined parameters.

#include "Config.h"
#include "CriticalSection.h"
#include <stdio.h>
#include <ctype.h>
#include <algorithm>

namespace ipworks 
{

Config::Config()
{
    pthread_mutex_init( & _mutex, 0);
}

Config::~Config()
{
    _settings.clear();
    _sections.clear();
    _orderedSettings.clear();

    pthread_mutex_destroy( & _mutex );
}

void Config::set(const char * key, const char *value)
{
    std::string upperkey = key;
    uppercase(upperkey);

    CriticalSection cs( & _mutex );
    _settings.insert( std::map< std::string, std::string >::value_type(upperkey, value ) );
}

void Config::replace(const char * key, const char *value)
{
    std::string upperkey = key;
    uppercase(upperkey);

    CriticalSection cs(&_mutex);
    _settings[upperkey] = value;
}


const char *Config::get(const char * key) const
{
    return get(key,(const char *)0);
}

const char *Config::get(const char * key, const char * default_value) const
{
    // Essentially this funciton is constant. i.e. no data is changed.
    // However it is required to lock the member mutex and perform search
    // operaitons on the string Map.  As such the constness has been cast away.

    std::string upperkey = key;

    uppercase(upperkey);

    CriticalSection cs( const_cast<pthread_mutex_t *>(& _mutex ) );

    std::map< std::string, std::string >::iterator it =
        const_cast<std::map< std::string, std::string >*>(&_settings)->find( upperkey );

    if (_settings.end() == it )
    {
        return default_value;
    }

    return it->second.c_str();
}

int Config::get(const char * key, int default_value) const
{
    const char *value = get(key,(const char *)0);

    if (!value) return default_value;

    return atoi(value);
}

bool Config::get(const char * key, bool default_value) const
{
    const char *value = get(key,(const char *)0);

    if (!value) return default_value;

    std::string v = value;

    uppercase(v);
    //uppercase is useless now, since the uppercase is used in many places, just add below line for the moment.
    std::transform( v.begin(), v.end(), v.begin(), ::toupper );

    if ( default_value )
    {
        if ( "F" == v || "FALSE" == v) return false;
    }
    else
    {
        if ( "T" == v || "TRUE" == v) return true;
    }

    return default_value;
}

const std::vector<std::string>& Config::get_sections() const
{
    CriticalSection cs( const_cast<pthread_mutex_t *> (&_mutex) );

    return _sections;
}

bool Config::get_suffix_keys(std::string prefix, std::vector<std::string>& suffix)
{
    uppercase(prefix);

    CriticalSection cs( const_cast<pthread_mutex_t *>(& _mutex ) );

    suffix.clear();

    std::map< std::string, std::string >::iterator it = _settings.begin();
    std::string key = "";
    size_t pos;
    size_t len;

    for(; it != _settings.end(); ++it)
    {
        key = (*it).first;
        len = prefix.size();

        pos = key.find(prefix);
        if(pos != std::string::npos)
        {
            std::string sname = key.substr(pos+len);

            if(sname.empty())
                continue;

            suffix.push_back(sname);
        }
    }

    if(suffix.empty())
        return false;

    return true;
}

bool Config::get_ordered_suffix_keys(std::string prefix, std::vector<std::string>& suffix)
{
    uppercase(prefix);

    CriticalSection cs( const_cast<pthread_mutex_t *>(& _mutex ) );

    suffix.clear();

    std::vector< SettingDef >::iterator it = _orderedSettings.begin();
    std::string key = "";
    size_t pos;
    size_t len;

    len = prefix.length();
    for(; it != _orderedSettings.end(); ++it)
    {
        key = (*it).key;

        pos = key.find(prefix);
        if(pos != std::string::npos)
        {
            std::string sname = key.substr(pos+len);

            if(sname.empty())
                continue;

            suffix.push_back(sname);
        }
    }

    if(suffix.empty())
        return false;

    return true;
}

bool Config::get_by_prefix(std::string prefix, std::vector<SettingDef>& outSettings)
{
    uppercase(prefix);

    CriticalSection cs( const_cast<pthread_mutex_t *>(& _mutex ) );

    outSettings.clear();

    std::vector< SettingDef >::iterator it = _orderedSettings.begin();
    std::string key = "";
    size_t pos;

    for(; it != _orderedSettings.end(); ++it)
    {
        key = (*it).key;

        pos = key.find(prefix);
        if(pos != std::string::npos)
        {
            outSettings.push_back(*it);
        }
    }

    if(outSettings.empty())
        return false;

    return true;
}


void Config::uppercase(std::string &s)
{
    //need to consider the upper/lower case
    //std::transform( s.begin(), s.end(), s.begin(), (int(*)(int)) toupper );
}

void Config::strip_quotes(std::string &s)
{
    std::string::size_type l = s.length();
    if (std::string::npos == l) return;

    //are the quotes there?
    if (('"' == s.c_str()[0] || '\'' == s.c_str()[0]) &&
            ('"' == s.c_str()[l-1] || '\'' == s.c_str()[l-1]))
    {
        s=s.substr(1,l-2);
    }
}

std::string Config::get_next_token(
    const std::string &s,
    std::string::size_type &pos
)
{
    static const std::string white_space = " \t\r\n";
    static const std::string symbols = "#=;()[]<>";
    static const std::string quotes = "\"'";
    static const std::string alpha_numeric = "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890_./\\:,+-@~?|!$%"
            "^&*";

    std::string::size_type start;

    pos = start = s.find_first_not_of(white_space, pos);

    if (std::string::npos == pos) return "";

    //is this an alpha or symbol ?
    char c = s.c_str()[pos];

    if ( std::string::npos != symbols.find( c ) )
    {
        pos = s.find_first_not_of( symbols, start );
    }
    else if ( std::string::npos != quotes.find( c ) )
    {
        pos = s.find_first_of( quotes, start + 1 );
        if (std::string::npos != pos ) ++pos;
    }
    else
    {
        pos = s.find_first_not_of( alpha_numeric, start );
    }

    // if its at the end then return the whole string.
    if (std::string::npos == pos)
    {
        return s.substr(start, std::string::npos);
    }

    std::string::size_type length = pos - start;

    return s.substr(start,length);
}

bool Config::load_ini_file( const char *filename, const char *match)
{
    _settings.clear();
    _sections.clear();
    _orderedSettings.clear();

    std::string section = "";

    FILE *file = fopen(filename,"r");

    if (!file)
    {
        return false;
    }

    char buffer[1024];
    std::string line, token;

    int idx = 0;
    while (0 != fgets(buffer, 1024, file ) )
    {
        line = buffer;
        // work out row type
        std::string::size_type pos =0;
        token = get_next_token(line, pos);

        strip_quotes(token);

        // section in square brackets []
        if ('[' == token.c_str()[0])
        {
            section = get_next_token(line, pos);
            _sections.push_back(section);

            continue;
        }

        if ( isalnum(token.c_str()[0]) || '_' == token.c_str()[0] )
        {
            // key = [value] [;]
            // key
            std::string key = token;

            token = get_next_token(line, pos);

            if ( '=' == token.c_str()[0]) token = get_next_token(line, pos);

            if ( ';' == token.c_str()[0] ) token = "";

            strip_quotes(token);

            if(section.empty())
            {
                if (    ( ! match )  ||
                        ( 0 == strncasecmp(match,key.c_str(),strlen(match)))
                   )
                {
                    set(key.c_str(),token.c_str());

                    SettingDef setting;
                    setting.id = idx ++;
                    setting.key = key;
                    setting.value = token;
                    _orderedSettings.push_back(setting);
                }
            }
            else// (!section.empty())
            {
                std::string sectionkey = section;
                sectionkey += ".";
                sectionkey += key;

                if (    ( ! match ) ||
                        ( 0 == strncasecmp(match,sectionkey.c_str(),strlen(match)))
                   )
                {
                    set(sectionkey.c_str(),token.c_str());

                    SettingDef setting;
                    setting.id = idx ++;
                    setting.key = section + "." + key;
                    setting.value = token;
                    _orderedSettings.push_back(setting);

                }
            }

            continue;
        }
    }

    fclose(file);

    return true;
}

}
