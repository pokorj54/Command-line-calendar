#include "PersonDatabase.hpp"

using namespace std;

bool PersonDatabase::AddNewPerson(const string & name)
{
    if(users.count(name) == 0)
    {
        shared_ptr<Person> tmp(new Person(name));
        users.insert(make_pair(name, tmp));
        return true;
    }
    return false;
}
std::shared_ptr<Person> PersonDatabase::GetPerson(const string & name) const
{
    return users.at(name);
}

const std::unordered_map<std::string, std::shared_ptr<Person>> & PersonDatabase::GetUsers() const
{
    return users;
}
