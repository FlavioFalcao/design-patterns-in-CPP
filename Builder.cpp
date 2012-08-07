// Family: Creational
// Name: Builder

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum PersintranceType{File, Queue, PathWay};


struct PersistanceAttribute{
PersintranceType type;
char value[30];
};

class DistrWrokPackage{

public:
	DistrWrokPackage(char *type){	
		sprintf_s(_desc, "Distributed Work Package for: %s", type);
	}

	void setFile(char *f, char *v){
		sprintf_s(_temp, "\n File(%s): %s", f, v);
		strcat_s(_desc, _temp);
	}

	void setQueue(char *q, char *v){
		sprintf_s(_temp, "\n Queue(%s): %s",q , v);
		strcat_s(_desc, _temp);
	}

	void setPathWay(char *p, char *v){
		sprintf_s(_temp, "\n Pathway(%s): %s", p, v);
		strcat_s(_desc, _temp);
	}

	const char *getState(){
		return _desc;
	}

private:
	char _desc[200], _temp[80];
};

class Builder{
public:
	virtual void configureFile(char*) = 0;
	virtual void configureQueue(char*) = 0;
	virtual void configurePathWay(char*) = 0;

	DistrWrokPackage *getResult(){
		return _result;
	}

protected:
	DistrWrokPackage *_result;
};

class UnixBuilder : public Builder{
public:
	UnixBuilder(){
		_result = new DistrWrokPackage("Unix");
	}

	void configureFile(char *name){
		_result->setFile("flatfile", name);
	}

	void configureQueue(char *queue){
		_result->setQueue("FIFO", queue);
	}

	void configurePathWay(char *type){
		_result->setPathWay("thread", type);	
	}
};

class VmsBuilder : public Builder{
public:
	VmsBuilder(){
		_result = new DistrWrokPackage("vms");
	}

	void configureFile(char *name){
		_result->setFile("ISAM", name);
	}

	void configureQueue(char *queue){
		_result->setQueue("Priority", queue);
	}

	void configurePathWay(char *type){
		_result->setPathWay("LWP", type);
	}
};

class Reader{
public:
	void setBulder(Builder *b){
		_builder = b;
	}

	void construct(PersistanceAttribute[], int);

private:
	Builder *_builder;
};

void Reader::construct(PersistanceAttribute list[], int num){
	for (int i = 0; i < num; i++)
		if(list[i].type == File)
			_builder->configureFile(list[i].value);
		else if(list[i].type == Queue)
			_builder->configureQueue(list[i].value);
		else if (list[i].type == PathWay)
			_builder->configurePathWay(list[i].value);						
	
}

const int NUM_ENTTRIES = 6;

PersistanceAttribute input[NUM_ENTTRIES] = {
	{File, "state.dat"},
	{File, "config.sys"},
	{Queue, "compute"},
	{Queue, "log"},
	{PathWay, "authentication"},
	{PathWay, "error processing"}	
};


int main(){
	UnixBuilder unixBuilder;
	VmsBuilder vsmBuilder;
	Reader reader;

	reader.setBulder(&unixBuilder);
	reader.construct(input, NUM_ENTTRIES);		
	cout<<unixBuilder.getResult()->getState()<<endl;

	reader.setBulder(&vsmBuilder);
	reader.construct(input, NUM_ENTTRIES);
	cout<<vsmBuilder.getResult()->getState() <<endl;
}
