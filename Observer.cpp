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
	UpdateManager(string name) {

		App = new Application(name);
		App->setVersion("1.0"); // Initial version

	}

	Application* App;
	virtual void Attach(ApplicationManager*);
	virtual void Detach(ApplicationManager*);
	virtual void Notify();
	virtual void updateApp(string newVersion);
	

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



class ConcreteApplicationManager : public ApplicationManager {

public:

	ConcreteApplicationManager(string appManagerName) : ApplicationManager(appManagerName) {}
		
};

class anotherConcreteApplicationManager : public ApplicationManager {

public:

	anotherConcreteApplicationManager(string appManagerName) : ApplicationManager(appManagerName) {}

};

class ConcreteUpdateManager : public UpdateManager {

public:

	ConcreteUpdateManager(string name) : UpdateManager(name) {}
};













/*
int main() {

	ApplicationManager* appManager = new ConcreteApplicationManager("TV Manager 1");
	ApplicationManager* appManager2 = new ConcreteApplicationManager("TV Manager 2");
	ApplicationManager* appManager3 = new anotherConcreteApplicationManager("TV Manager 3");
	ApplicationManager* appManager4 = new anotherConcreteApplicationManager("TV Manager 4");

	UpdateManager* netflixUpdateManager = new ConcreteUpdateManager("Netflix");
	UpdateManager* spotifyUpdateManager = new ConcreteUpdateManager("Spotify");

	netflixUpdateManager->Attach(appManager);
	netflixUpdateManager->Attach(appManager2);
	netflixUpdateManager->Attach(appManager3);
	netflixUpdateManager->Attach(appManager4);

	spotifyUpdateManager->Attach(appManager);
	spotifyUpdateManager->Attach(appManager2);

	netflixUpdateManager->updateApp("2.0");
	spotifyUpdateManager->updateApp("2.0");

	netflixUpdateManager->Detach(appManager2);

	netflixUpdateManager->updateApp("3.0");

}

*/

