#ifndef PersonDatabase_4a309fbd1acf40f2ade6687b50fb707c
#define PersonDatabase_4a309fbd1acf40f2ade6687b50fb707c

#include "Person.hpp"

#include <unordered_map>
#include <memory>
#include <iostream>

/**
 * @brief Represnts container for Person objects
 * 
 */
class PersonDatabase
{
    private:
        std::unordered_map<std::string, std::shared_ptr<Person>> users;
    public:
        PersonDatabase() = default;

        /**
         * @brief Adds new Person object to PersonDatabase
         * 
         * @param name unique identificator for Peron object
         * @return true if Person was added
         * @return false if Person object has already existed in the PersonDatabase,
         *  thus could not be added
         */
        bool AddNewPerson(const std::string & name);
        /**
         * @brief Gets smart pointer to an object specified by 
         * 
         * @param name Identifier by which Person can be found
         * @return std::shared_ptr<Person> 
         * @throws out_of_range if Person object with given name does not exist
         */
        std::shared_ptr<Person> GetPerson(const std::string & name) const;

        /**
         * @brief Gets all user in a unordered map
         * 
         * @return const std::unordered_map<std::string, std::shared_ptr<Person>>& 
         */
        const std::unordered_map<std::string, std::shared_ptr<Person>> & GetUsers() const;
};

#endif //PersonDatabase_4a309fbd1acf40f2ade6687b50fb707c