/*
Lets create a simple example. We have an application which writes to a log file. The configuration of this log file is written in XML.
We use boost::property_tree to read this xml into a configuration object (so basically XML to object), & then basically use that object in log file configuration. */

/*
Log file config XML:
   <debug>
      <filename>application.log</filename>
	  <modules>
	      <module>Finance</module>
	      <module>Admin</module>
		  <module>HR</module>
      </module>
      <level>2</level>
   </debug>	
*/

#include <iostream>
#include <string>
#include <set>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <iterator>
#include <sstream>


using namespace std;
using namespace boost::property_tree;
using namespace boost::property_tree::xml_parser;

#define FILENAME   "debug.filename"
#define MODULES    "debug.modules"
#define MODULE     "debug.modules.module"
#define LEVEL      "debug.level"


//Create an object into which we'll read this XML.
struct LogConfig {
	std::string m_logFileName;
	int m_level;
	std::set<std::string> m_moduleNames;

	void load(const std::string& fileName);
	void save(const std::string& fileName);

	void display() const;
};

void LogConfig::load(const std::string& fileName) {
	ptree pt; //Empty tree

	//Read XML into this ptree;
	read_xml(fileName, pt);

	//Read the fileName
	m_logFileName = pt.get<std::string>(FILENAME);

	//Read the log level
	m_level = pt.get<int>(LEVEL);

	BOOST_FOREACH(ptree::value_type& v, pt.get_child(MODULES))
		m_moduleNames.insert(v.second.data());
}

void LogConfig::save(const std::string& fileName) {
	ptree pt;

	pt.put(FILENAME, m_logFileName);

	pt.put(LEVEL, m_level);

	BOOST_FOREACH(const std::string& moduleName, m_moduleNames)
		pt.add(MODULE, moduleName);

	//Wtite xml out
	write_xml(fileName, pt);
}

void LogConfig::display() const {
	std::cout << "FileName: " << m_logFileName << std::endl;
	std::cout << "LogLevel: " << m_level << std::endl;

	std::cout << "Modules: " << std::endl;
	std::copy(m_moduleNames.begin(), m_moduleNames.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Usage:\n";
		std::cout << "     ./a.out configFileName\n";
		return 1;
	}
	else {
		LogConfig logConfig;
		logConfig.load(argv[1]);

		logConfig.display();
	}

	
	std::cout << "Writing xml now";
	LogConfig lcOut;
	lcOut.m_logFileName = "rajat.log";
	lcOut.m_level = 3;
	std::set<std::string> tempSet;
	tempSet.insert("Finance"); tempSet.insert("HR"); tempSet.insert("Admin");
	lcOut.m_moduleNames = tempSet;

	lcOut.save("configOut.xml");

	stringstream xmlStr;
	return 0;
}