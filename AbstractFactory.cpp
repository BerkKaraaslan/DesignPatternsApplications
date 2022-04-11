#include <string>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class User {
public:

	int userInfo;

	User(int userInfo) {
		this->userInfo = userInfo;
	}
};


class UserFactory {
public:
	virtual string getColorPreference() { return ""; }
	virtual string getThemePreference() { return ""; }
	virtual string getLayoutPreference() { return ""; }

};

class YoungUserFactory : public UserFactory {
public:
	string getColorPreference() {
		return "Light Blue"; 
	}

	string getThemePreference() { 
		return "Opra";
	}

	string getLayoutPreference() {
		return "Grid";
	}

};

class AnimationUserFactory : public UserFactory {
public:
	string getColorPreference() {
		return "Pink";
	}

	string getThemePreference() {
		return "Velvet";
	}

	string getLayoutPreference() {
		return "Border";
	}

};

class DarkUserFactory : public UserFactory {
public:
	string getColorPreference() {
		return "Black";
	}

	string getThemePreference() {
		return "Darcula";
	}

	string getLayoutPreference() {
		return "Grid";
	}

};

class LightUserFactory : public UserFactory {
public:
	string getColorPreference() {
		return "White";
	}

	string getThemePreference() {
		return "Shiny";
	}

	string getLayoutPreference() {
		return "Center";
	}

};

class OldUserFactory : public UserFactory {
public:
	string getColorPreference() {
		return "Light Green";
	}

	string getThemePreference() {
		return "Green Valley";
	}

	string getLayoutPreference() {
		return "Grid";
	}

};


class Application {

public:

	string name;

	void run(UserFactory* userFactory) {
		makeCustomizedUserInterface(userFactory);
		cout << "App " + name + " is running with customized interface! \n";
		cout << "***********************************************\n";
	}

	void makeCustomizedUserInterface(UserFactory* userFactory) {
		cout << "Customized user interface made with Color: " + userFactory->getColorPreference() + " Theme: " + userFactory->getThemePreference();
	    cout << " and Layout: " + userFactory->getLayoutPreference() + "\n";
	}

	Application(string appName) {
		name = appName;
	}

};



class ApplicationManager {
public:
	ApplicationManager() {
		userFactories[0] = new YoungUserFactory();
		userFactories[1] = new AnimationUserFactory();
		userFactories[2] = new DarkUserFactory();
		userFactories[3] = new LightUserFactory();
		userFactories[4] = new OldUserFactory();
	}

	virtual void addApplication(Application* application);

	virtual void removeApplication(Application* application);

	virtual void runCustomizedApplication(string name, User* user); // once user i classify edip factory yi belirleyecek daha sonra app i o factory ile konfigüre edecek

	virtual UserFactory* classifyUser(User* user); 
	
private:
	list<Application*> applications;
	UserFactory* userFactories[5];
};


void ApplicationManager::runCustomizedApplication(string name, User* user) {
	list<Application*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == name) {
			UserFactory* userFactory = classifyUser(user);
			(*it)->run(userFactory);
		}
}

void ApplicationManager::addApplication(Application* application) {

	applications.push_back(application);
}

void ApplicationManager::removeApplication(Application* application) {

	applications.remove(application);
}

UserFactory* ApplicationManager::classifyUser(User* user) {

	if (user->userInfo <= 10) {
		return userFactories[0]; // returns YoungUserFactory
	} 
	
	else if (user->userInfo <= 40) {
		return userFactories[4]; // returns OldUserFactory
	}

	else if (user->userInfo <= 75) {
		return userFactories[1]; // returns AnimationUserFactory
	}

	else if (user->userInfo <= 90) {
		return userFactories[3]; // returns LightUserFactory
	}

	else {
		return userFactories[2]; // returns DarkUserFactory
	}
}


/*

int main() {

	ApplicationManager* applicationManager = new ApplicationManager();

	Application* application = new Application("Netflix");
	Application* application2 = new Application("Amazon Prime");
	Application* application3 = new Application("Youtube");


	applicationManager->addApplication(application);
	applicationManager->addApplication(application2);
	applicationManager->addApplication(application3);

	User* user = new User(5); // young
	User* user2 = new User(25); // old
	User* user3 = new User(63); // animation
	User* user4 = new User(90); // light 
	User* user5 = new User(250); // dark


	applicationManager->runCustomizedApplication("Netflix", user);
	applicationManager->runCustomizedApplication("Netflix", user2);
	applicationManager->runCustomizedApplication("Amazon Prime", user3);
	applicationManager->runCustomizedApplication("Amazon Prime", user4);
	applicationManager->runCustomizedApplication("Youtube", user5);

}

*/