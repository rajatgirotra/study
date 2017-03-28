/*
Let us know see some other functions of the property tree class.
*/

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <boost/exception/all.hpp>

using namespace boost::property_tree;
using namespace boost::property_tree::xml_parser;
using namespace std;

int main() {
	ptree pt;
	stringstream xmlString[10];

	pt.put("organisation", ""); //Add "organisation" as the child of the node which ptree currently points to. An empty ptree points to the <?xml version="1.0" encoding="utf-8"?> node.
	write_xml(xmlString[0], pt);
	cout << xmlString[0].str() << endl;

	//Now add some data. First get the ptree that contains the "organisation" node.
	cout << endl << endl;
	pt.get_child("organisation").put_value("Standard Chartered Bank"); //put.get_child() throws ptree_bad_data if an exception is thrown.
	write_xml(xmlString[1], pt);
	cout << xmlString[1].str() << endl;

	//Catch ptree_bad_data exception.
	try {
		pt.get_child("NON_EXISTENT");
	} catch(const boost::exception& e) {
		cout <<  endl << endl << endl << boost::diagnostic_information(e) << endl;
	}

	//Now retrieve this data.
	//All of the get() functions are template functions, so you must specify the template parameter to them.
	//So using get() you can data of any arbitrary node.
	std::string str = pt.get<std::string>("organisation");
	cout << endl << endl << "Organisation: " << str << endl;

	//Add some child nodes of organisation. say employee or contractual.
	//You see two ways: Either first get the child or otherwise just use the dotted notation, which is easy i think.
	cout << endl << endl;
	pt.get_child("organisation").put("employee", "");
	pt.put("organisation.contractual", "");
	pt.add("organisation.employee", ""); //Note the difference between put() and add(). add() will add another element with the same key.
	write_xml(xmlString[2], pt);
	cout << xmlString[2].str() << endl;

	//Add some data to employee and contractual elements
	cout << endl << endl;
	pt.get_child("organisation.employee").put_value("Rajat");
	pt.get_child("organisation.contractual").put_value("Raman");
	write_xml(xmlString[3], pt);
	cout << xmlString[3].str() << endl;

	//Now you have two employee elements in organisation. So you cannot be sure what you'll get when you fetch "organisation.employee".
	std::string name = pt.get<

	return 0;
}
