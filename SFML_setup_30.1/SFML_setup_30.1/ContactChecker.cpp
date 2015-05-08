#include "ContactChecker.h"


MyContactListener::MyContactListener() : _contacts() {
}

MyContactListener::~MyContactListener() {
}

void MyContactListener::BeginContact(b2Contact* contact) {
	 /*We need to copy out the data because the b2Contact passed in
	 is reused.*/
	ContactCheck myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_contacts.push_back(myContact);

}

void MyContactListener::EndContact(b2Contact* contact) {
	ContactCheck myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
	std::vector<ContactCheck>::iterator pos;
	pos = std::find(_contacts.begin(), _contacts.end(), myContact);
	
	if (pos != _contacts.end()) 
	{
		_contacts.erase(pos);
	}

}

void MyContactListener::PreSolve(b2Contact* contact,
	const b2Manifold* oldManifold) {
}

void MyContactListener::PostSolve(b2Contact* contact,
	const b2ContactImpulse* impulse) {
}

//void begin_contact(b2Contact* contact)
//{      //check if fixture A was a ball
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if (bodyUserData)
//		static_cast<Ammo*>(bodyUserData)->start_contact();
//
//	//check if fixture B was a ball
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if (bodyUserData)
//		static_cast<Ammo*>(bodyUserData)->start_contact();
//
//
//
//}

//void EndContact(b2Contact* contact) {
//
//	//check if fixture A was a ball
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if (bodyUserData)
//		static_cast<Ammo*>(bodyUserData)->end_contact();
//
//	//check if fixture B was a ball
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if (bodyUserData)
//		static_cast<Ammo*>(bodyUserData)->end_contact();
//
//}