#pragma once

#include <iostream>
#include <string>
#include <variant>
#include "json.hpp"

std::string to_upper(std::string& str);

class FieldAttr{
public:
	std::string ctype, datatype, sql_segment;
	bool primary_key, not_null, unique;

	FieldAttr(std::string ct = "null",std::string dt = "null", bool nn = false, bool uq = false, bool pk = false)
	: ctype(ct), datatype(dt), not_null(nn), unique(uq), primary_key(pk)
	{}
};

class IntegerField: public FieldAttr{
public:
	std::string check_condition;
	int check_constraint;

  IntegerField() = default;
	IntegerField(std::string datatype, bool pk = false, bool not_null = false, bool unique = false, int check_constr = 0, std::string check_cond = "default")
    :FieldAttr("int", datatype, not_null, unique, pk), check_constraint(check_constr), check_condition(check_cond)
 	{
    	sql_generator();
	}

	void sql_generator(){
		datatype = to_upper(datatype);
		if(datatype != "INT" && datatype != "SMALLINT" && datatype != "BIGINT"){
			std::cerr<< "Datatype " <<datatype<<" is not supported by postgreSQL. Provide a valid datatype"<<std::endl;
			return;
		}
		sql_segment += datatype;
		if (not_null) sql_segment = datatype + " NOT NULL";
	}
};

void to_json(nlohmann::json& j, const IntegerField& field);
void from_json(const nlohmann::json& j, IntegerField& field);

class DecimalField: public FieldAttr{
public:
	int max_length, decimal_places;

  DecimalField() = default;
	DecimalField(std::string datatype, int max_length, int decimal_places, bool pk = false)
    :FieldAttr("float", datatype, false, false, pk), max_length(max_length), decimal_places(decimal_places)
	{
    	sql_generator();
	}

	void sql_generator(){
    	datatype = to_upper(datatype);
    	if(datatype != "DECIMAL" && datatype != "REAL"&& datatype != "DOUBLE PRECISION" && datatype != "NUMERIC"){
			std::cerr<< "Datatype" <<datatype<<"is not supported by postgreSQL. Provide a valid datatype"<<std::endl;
			return;
    	}
		if(max_length > 0 || decimal_places > 0)
		  	sql_segment = datatype + "(" + std::to_string(max_length) + "," + std::to_string(decimal_places) + ")";
		else
			std::cerr<<"Max length and/or decimal places cannot be 0 for datatype " << datatype <<std::endl;
	}
};

void to_json(nlohmann::json& j, const DecimalField& field);
void from_json(const nlohmann::json& j, DecimalField& field);

class CharField: public FieldAttr{
public:
	int length;

  CharField() = default;
	CharField(std::string datatype, int length = 0, bool not_null = false, bool unique = false, bool pk = false)
    :FieldAttr("std::string", datatype, not_null, unique, pk), length(length)
	{
	    sql_generator();
	}
	void sql_generator(){
		datatype = to_upper(datatype);
		if(datatype != "VARCHAR" && datatype != "CHAR" && datatype != "TEXT"){
			std::cerr<< "Datatype " <<datatype<<" is not supported by postgreSQL. Provide a valid datatype"<<std::endl;
			return;
		}
		sql_segment += datatype;
		if (length == 0 && datatype != "TEXT"){
      std::cerr<< "Length attribute is required for datatype " << datatype << std::endl;
			return;
		}
		sql_segment += "(" + std::to_string(length) + ")";
		if (not_null) sql_segment +=  " NOT NULL"; 
	}
};

void to_json(nlohmann::json& j, const CharField& field);
void from_json(const nlohmann::json& j, CharField& field);

class BoolField:public FieldAttr{
public:
	bool enable_default, default_value;

	BoolField(bool not_null = false, bool enable_default = false, bool default_value = false)
	:FieldAttr("bool", "BOOLEAN", not_null, false, false), enable_default(enable_default), default_value(default_value)
	{
    	sql_generator();
	}

	void sql_generator(){
		sql_segment += datatype;
		if (not_null)sql_segment += " NOT NULL";
		if (enable_default){
			if(default_value)sql_segment += " DEFAULT TRUE";
			else sql_segment += " DEFAULT FALSE";
		}
	}
};
void to_json(nlohmann::json& j, const BoolField& field);
void from_json(const nlohmann::json& j, BoolField& field);

class BinaryField: public FieldAttr{
public:
	int size;

  BinaryField() = default;
	BinaryField(int size, bool not_null = false, bool unique = false, bool pk = false)
  :FieldAttr("int", "BYTEA", not_null, unique, pk),size(size)
	{
    	sql_generator();
	}
	void sql_generator(){ 
		if(size == 0){
			std::cerr<< "Size cannot be zero for datatype "<<datatype<<std::endl;
			return;
		}
		sql_segment = datatype + "(" + std::to_string(size) + ")";
		if(not_null) sql_segment += " NOT NULL";
	}
};

void to_json(nlohmann::json& j, const BinaryField& field);
void from_json(const nlohmann::json& j, BinaryField& field);

class DateTimeField:public FieldAttr{
public:
	bool enable_default;
	std::string default_val;

  DateTimeField() = default;
	DateTimeField(std::string datatype, bool enable_default = false, std::string default_val = "default", bool pk = false)
  :FieldAttr("std::string",datatype, false, false, pk), enable_default(enable_default), default_val(default_val)
	{
   	sql_generator();
	}
	void sql_generator(){
		datatype = to_upper(datatype);
		if(datatype != "DATE" && datatype != "TIME" && datatype != "TIMESTAMP_WTZ" && datatype != "TIMESTAMP" && datatype != "TIME_WTZ"  && datatype != "INTERVAL"){
			std::cerr<<"Datatype " <<datatype<< "not supported in postgreSQL. Provide a valid datatype"<<std::endl;
			return;
		}

		sql_segment = datatype;
		if(enable_default && default_val != "default"){
			default_val = to_upper(default_val);
			sql_segment += " DEFAULT " + default_val;
		}
	}
};

void to_json(nlohmann::json& j, const DateTimeField& field);
void from_json(const nlohmann::json& j, DateTimeField& field);

class ForeignKey : public FieldAttr{
public:
  std::string model_name, column_name, on_delete, on_update;

	ForeignKey(std::string mn = "def", std::string cn = "def", std::string on_del = "def", std::string on_upd = "def")
	:FieldAttr("null", "FOREIGN KEY", false, false, false), model_name(mn), column_name(cn), on_delete(on_del), on_update(on_upd)
	{}

	std::string sql_generator(const std::string& column){
    if(model_name == "def" || column_name == "def"){
      std::cerr<< "Please provide the reference model name and column name for the column "<< column << std::endl;
		}
	  std::string sql_segment = "FOREIGN KEY(" + column + ") REFERENCES " + model_name + " (" + column_name + ")";
		if(on_delete != "def"){
			on_delete = to_upper(on_delete);
			sql_segment += " ON DELETE " + on_delete;
		} 
		if(on_update != "def" ){
			on_update = to_upper(on_update);
			sql_segment += " ON UPDATE " + on_update;
		}
		return sql_segment;
	}
};

void to_json(nlohmann::json& j, const ForeignKey& field);
void from_json(const nlohmann::json& j, ForeignKey& field);

using DataTypeVariant = std::variant<IntegerField, CharField, BoolField, BinaryField, DateTimeField, ForeignKey, DecimalField>;

void variant_to_json(nlohmann::json& j, const DataTypeVariant& variant);
void variant_from_json(const nlohmann::json& j, DataTypeVariant& variant);
