#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

class Config {

    public:
        std::vector<std::pair<std::string, std::string>> variables;

        Config(void){}
        //
        // Config(const std::string path)
        // {
        //     this->Parse(path);
        // }

        void LoadConfig(const std::string path)
        {
            this->Parse(path);
        }

        std::string GetValue(const std::string& name)
        {
            for(auto& pair: variables)
            {
                if(std::get<0>(pair) == name)
                {
                    return std::get<1>(pair);
                }
            }
            return "";
        }

    private:

        void Parse(const std::string& path)
        {
            std::fstream dfile(path);
            if(dfile)
            {
                std::string line;
                while(getline(dfile,line))
                {
                    line.erase( std::remove_if(line.begin(),line.end(), isspace),line.end());
                    auto splitPos = line.find("=");
                    if(line.empty())
                    {
                        continue;
                    }
                    auto name = line.substr(0,splitPos);
                    auto value = line.substr(splitPos + 1);
                    variables.push_back(std::make_pair(name,value));
                }
                printf("INFO: Read Config File [%s]!\n", path.c_str());
            }
            else if(!dfile) {
                printf("ERROR: Couldn't Open Config File [%s]!\n", path.c_str());
            }
            dfile.close();
        }
};
