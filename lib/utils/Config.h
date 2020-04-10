// File: Config.h
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

#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <stdint.h>

typedef struct _SettingDef
{
    int id;
    std::string key;
    std::string value;
} SettingDef;

namespace ipworks
{

    class Config
    {
    public:
        Config();
        virtual ~Config();

        /**
         * Loads in an ini-style formatted file.
         * Syntax is as follows:
         *   # comment
         *   key
         *   key = value
         *   [Section]
         * Section names are prefixed to the key prior to storing. i.e. key "One"
         * in section "[Number]" becomes the key "Number.One"
         * Keys and values must be a string of alpha-numeric or valid symbols, alternatively
         * they can be a quoted string of any types of characters.
         * Valid symbols are _./\\:,+-@~?|!$%^&*
         *
         * \param filename  The full or releative path name to the inifile.
         * \param match     Prefix string used to match for key matching,
         *                  section names are prefixed to the key prior to checking
         *                  for a match.  If unset then all arguments are matching.
         * \return false if the file could not be read.
         */
        bool load_ini_file(const char* filename, const char* match = 0);

        /**
         * Obtain a string based value based on the supplied key. All searches are case-sensitive.
         * \param key The key for the search.
         * \return the stored value or a null pointer if not found.
         */
        const char* get(const char* key) const;

        /**
         * Obtain a string based value based on the supplied key. All searches are case-sensitive.
         * \param key The key for the search.
         * \param default_value the value that should be returned if not found
         * \return the stored value or the default value if not found.
         */
        const char* get(const char* key, const char* default_value) const;

        /**
         * Obtain an integer based value based on the supplied key. All searches are case-sensitive.
         * \param key The key for the search.
         * \param default_value the value that should be returned if not found
         * \return the stored value or the default value if not found.
         */
        int get(const char* key, int default_value) const;

        /**
         * Obtain an boolean based value based on the supplied key. All searches are case-sensitive.
         * Valid values are as true and false, invalid values will result in the default being returned.
         * \param key The key for the search.
         * \param default_value the value that should be returned if not found
         * \return the stored value if appropriate or the default value.
         */
        bool get(const char* key, bool default_value) const;

        /**
         * Obtain the section names in this file. All searches are case-sensitive.
         * \return the stored section vector
         */
        const std::vector<std::string>& get_sections() const;

        /**
         * Obtain the key suffix names with the specific prefix in this file. All searches are case-sensitive.
         * \param prefix the matching prefix to be searched for keys
         * \param suffix the matched keys' suffix names vector
         * \return true if any, otherwise false
         */
        bool get_suffix_keys(std::string prefix, std::vector<std::string>& suffix);

        /**
         * Obtain the key suffix names with the specific prefix in this file. All searches are case-sensitive.
         * \param prefix the matching prefix to be searched for keys
         * \param suffix the matched keys' suffix names vector
         * \return true if any, otherwise false
         */
        bool get_ordered_suffix_keys(std::string prefix, std::vector<std::string>& suffix);
        bool get_by_prefix(std::string prefix, std::vector<SettingDef>& outSettings);

        /**
         * Set method to change or insert a new key-value pair.
         * \param key The key to be added or changed.
         * \param value The value in string form.
         */
        void set(const char* key, const char* value);

        void replace(const char* key, const char* value);

    protected:
        static void uppercase(std::string& s);
        static void strip_quotes(std::string& s);
        static std::string get_next_token(
            const std::string& s,
            std::string::size_type& pos);

        pthread_mutex_t _mutex;
        std::map< std::string, std::string > _settings;
        std::vector< std::string > _sections;
        std::vector<SettingDef> _orderedSettings;
    };

}

#endif

