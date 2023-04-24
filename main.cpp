#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
#include <exception>
#include <iostream>
using namespace std;
using namespace boost::property_tree;

class IniFile{
    public:
    template <typename T>
    static T GetPrivateProfile(const string &lpAppName,const  string &lpKeyName,const T tDefault,const string &lpFileName )
    {
        ptree root;
        T retValue = tDefault;
        read_ini(lpFileName, root);
        try
        {
            ptree appNameTree = root.get_child(lpAppName);
            retValue = appNameTree.get<T>(lpKeyName);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return retValue;

    }
    template <typename T>
    static void WritePrivateProfile(const string &lpAppName,const string &lpKeyName, T tData,const string &lpFileName )
    {
        ptree root;
        ptree newNode;
        newNode.put(lpKeyName, tData);
        try
        {
            read_ini(lpFileName, root);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        try
        {
            root.put_child(lpAppName, newNode);
            write_ini(lpFileName, root);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
int main()
{
    string Default = "Test";
    IniFile::WritePrivateProfile<string>("Param2", "Name1", "Duynt2", "Test.ini");
    // cout << IniFile::GetPrivateProfile<string>("Param", "Name1", Default, "Test.ini");
    
    return 0;
}
