#include "../../core/includes/models.hpp"

class Test1 : public Model{
public:
  Test1(){
    fields["test1col1"] = CharField("char", 34, false, true);
    fields["test1col2"] = IntegerField("int");
    fields["test1col3"] = BinaryField(4, true, true, false);
    fields["test1col4"] = DateTimeField("date", false, "26-06-2004", false);
    fields["test1col5"] = BoolField(true, false, true);
    fields["test1col7"] = DecimalField("double precision", 3, 2, false);
  }
};
REGISTER_MODEL(Test1);

class Test2 : public Model{
public:
  Test2(){
    fields["test2col1"] = IntegerField("int");
    fields["test2col2"] = BoolField(true, true, false);
    fields["test2col3"] = BinaryField(8, true, false, true);
    fields["test2col4"] = DateTimeField("time", true, "12:00:00", false);
    fields["test2col5"] = ForeignKey("Test1","Test1_id", "cascade", "update");
    fields["test2col6"] = DecimalField("decimal", 8, 2, false);
    fields["test2col7"] = CharField("varchar",15, true, false);
  }
};
REGISTER_MODEL(Test2);

int main(){
  Model model;
  model.make_migrations();
  return 0; 
}
