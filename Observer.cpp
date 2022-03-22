#include <string>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class Application {

public:
	
	void printAppInfo() {
		cout << "Application with name: " + name + " and  version: " + version + " is running!" + "\n";
	}
	Application(string appName) {
		name = appName;
	}

	void setVersion(string appVersion) {
		version = appVersion;
	}

private:

	string version;
	string name;
};

class UpdateManager;

class ApplicationManager { // every ApplicationManager corresponds to a smart TV because every TV has 1 ApplicationManager

public:
	virtual void displayLatestAppVersion(UpdateManager* appUpdateManager); 
															 
	string name;
	
	ApplicationManager(string appManagerName) {
		name = appManagerName;
	}

};																 




class UpdateManager { // every UpdateManager corresponds to update manager of some app. ex: Netflix,Youtube

public:
	UpdateManager(string name) { // bu isim ile app olustur

		App = new Application(name);
		App->setVersion("1.0"); // Initial version

	}
	string appName;
	Application* App;
	virtual void Attach(ApplicationManager*);
	virtual void Detach(ApplicationManager*);
	virtual void Notify();
	virtual void updateApp(string newVersion); // bu metot her cagirildiginda notify yapilacak
	

private:
	list<ApplicationManager*> applicationManagers;
};

void UpdateManager::Attach(ApplicationManager* applicationManager) {
	applicationManagers.push_back(applicationManager);
}

void UpdateManager::Detach(ApplicationManager* applicationManager) {
	applicationManagers.remove(applicationManager);
}

void UpdateManager::Notify() {

	list<ApplicationManager*>::iterator it;
	for (it = applicationManagers.begin(); it != applicationManagers.end(); ++it)
		(*it)->displayLatestAppVersion(this);
}

void UpdateManager::updateApp(string newVersion) {

	App->setVersion(newVersion);
	Notify();
}


void ApplicationManager::displayLatestAppVersion(UpdateManager* appUpdateManager) {
	cout << "Application Manager with name: " + name + " worked!" + "\n";
	appUpdateManager->App->printAppInfo();
	cout << "***********************************************\n";
}




int main() {



	ApplicationManager* appManager = new ApplicationManager("Manager 1");
	ApplicationManager* appManager2 = new ApplicationManager("Manager 2");
	ApplicationManager* appManager3 = new ApplicationManager("Manager 3");

	UpdateManager* netflixUpdateManager = new UpdateManager("Netflix");

	netflixUpdateManager->Attach(appManager);
	netflixUpdateManager->Attach(appManager2);
	netflixUpdateManager->Attach(appManager3);

	

	netflixUpdateManager->updateApp("2.0");


}