#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


struct Data {
	string name;
	string numberOfLines;
	int numberOfRepeats;
};
class SmlCompiler {
private:
	string adderess;
	string file[9999];
	int numberOfLines;
	Data data[9999];
	int numberOfdata;
	vector<string> split(string s, string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		string token;
		vector<string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}
	string trim(const std::string& str,const std::string& whitespace = " \t")
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}
	string reduce(const std::string& str,const std::string& fill = " ",const std::string& whitespace = " \t")
	{
		// trim first
		auto result = trim(str, whitespace);

		// replace sub ranges
		auto beginSpace = result.find_first_of(whitespace);
		while (beginSpace != std::string::npos)
		{
			const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
			const auto range = endSpace - beginSpace;

			result.replace(beginSpace, range, fill);

			const auto newStart = beginSpace + fill.length();
			beginSpace = result.find_first_of(whitespace, newStart);
		}

		return result;
	}
	void init() {
		numberOfLines = 0;
		ifstream files(adderess);
		if (files.is_open()) {
			string line;
			while (getline(files, line)) {
				file[numberOfLines] = line.c_str();
				numberOfLines++;
			}
			files.close();
		}
		analysis();
	}
	void addToData(string NAME, int LINE) {
		if (data[0].numberOfRepeats == 0) { 
			data[0].name = NAME;
			data[0].numberOfRepeats ++;
			data[0].numberOfLines = to_string(LINE);
			numberOfdata++;
		}
		else {
			int temp = 0;
			for (int i = 0; i < numberOfdata; i++) {
				if (data[i].name == NAME) {
					temp = 1;
					data[i].numberOfRepeats++;
					data[i].numberOfLines += "," + to_string(LINE);
				}
			}
			if (temp == 0) {
				Data newData;
				newData.name = NAME;
				newData.numberOfRepeats = 1;
				newData.numberOfLines = to_string(LINE);
				numberOfdata++;
				data[numberOfdata] = newData;

			}
		}
	}
	void addToDatas(string NAME, int LINE) {
			for (int i = 0; i < numberOfdata; i++) {
				if (data[i].name == NAME) {
					data[i].numberOfRepeats++;
					data[i].numberOfLines += "," + to_string(LINE);
				}
			}
			
		}
	void analysis() {
		numberOfdata = 0;
		Data zero;
		zero.numberOfRepeats = 0;
		data[0] = zero;
		for (int i = 0; i < numberOfLines; i++) {
			file[i] = reduce(file[i]);
			string text = file[i];
			size_t pos = 0;
			string delimiter = " ";
			string token ;
			int situ = 0;
			vector<string> v = split(text, delimiter);
			for (auto m : v) {
				if (situ == 1) {
					addToData(m, i);
					break;
				}
				if (m == "class" || m == "int" || m == "string" || m == "void" || m == "struct") {
					situ = 1;
				}
			}
		}
		for (int i = 0; i < numberOfLines; i++) {
			file[i] = reduce(file[i]);
			string text = file[i];
			size_t pos = 0;
			string delimiter = " ";
			string token;
			int situ = 0;
			vector<string> v = split(text, delimiter);
			for (auto m : v) {
				addToDatas(m, i);
			}
		}

	}
	void sort() {
		Data temp;
		for (int i = 0; i < numberOfdata; i++) {
			for (int j = 0; j < numberOfdata; j++) {
				if (data[i].numberOfRepeats > data[j].numberOfRepeats) {
					temp = data[j];
					data[j] = data[i];
					data[i] = temp;
				}

			}
		}
	}
public:
	void addAddress(string FILENAME) {
		adderess = FILENAME;
		init();
	}
	void showFile(){
		for (int i = 0; i < 60; i++) {
			cout << "_";
		}
		cout << endl;
		for (int i = 0; i < numberOfLines; i++) {
			cout << file[i] << endl;
		}
		for (int i = 0; i < 60; i++) {
			cout << "_";
		}
		cout << endl;
	}
	void showData() {
		sort();
		cout << "Data Analysis = " << endl;
		for (int i = 0; i < numberOfdata; i++) {
			cout << "Name = " << data[i].name;
			cout << "       ";
			cout << "Number Of Repeats = " << data[i].numberOfRepeats;
			cout << "       ";
			cout << "Found in These Lines = " << data[i].numberOfLines;
			cout << endl;

		}
	}
};


int main() {
	string fileName;
	SmlCompiler compiler;
	cout << "Link file ra vared Konid = ";
	cin >> fileName;
	compiler.addAddress(fileName);
	compiler.showFile();
	compiler.showData();

	return 0;
}


//Mohammad Mahdi Safarmohammadloo
