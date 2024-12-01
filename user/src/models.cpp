#include "../../core/includes/models.hpp"

class User : public Model{
public:
    User(){
        fields["name"] = CharField("VARCHAR", true, false, 50);
        fields["dob"] = IntegerField();
    }
};
REGISTER_MODEL(User);

class Account : public Model{
public:
    Account(){
        fields["balance"] = DecimalField("DECIMAL", 8, 2);
        fields["acc_no"] = CharField("VARCHAR", true, true, 16);
    }
};
REGISTER_MODEL(Account);

int main(){
    std::cout<<"we are in the main fn of the models.cpp file in users"<<std::endl;
    Model model;
    model.make_migrations();
    return 0; 
}
