#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
//#include <chrono>


using namespace std;


class cardDec{
private:
	string name;
	string className;
	string rarity;
	string set;
	string type;
	int cost;
public:
	cardDec();
	cardDec(string t_name, string t_className, string t_rarity, string t_set, string t_type, int t_cost);
	~cardDec(){};
	string getName();
	string getClassName();
	string getRarity();
	string getSet();
	string getType();
	int getCost();

};
cardDec::cardDec(string t_name, string t_className, string t_rarity, string t_set, string t_type, int t_cost){
	name = t_name;
	className = t_className;
	rarity = t_rarity;
	set = t_set;
	type = t_type;
	cost = t_cost;
}
cardDec::cardDec() {}
string cardDec::getClassName() {
	return className;
}
string cardDec::getName() {
	return name;
}
string cardDec::getRarity() {
	return rarity;
}
string cardDec::getSet() {
	return set;
}
string cardDec::getType() {
	return type;
}
int cardDec::getCost() {
	return cost;
}
void insertion_filter_sort(vector<cardDec> &arr);
void outTextFile(const string filename, vector<cardDec> arr);
void MergeFull(vector<cardDec> &arr, int low, int mid, int high);
void merge_sort(vector<cardDec> &arr, int low, int high);
void insertion_full_sort(vector<cardDec> &arr);
void printCardDeck(vector<cardDec> arr);
vector<cardDec>::iterator find_middle(vector<cardDec> &arr);

int main(int argc , char**argv) {
	/*const string sortSelect = argv[0];
	const string methodSelect = argv[1];
	const string filename = argv[3];
	const string outputName = argv[4];*/
	//auto start = std::chrono::system_clock::now();;
	//auto end = std::chrono::system_clock::now();;
	int r_cost;
	string r_name;
	string r_className;
	string r_rarity;
	string r_set;
	string r_type;
	vector<cardDec> cardDecVector;

	ifstream file("hs-set-10k.txt");
	string line;
	while (getline(file, line)){
		istringstream isStream(line);
		getline(isStream, r_name, '\t');
		getline(isStream, r_className, '\t');
		getline(isStream, r_rarity, '\t');
		getline(isStream, r_set, '\t');
		getline(isStream, r_type, '\t');
		isStream >> r_cost;
		cardDec tempCard(r_name, r_className, r_rarity, r_set, r_type, r_cost);
		cardDecVector.push_back(tempCard);
	}

	/*if(sortSelect.compare("-full")){
		if(methodSelect.compare("-i")){
			//start = std::chrono::system_clock::now();
			insertion_full_sort(cardDecVector);
			//end = std::chrono::system_clock::now();
		}else if(methodSelect.compare("-m")){
			//start = std::chrono::system_clock::now();
			merge_sort(cardDecVector,0,cardDecVector.size());
			//end = std::chrono::system_clock::now();
		}else cout << "Wrong type of method.";
	}else if (sortSelect.compare("-filter")){
		if(methodSelect.compare("-i")){
			//start = std::chrono::system_clock::now();
			insertion_filter_sort(cardDecVector);
			//end = std::chrono::system_clock::now();
		}else if(methodSelect.compare("-m")){
			//start = std::chrono::system_clock::now();
			merge_sort(cardDecVector,0,cardDecVector.size());
			//end = std::chrono::system_clock::now();
		}else cout << "Wrong type of Method";

	}else cout<< "wrong type of Sort" <<endl;*/

	//std::chrono::duration<double> elapsed_seconds = end-start;
	//cout << "Elapsed Time : "<< elapsed_seconds.count() <<"s" << endl;
	insertion_full_sort(cardDecVector);
	//insertion_filter_sort(cardDecVector);
	//merge_sort(cardDecVector, 0, cardDecVector.size());
	outTextFile("name",cardDecVector);
	//printCardDeck(cardDecVector);
	return 0;
}

void insertion_full_sort(vector<cardDec> &arr){
	int n = arr.size();
	string key = "";
	int i = 0;
	cardDec temp;
	cout << "hello";
	for (int j = 2; j <= n; j++){
		temp = arr[j];
		i = j - 1;
		key = arr[j].getClassName();
		while (i>0 && arr[i].getClassName().compare(key) >0){
			arr[i + 1] = arr[i];
			i = i - 1;
		}
		arr[i + 1] = temp;
	}

	i = 0;
	int costkey = 0;
	for (int j = 2; j <= n; j++){
		costkey = arr[j].getCost();
		key = arr[j].getClassName();
		temp = arr[j];
		i = j - 1;

		while (i>0 && arr[i].getCost() > costkey && arr[i].getClassName().compare(key) == 0){
			arr[i + 1] = arr[i];
			i = i - 1;
		}
		arr[i + 1] = temp;
	}

	i = 0;
	costkey = 0;
	string namekey = "";

	for (int j = 2; j <= n; j++){
		costkey = arr[j].getCost();
		key = arr[j].getClassName();
		namekey = arr[j].getName();
		temp = arr[j];
		i = j - 1;

		while (i>0 && arr[i].getCost() == costkey && arr[i].getClassName().compare(key) == 0 && arr[i].getName().compare(namekey) > 0){
			arr[i + 1] = arr[i];
			i = i - 1;
		}
		arr[i + 1] = temp;
	}
}

void merge_sort(vector<cardDec> &arr, int low, int high){
	int middle = 0;
	if (low < high && low >=0){
		middle = (low + high) / 2;
		merge_sort(arr, low, middle);
		merge_sort(arr, middle + 1, high);
		MergeFull(arr, low, middle, high);
	}

}
void MergeFull(vector<cardDec> &arr, int low, int mid, int high){
	int i = 0;
	int j = 0;
	int k = 0 ;
	vector<cardDec>::iterator middle = arr.begin();
	middle = find_middle(arr);
	vector<cardDec> tempLowVector;
	vector<cardDec> tempHighVector;
	tempLowVector.insert(tempLowVector.begin(), arr.begin(), middle);
	tempHighVector.insert(tempHighVector.begin(), middle, arr.end());
	j=1;
	i=1;
	for (k = low; k <= high; k++){
		//cout << k << endl;
		if (tempLowVector[i].getClassName().compare(tempHighVector[j].getClassName()) >= 0){
			arr[k] = tempLowVector[i];
			cout << i;
			cout <<tempLowVector[i].getName() << endl;
			++i;
		}
		else{
			arr[k] = tempHighVector[j];
			j++;

		}

	}

}
void outTextFile(const string filename , vector<cardDec> arr){
	ofstream outfile;
	outfile.open("hs-set-10k-sorted.txt");
	int size = arr.size();
	for (int i = 0; i <= size; i++){
		outfile << i << ',';
		outfile << arr[i].getName() << ',';
		outfile << arr[i].getClassName() << ',';
		outfile << arr[i].getRarity() << ',';
		outfile << arr[i].getSet() << ',';
		outfile << arr[i].getType() << ',';
		outfile << arr[i].getCost() << endl;
	}
}

void insertion_filter_sort(vector<cardDec> &arr) {
	int n = arr.size();
	string key = "";
	int i = 0;
	cardDec temp;
	for (int j = 2; j <= n; j++) {
		temp = arr[j];
		i = j - 1;
		key = arr[j].getType();
		while (i > 0 && arr[i].getType().compare(key) > 0) {
			arr[i + 1] = arr[i];
			i = i - 1;
		}
		arr[i + 1] = temp;
	}
}


void printCardDeck(vector<cardDec> arr){
	int size = arr.size();
	for (int i = 0; i <= size; i++){
		cout << i << '\t';
		cout << arr[i].getName() << '\t';
		cout << arr[i].getClassName() << '\t';
		cout << arr[i].getRarity() << '\t';
		cout << arr[i].getSet() << '\t';
		cout << arr[i].getType() << '\t';
		cout << arr[i].getCost() << endl;
	}
}
/*advance(it,n1-1);
tempLowVector.insert(tempLowVector.begin(),arr.begin(),it);
it = arr.begin();
advance(it,n1-1);
tempHighVector.insert(tempHighVector.begin(),it,arr.end());
//tempHighVector.push_back( arr[(mid+j)]);

*/
vector<cardDec>::iterator find_middle(vector<cardDec> &arr){
	vector<cardDec>::iterator it = arr.begin();
	int middle = 0;
	if (arr.size() % 2 == 0) {
		middle = arr.size() / 2;
	}
	else {
		middle = (arr.size() - 1) / 2;
	}
	advance(it, middle);
	return it;
}
