#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include <iostream>
#include <list>
#include "ParticleSystem.h"
#include "PxShape.h"

#include "RenderUtils.hpp"
#include "Suelo.h"
#include "SolidoDinamico.h"
#include "RigidBodySystem.h"

std::string display_text = "Mateme";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
std::list<Particle*>particulas;
ParticleSystem* p=nullptr;
ParticleSystem* p2 = nullptr;
RigidBodySystem* r = nullptr;
using namespace std;
list<Suelo*> s;
//std::vector<Particle*> particulas;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	
	
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	p = new ParticleSystem(gScene,gPhysics);
	//r = new RigidBodySystem(gScene, gPhysics);



	
	////GetCamera()->handleMotion(0, 0);
	//Suelo* abajo = new Suelo({ 0, 0, 0 }, { 20, 1, 20, 1 }, gScene, gPhysics);
	//Suelo* enfrente = new Suelo({ -20, 20, -20 }, { 20, 30, 1, 1 }, gScene, gPhysics);
	//enfrente->suelo->setGlobalPose({ 0, 20, -20 });

	//Suelo* lado = new Suelo({ -20, 20, -20 }, { 1, 30, 30, 1 }, gScene, gPhysics);
	//lado->suelo->setGlobalPose({ -20, 20, 0 });

	//Suelo* lado2 = new Suelo({ 20, 20, -20 }, { 1, 30, 30, 1 }, gScene, gPhysics);
	//lado2->suelo->setGlobalPose({ 20, 20, 0 });

	//Suelo* enfrente2 = new Suelo({ -20, 20, -20 }, { 20, 30, 1, 1 }, gScene, gPhysics);
	//enfrente2->suelo->setGlobalPose({ 0, 20, 20 });

	//GetCamera()->handleAnalogMove(0,0);


	//suelos
	// 
	// 
	
	for (int i = 0; i < 50; ++i) {

		Suelo* Parela = new Suelo({(float) i * 70,1,(float)i *70 }, { 70,1,70,1 }, gScene, gPhysics, { 0.7,0.7,0.1 ,0.5 });
		s.push_back(Parela);
	}
	//el de abajo con viento
	for (int i = 50; i < 60; ++i) {

		Suelo* Parela = new Suelo({ (float)i * 70,-40,(float)i * 70 }, { 70,1,70,1 }, gScene, gPhysics, { 0.2,0.2,0.1 ,0.5 });
		s.push_back(Parela);
	}
	for (int i = 60; i < 120; ++i) {

		Suelo* Parela = new Suelo({ (float)i * 70,100,(float)i * 70 }, { 70,1,70,1 }, gScene, gPhysics, { 0.7,0.7,0.1 ,0.5 });
		s.push_back(Parela);
	}
	//lateral derecha
	for (int i = 120; i < 150; ++i) {
		Suelo* Parela = new Suelo({ (float)i*70,100,(float)i*70+90 }, { 10,100,10,1 }, gScene, gPhysics, { 0.9,0.8,0.4 ,0.5 });
		s.push_back(Parela);
	}
	//lateral izquierda
	for (int i = 150; i < 180; ++i) {
		Suelo* Parela = new Suelo({ (float)i * 70,100,(float)i * 70 - 200 }, { 10,100,10,1 }, gScene, gPhysics, { 0.9,0.8,0.4 ,0.5 });
		s.push_back(Parela);
	}
	//lateral derechas
	for (int i = 180; i < 210; ++i) {
		Suelo* Parela = new Suelo({ (float)i * 70,100,(float)i * 70 + 200 }, { 10,100,10,1 }, gScene, gPhysics, { 0.9,0.8,0.4 ,0.5 });
		s.push_back(Parela);
	}
	//el de abajo con viento
		for (int i = 210; i < 260; ++i) {

			Suelo* Parela = new Suelo({ (float)i * 70,-40,(float)i * 70 }, { 70,1,70,1 }, gScene, gPhysics, { 0.2,0.2,0.1 ,0.5 });
			s.push_back(Parela);
		}

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	/*list<Particle*>::iterator e = particulas.begin();
	while (e != particulas.end()) {
		auto aux = e;
		++aux;
		if((*e)->gettimer() <= 3)(*e)->integrate(t);
		else { delete* e; particulas.remove(*e); }
		e = aux;
	}*/
	if(p!=nullptr)p->update(t);
	//if (p2 != nullptr)p2->update(t);
	//if (r != nullptr)r->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	auto x = s.begin();
		/*while (x != s.end()) {
			delete(*x);
		}*/
	delete(p);
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'T':
		p->movePlayer();
		break;
	case 'F':
		p->MoveRight();
		break;
	case 'H':
	
		p->MoveLeft();
		break;
	default: break;
	
	}
	
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	/*const string a = actor1->getName();
	const string b = actor2->getName();
	std::cout << a << std::endl;*/
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}