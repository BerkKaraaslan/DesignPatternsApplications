#include <string>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class Application {
public:

	string name;
	int usage_time;

	void start(string deviceName) {

		cout << "App " + name + " is succesfully started! \n" + "This operation made for Device: " + deviceName + " \n";
	}

	void terminate(string deviceName) {

		cout << "App " + name + " is succesfully terminated! \n" + "This operation made for Device: " + deviceName + " \n";
	}

	void getUsageTime(string deviceName) {
		cout << "App " + name + " has " + to_string(usage_time) + " minutes. \n" + "This operation made for Device: " + deviceName + " \n";
	}

	Application(string appName, int usage_time) {
		name = appName;
		this->usage_time  = usage_time;
	}
};


class ApplicationExecutionSystem {

public:
	virtual void runApplication(string appName, string deviceName);

	virtual void terminateApplication(string appName, string deviceName);

	virtual void getApplicationUsageTime(string appName, string deviceName);

	virtual void addApplication(Application* application);

	virtual void removeApplication(Application* application);

private:
	list<Application*> applications;

};


void ApplicationExecutionSystem::runApplication(string appName, string deviceName) {
	list<Application*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == appName) {
			(*it)->start(deviceName);
		}
}

void ApplicationExecutionSystem::terminateApplication(string appName, string deviceName) {
	list<Application*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == appName) {
			(*it)->terminate(deviceName);
		}
}

void ApplicationExecutionSystem::getApplicationUsageTime(string appName, string deviceName) {
	list<Application*>::iterator it;
	for (it = applications.begin(); it != applications.end(); ++it)
		if ((*it)->name == appName) {
			(*it)->getUsageTime(deviceName);
			//return application_usage;
		}
}

void ApplicationExecutionSystem::addApplication(Application* application) {

	applications.push_back(application);
}

void ApplicationExecutionSystem::removeApplication(Application* application) {

	applications.remove(application);
}



class ApplicationManagementAndControlSystem { // Mediator
public:
	virtual void startApplication(string appName, int commandDevicePriority, string deviceName); 
	virtual void terminateApplication(string appName, int commandDevicePriority, string deviceName); 
	virtual void computeApplicationUsageTime(string appName, int commandDevicePriority, string deviceName);
	virtual void setAppExecutionSystem(ApplicationExecutionSystem* newAppExecutionSystem);

	ApplicationExecutionSystem* appExecutionSystem;
};

void ApplicationManagementAndControlSystem::startApplication(string appName, int commandDevicePriority, string deviceName) {
	
	appExecutionSystem->runApplication(appName, deviceName);
}

void ApplicationManagementAndControlSystem::terminateApplication(string appName, int commandDevicePriority, string deviceName) {

	appExecutionSystem->terminateApplication(appName, deviceName);
}

void ApplicationManagementAndControlSystem::computeApplicationUsageTime(string appName, int commandDevicePriority, string deviceName) {

	appExecutionSystem->getApplicationUsageTime(appName, deviceName);
	//return application_usage_time;
}

void ApplicationManagementAndControlSystem::setAppExecutionSystem(ApplicationExecutionSystem* newAppExecutionSystem) {

	appExecutionSystem = newAppExecutionSystem;
}


class TVExecutive : public ApplicationManagementAndControlSystem { // This Mediator uses all methods of super class "ApplicationManagementAndControlSystem"

}; 

class AnotherTVExecutive : public ApplicationManagementAndControlSystem { // This Mediator overrides super class' functions

	virtual void startApplication(string appName, int commandDevicePriority, string deviceName);
	virtual void terminateApplication(string appName, int commandDevicePriority, string deviceName);
	virtual void computeApplicationUsageTime(string appName, int commandDevicePriority, string deviceName);

};

void AnotherTVExecutive::startApplication(string appName, int commandDevicePriority, string deviceName) {

	string additional_info = "This TV Executive coordinates communication of objects in different way. If command device priority is less than 100 then the request of this device will not executed. \n";
	string positive = "This request was accepted because device priority is not less than 20 \n";
	string negative = "This request was not accepted because device priority is less than 20 \n";

	if (commandDevicePriority < 100) {

		cout << additional_info << negative;
	}
	else {
		appExecutionSystem->runApplication(appName, deviceName);
		cout << additional_info << positive;
	}

}

void AnotherTVExecutive::terminateApplication(string appName, int commandDevicePriority, string deviceName) {

	string additional_info = "This TV Executive coordinates communication of objects in different way. If command device priority is less than 100 then the request of this device will not executed. \n";
	string positive = "This request was accepted because device priority is not less than 20 \n";
	string negative = "This request was not accepted because device priority is less than 20 \n";

	if (commandDevicePriority < 100) {

		cout << additional_info << negative;
	}
	else {
		appExecutionSystem->terminateApplication(appName, deviceName);
		cout <<additional_info << positive;
	}
}

void AnotherTVExecutive::computeApplicationUsageTime(string appName, int commandDevicePriority, string deviceName) {

	string additional_info = "This TV Executive coordinates communication of objects in different way. If command device priority is less than 100 then the request of this device will not executed. \n";
	string positive = "This request was accepted because device priority is not less than 20 \n";
	string negative = "This request was not accepted because device priority is less than 20 \n";

	if (commandDevicePriority < 100) {
		
		cout << additional_info << negative;
		
	}
	else {
		appExecutionSystem->getApplicationUsageTime(appName, deviceName);
		cout << additional_info << positive;
		
	}
}

class CommandDevice {

public:
	CommandDevice(ApplicationManagementAndControlSystem* applicationManagenementAndControlSystem, int devicePriority, string deviceName) {
		tvExecutive = applicationManagenementAndControlSystem;
		this->devicePriority = devicePriority;
		this->deviceName = deviceName;
	}

	void setTvExecutive(ApplicationManagementAndControlSystem* newTvExecutive) {
		tvExecutive = newTvExecutive;
	}

	void OpenApplication(string appName) {

		tvExecutive->startApplication(appName, devicePriority, deviceName);
		cout << "***********************************************\n";
	}

	void CloseApplication(string appName) {
		
		tvExecutive->terminateApplication(appName, devicePriority, deviceName);
		cout << "***********************************************\n";
	}

	void DisplayApplicationUsageTime(string appName) {

		tvExecutive->computeApplicationUsageTime(appName, devicePriority, deviceName);
		cout << "***********************************************\n";
	}


	ApplicationManagementAndControlSystem* tvExecutive;
	int devicePriority;
	string deviceName;

};

class RemoteController : public CommandDevice {
public:
	RemoteController(ApplicationManagementAndControlSystem* tvExecutive, int devicePriority, string deviceName) : CommandDevice(tvExecutive, devicePriority, deviceName) {}
};



int main() {
	ApplicationManagementAndControlSystem* applicationManagementAndControlSystem = new TVExecutive();

	Application* application = new Application("Netflix", 100);
	Application* application2 = new Application("Amazon Prime", 350);
	Application* application3 = new Application("Youtube", 500);

	ApplicationExecutionSystem* applicationExecutionSystem = new ApplicationExecutionSystem();
	applicationManagementAndControlSystem->setAppExecutionSystem(applicationExecutionSystem);

	applicationExecutionSystem->addApplication(application);
	applicationExecutionSystem->addApplication(application2);
	applicationExecutionSystem->addApplication(application3);

	CommandDevice* commandDevice = new CommandDevice(applicationManagementAndControlSystem, 100, "Command Device");
	CommandDevice* remoteController = new RemoteController(applicationManagementAndControlSystem, 150, "Remote Controller");

	commandDevice->OpenApplication("Netflix");
	remoteController->OpenApplication("Amazon Prime");
	commandDevice->CloseApplication("Netflix");
	remoteController->DisplayApplicationUsageTime("Youtube");
	
	applicationManagementAndControlSystem = new AnotherTVExecutive(); // Mediator changed
	applicationExecutionSystem = new ApplicationExecutionSystem();

	application = new Application("Netflix", 100);
	application2 = new Application("Amazon Prime", 350);
	application3 = new Application("Youtube", 500);

	applicationExecutionSystem->addApplication(application);
	applicationExecutionSystem->addApplication(application2);
	applicationExecutionSystem->addApplication(application3);

	applicationManagementAndControlSystem->setAppExecutionSystem(applicationExecutionSystem);
	
	commandDevice->setTvExecutive(applicationManagementAndControlSystem);
	remoteController->setTvExecutive(applicationManagementAndControlSystem);

	commandDevice->OpenApplication("Netflix");
	remoteController->OpenApplication("Amazon Prime");
	commandDevice->CloseApplication("Netflix");
	remoteController->DisplayApplicationUsageTime("Youtube");
}