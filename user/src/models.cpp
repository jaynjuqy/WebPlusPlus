#include "../../core/includes/models.hpp"

class User : public Model{
public:
    User(){
        fields["name"] = CharField("varchar", 34, false, true);
        fields["yob"] = IntegerField("int");
    }
};
REGISTER_MODEL(User);

class Account : public Model{
public:
    Account(){
        fields["balance"] = DecimalField("decimal", 8, 2);
        fields["acc_no"] = CharField("char",15, true, false);
    }
};
REGISTER_MODEL(Account);

int main(){
    Model model;
    model.make_migrations();
    return 0; 
}
