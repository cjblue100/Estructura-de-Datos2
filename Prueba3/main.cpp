#include <iostream>
#include <fstream>
#include <vector>
#include "Jzon.h"
#include "Yaml.hpp"

namespace Json = Jzon;


Yaml::Node J_To_Y(Json::Node& jsan,Yaml::Node& niu)
{
    

    if (jsan.isObject())
    {
        Yaml::Node lol;
        
        for ( auto n : jsan)
        {
            
            niu[n.first]=J_To_Y(n.second,lol);
            
            lol.Clear();
                
        }
        
        return niu;
        
    }
    else if (jsan.isArray())
    {
        Yaml::Node lol;
        for ( auto n : jsan)
        {
            
            
            
            
            niu.PushBack()=J_To_Y(n.second,lol);
            
            lol.Clear();
            
            
            
        }
        return niu;
        
    }else
    {
        return jsan.toString();
    }
    
    
    return niu;

}


int main(int argc, char *argv[])
{
    

    //Jason Begin


  
    
	Json::Parser parser;
	
	Json::Node root2 = parser.parseFile(argv[1]);
    
	if (!root2.isValid())
	{
		std::cerr << parser.getError() << '\n';
		return 1;
	}
    
    //Json Finish

    Yaml::Node niu;
    Yaml::Node pop;
    J_To_Y(root2,niu);
    

    Json::Node jsan;
   
    Yaml::Serialize(niu,argv[2],Yaml::SerializeConfig(2,64,true,false));

	return 0;
}
