#include <string>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class ApplicationAbstraction;
class ApplicationImplementor;

class ApplicationManager { 

public:
	
	
	virtual void runApplication(string name); // isim ile applications da arayip buldugunu calistiracak

	virtual void updateImplementation(string appName, ApplicationImplementor* implementation);

	virtual void addApplication(ApplicationAbstraction* application);

	virtual void removeApplication(ApplicationAbstraction* application);

private:
	list<ApplicationAbstraction*> applications;

};


class ApplicationAbstraction {

public:

	string name;

	ApplicationAbstraction(string applicationName) {
		name = applicationName;
		implementation = nullptr;
	}

	virtual void setImplementation(ApplicationImplementor*);

	virtual void run();

private:
	ApplicationImplementor* implementation;


};

class ApplicationImplementor {

public:

	string implementationInfo;

	ApplicationImplementor(string info) {
		implementationInfo = info;
	}

	virtual void runApp(string applicationName);
};

void ApplicationImplementor::runApp(string applicationName) {
	cout << "App " + applicationName + "  is running with implementation info: " + implementationInfo + "\n";
	cout << "***********************************************\n";

}



void ApplicationManager::runApplication(string name) {
	list<ApplicationAbstraction*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == name)
			(*it)->run();

}

void ApplicationManager::addApplication(ApplicationAbstraction* application) {

	applications.push_back(application);
}

void ApplicationManager::removeApplication(ApplicationAbstraction* application) {

	applications.remove(application);
}

void ApplicationManager::updateImplementation(string name, ApplicationImplementor* imp) {
	list<ApplicationAbstraction*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == name)
			(*it)->setImplementation(imp);

}


void ApplicationAbstraction::setImplementation(ApplicationImplementor* imp) {

	implementation = imp;
}

void ApplicationAbstraction::run() {

	if (implementation != nullptr)
		implementation->runApp(name);
}

int main() {

	ApplicationManager* applicationManager = new ApplicationManager();

	ApplicationAbstraction* netflixAbstraction = new ApplicationAbstraction("Netflix");

	ApplicationAbstraction* amazonPrimeAbstraction = new ApplicationAbstraction("Amazon Prime");

	ApplicationAbstraction* youtubeAbstraction = new ApplicationAbstraction("Youtube");

	ApplicationImplementor* netflixImplementor = new ApplicationImplementor("This is first version of Netflix");

	ApplicationImplementor* amazonPrimeImplementor = new ApplicationImplementor("This is first version of Amazon Prime");

	ApplicationImplementor* youtubeImplementor = new ApplicationImplementor("This is first version of Youtube");

	applicationManager->addApplication(netflixAbstraction);
	applicationManager->addApplication(amazonPrimeAbstraction);
	applicationManager->addApplication(youtubeAbstraction);

	applicationManager->updateImplementation("Netflix", netflixImplementor);
	applicationManager->updateImplementation("Amazon Prime", amazonPrimeImplementor);
	applicationManager->updateImplementation("Youtube", youtubeImplementor);

	applicationManager->runApplication("Netflix");
	applicationManager->runApplication("Amazon Prime");
	applicationManager->runApplication("Youtube");

	ApplicationImplementor* netflixImplementor_2 = new ApplicationImplementor("This is second version of Netflix! Now Netflix contains a lot of extra features.");

	ApplicationImplementor* amazonPrimeImplementor_2 = new ApplicationImplementor("This is second version of Amazon Prime! Now Amazon Prime contains a lot of extra features.");

	ApplicationImplementor* youtubeImplementor_2 = new ApplicationImplementor("This is second version of Youtube! Now Youtube contains a lot of extra features.");

	applicationManager->updateImplementation("Netflix", netflixImplementor_2);
	applicationManager->updateImplementation("Amazon Prime", amazonPrimeImplementor_2);
	applicationManager->updateImplementation("Youtube", youtubeImplementor_2);

	applicationManager->runApplication("Netflix");
	applicationManager->runApplication("Amazon Prime");
	applicationManager->runApplication("Youtube");

}