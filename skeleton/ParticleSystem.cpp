#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem( PxScene* scene, PxPhysics* gPhysics, const Vector3& g):scene(scene),gPhysics(gPhysics) {
	_gravity = g;
	createFireworkSystem();
	Vector3 g2(0, -9.8, 0);
	gr = new GravityForceGenerator(g2);
	force_registry = new ParticleForceRegistry();
	fg.push_back(gr);
	g2 = Vector3(0, -3.8, 0);
	fg.push_back(new GravityForceGenerator(g2));

	wf = new WindForceGenerator(Vector3(90,100,90),Vector3(-70,-60,-60),Vector3(50,50,50),3,0);
	
	                                  //Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2
	tg = new TorbellinoForceGenerator({ 0.0f,0.0f,0.0f },{0,0,0},{0,0,0},1.7,0);
	eg = new ExplosionForceGenerator({0,0,0},{90,90,90},60400,10);
	Vector3 centre(0, 0, 0);
	fg.push_back(wf);
	fg.push_back(tg);
	fg.push_back(eg);

	////generamos particulas para luego la explosion
	for (int i = 0; i < 15; ++i) {
		// Calcular una posición aleatoria dentro del área
		float randomRadius = (static_cast<float>(rand()) / RAND_MAX) * 50;
		float theta = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;
		float phi = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;

		float x = centre.x + randomRadius * sin(theta) * cos(phi);
		float y = centre.y + randomRadius * sin(theta) * sin(phi);
		float z = centre.z + randomRadius * cos(theta);

		// Dirección fija para mantenerse quietas
		Vector3 direction(0.0f, 0.0f, 0.0f);

		// Crear la partícula y añadirla al contenedor
		Particle* newParticle = new Firework(Vector3(x, y, z), direction, _gravity, 2, Vector4{ 0.4f, 0.3f, 0.4f, 1.0f }, 0,scene,gPhysics);
		newParticle->GetPxRigidDynamic()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);//QUITAR GRAVEDAD
		newParticle->GetPxRigidDynamic()->addForce(PxVec3(0.0f, 0.0f, 0.0f));
		newParticle->GetPxRigidDynamic()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
		_particles.push_back(newParticle);
		explosion_parts.push_back(newParticle);
	}
	//_firework_generator = new ParticleGenerator();


	pl = new Particle(Vector3{ 10,30.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0,scene,gPhysics);
	pl->setDuration(9999);
	pl->SetLinearVelocity({ 100,0,100 });
}
void ParticleSystem::AplicarFuerzaSegunRaton(const physx::PxVec3& posicionRaton, const physx::PxVec3& camaraPosicion, physx::PxRigidDynamic* rigidDynamic) {
	// Calcula la dirección desde la cámara hasta la posición del ratón en el mundo
	physx::PxVec3 direccion = posicionRaton - camaraPosicion;
	direccion.normalize();

	// Aplica una fuerza en la dirección calculada
	physx::PxReal fuerzaMagnitude = 100.0f;  // Ajusta según sea necesario
	physx::PxVec3 fuerza = direccion * fuerzaMagnitude;

	// Aplica la fuerza al objeto
	pl->SetLinearVelocity(fuerza);
}
ParticleSystem::~ParticleSystem() {
	auto c = _particles.begin();
	while (c != _particles.end()) {
		Particle* v = *c;
		++c;
	//	onParticleDeath(v);
		
	}
	for (auto it = _particle_generators.begin(); it != _particle_generators.end(); ++it) {
		delete* it;
	}
	_particle_generators.clear();
	delete(force_registry);
	auto d = fg.begin();
	while (d != fg.end()) {
		auto v = d;
		++d;
		delete(*v);
		
	}
	fg.clear();
	auto x = to_delete.begin();
	while (x != to_delete.end()) {
		Particle* sd = *x;
		++x;
		scene->removeActor(*(sd->GetPxRigidDynamic()));
	//	sd->GetPxRigidDynamic()->detachShape(*(sd->getShape()));
	//	sd->getRenderItem()->release();
		sd->GetPxRigidDynamic()->release();
		scene->removeActor(*(sd->GetPxRigidDynamic()));
		sd->release();
		delete(sd);
		//p->GetPxRigidDynamic()->release();
	}
}
void ParticleSystem::explosion() {
	for (auto d : explosion_parts) {
		
		force_registry->addRegistry(eg, d);
	}

}
void ParticleSystem::update(double t) {
	auto c = _particles.begin();
	force_registry->updateForces(t);
	while (c != _particles.end()) {
		auto v = c;
		++c;
		bool finish=(*v)->integrate(t);
		//std::cout << (*v)->gettimer() << "\n";
		
			if ((*v)->_type>0 && finish) {
				Firework* firework = static_cast<Firework*>(*v);
				std::list<Particle*> p = firework->explode();
				onParticleDeath(*v);
				for (auto d : p) {
					_particles.push_back(d);
					force_registry->addRegistry(gr, d);
					force_registry->addRegistry(wf, d);
				}
				
			}
			else if (finish) { 
				onParticleDeath(*v);
			}

	}
	
}
void ParticleSystem::generateFirework(unsigned firework_type) {
	
	Firework* ne;
	Particle* pu;
	std::list<Particle*> p;
	//switch (firework_type)
	//{
	//case 1: {
	//	 ne = new Firework(Vector3(GetCamera()->getEye().x - 50, GetCamera()->getEye().y - 50, GetCamera()->getEye().z - 50), Vector3(GetCamera()->getDir().x * 100, GetCamera()->getDir().y * 80, GetCamera()->getDir().z * (80)), _gravity, 2, Vector4{ 0.4 , 0.3 , 0.4,1 }, firework_type);
	//	_particles.push_back(ne);
	//	ne->addGenerator(_firework_generator);
	//	/*Vector3 p = ne->GetPos();
	//	ne->setPos({ p.x - 40,p.y,p.z-40 });*/
	//	force_registry->addRegistry(fg[1], ne);
	//	force_registry->addRegistry(tg, ne);
	//	break;
	//}
	//case 2: {
	//	
	//	ne = new Firework(Vector3(GetCamera()->getEye().x , GetCamera()->getEye().y , GetCamera()->getEye().z ), Vector3(GetCamera()->getDir().x * 100, GetCamera()->getDir().y * 80, GetCamera()->getDir().z * (80)), _gravity, 2, Vector4{ 0.4 , 0.3 , 0.4,1 }, 2,scene,gPhysics);
	//	_particles.push_back(ne);
	//	ne->SetLinearVelocity(GetCamera()->getDir());
	//	ne->addGenerator(_firework_generator);
	//	//ne->GetPxRigidDynamic()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);//QUITAR GRAVEDAD
	//	ne->GetPxRigidDynamic()->addForce(PxVec3(0.0f, 0.0f, 0.0f));
	//	ne->GetPxRigidDynamic()->setLinearVelocity(PxVec3(0.0f, 0.0f, 0.0f));
	//	force_registry->addRegistry(wf, ne);
	//	force_registry->addRegistry(gr, ne);
	//	break;
	//}
	//case 3:{
	//	ne = new Firework(Vector3(GetCamera()->getEye().x - 50, GetCamera()->getEye().y - 50, GetCamera()->getEye().z - 50), Vector3(GetCamera()->getDir().x * 100, GetCamera()->getDir().y * 80, GetCamera()->getDir().z * (80)), _gravity, 2, Vector4{ 0.4 , 0.3 , 0.4,1 }, firework_type);
	//	_particles.push_back(ne);
	//	ne->addGenerator(g3);
	//	force_registry->addRegistry(gr, ne);
	//	
	//	break;
	//}

	//default:
	//	break;
	//}
	switch (firework_type)
	{
	case 1:
		fire->setOrigin({ 10,0,10 });
		fire->setMeanVelocity({ 2,2,2 });
		 p = fire->generateParticles();
		for (auto c : p) {
			_particles.push_back(c);
		}
		break;
	case 2:
		_firework_generator->setOrigin({ 10,0,10 });
		_firework_generator->setMeanVelocity({ 2,2,2 });
		p = _firework_generator->generateParticles();
		for (auto c : p) {
			_particles.push_back(c);
		}
	case 3:
		g2->setOrigin({ 10,0,10 });
		g2->setMeanVelocity({ 2,2,2 });
		p = g2->generateParticles();
		for (auto c : p) {
			_particles.push_back(c);
		}
		break;
	default:
		break;
	}
	



}

void ParticleSystem::Torbelline() {

	Particle* p = new Particle(Vector3{ 10,30.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0, scene, gPhysics);
	p->setDuration(3);
	force_registry->addRegistry(tg, p);
	_particles.push_back(p);
}
ParticleGenerator* ParticleSystem::getParticleGenerator(const std::string& n) {
	if (n == "fireworkGenerator") {
		return _firework_generator;
	}
	else {
		return _firework_generator;
	}
}
void ParticleSystem::onParticleDeath(Particle* v) {
	auto c = force_registry->begin();
	while ( force_registry->size()>0&  c != force_registry->end()) {
		auto d = c;
		++c;
		if (v == d->second) {
			d->second = nullptr;
		}
	}


	if (v->GetPxRigidDynamic() != nullptr) {
		scene->removeActor(*(v->GetPxRigidDynamic()));
		v->GetPxRigidDynamic()->detachShape(*(v->getShape()));
		v->getRenderItem()->release();
		v->GetPxRigidDynamic()->release();
		_particles.remove(v);
		
		delete(v);
	}
	else {
		v->getRenderItem()->release();
		_particles.remove(v);
		delete(v);
	}
	


}
void ParticleSystem::createFireworkSystem() {
	_firework_generator = new GaussianParticleGenerator(scene,gPhysics);
	_firework_generator->setGravity(_gravity);
	_particle_generators.push_back(_firework_generator);
	

	g2 = new UniformParticleGenerator();
	_particle_generators.push_back(g2);
	g2->setGravity(_gravity);
	g2->pos_width = Vector3(0, 0,0);
	g2->vel_width = Vector3(20, 50, 10);



	 g3 = new GaussianParticleGenerator(scene,gPhysics);
	_particle_generators.push_back(g3);
	g3->setGravity(0*_gravity);
	 g3->dev_pos = Vector3(1, 1,1);
	g3->dev_vel = Vector3(60, 1, 50);

	fire = new MiniFirework_Generator(scene,gPhysics);
	_particle_generators.push_back(fire);
	fire->setGravity(10*_gravity);
	fire->pos_width = Vector3(7, 3, 7);
	fire->vel_width = Vector3(16, 12, 11);
	fire->setNParticles(10);
	fire->setgenerator(g3);

}
void ParticleSystem::generateDinamic() {
	float randomX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // Número aleatorio entre -1 y 1
	float randomY = 1; // Número aleatorio entre -1 y 1
	float randomZ = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // Número aleatorio entre -1 y 1

	// Normaliza el vector para asegurarse de que tenga longitud 1
	physx::PxVec3 randomDirection(randomX, randomY, randomZ);
	randomDirection.normalize();
	//(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color, int c, PxScene* scene, PxPhysics* gPhysi
	Firework* p = new Firework({-100,30,-100}, randomDirection,{0,0,0},1,{0.5,0.3,0.3,1},1,scene,gPhysics);
	p->SetLinearVelocity(randomDirection);
	p->addGenerator(_firework_generator);
//PxScene* scene, PxPhysics* gPhysics, Vector3  pos, Vector3 size
	//SolidoDinamico* d = new SolidoDinamico(scene, gPhysics, { -100,30,-100 }, { 2,2,2 });
	//d->setLinearVel(randomDirection);
	_particles.push_back(p);
}

void ParticleSystem::generateSpringDemo() {

	// First one standard spring uniting 2 particles
				//10.0, 10.0, 0.0 3, (0.0, 0.0, 0.0 3, (0.0, 0.0, 0.0 3, 0.85, 60)
								//Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color,int c
	Particle* pl = new Particle(Vector3{ -10.0,50.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0,scene,gPhysics);

	Particle * p2 = new Particle(Vector3{ 10.0,50.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0,scene,gPhysics);
	
	SpringForceGenerator * f1 = new SpringForceGenerator(1, 10, p2);
	force_registry->addRegistry(f1, pl);

	SpringForceGenerator * f2 = new SpringForceGenerator(1, 10, pl);
	force_registry->addRegistry(f2, p2);

	fg.push_back(f1);

	fg.push_back(f2);

	_particles.push_back(pl);

	_particles.push_back(p2);


	WindForceGenerator* wind = new WindForceGenerator(Vector3(0,500,0),{0,-30,0},{100,60,300},0.5,0);
	pl->setDuration(90);
	p2->setDuration(90);
	force_registry->addRegistry(wind, pl);
	force_registry->addRegistry(wind, p2);
	force_registry->addRegistry(fg[1], p2);
	force_registry->addRegistry(fg[1], pl);
	fg.push_back(wind);

}
void ParticleSystem::P4_ejercicio1() {
	Particle* pl = new Particle(Vector3{ -11.0,30.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0,scene,gPhysics);
	pl->GetPxRigidDynamic()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	pl->setDuration(99);
	anche= new AnchoredSpringFG(1, 30, { -10,29,0 },scene,gPhysics);

	force_registry->addRegistry(anche, pl);
	fg.push_back(anche);
	_particles.push_back(pl);
}

void  ParticleSystem::P4_ejercicio3() {
	physx::PxBoxGeometry v;
	 pl = new Particle(Vector3{ -16.0,30.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0,v,scene,gPhysics);
	 pl->setDuration(99);
	pl->GetPxRigidDynamic()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	buyoancy = new BuyoancyForceGenerator(50,3,4,Vector3{10,20,0});
	force_registry->addRegistry(fg[1], pl);
	force_registry->addRegistry(buyoancy, pl);
	fg.push_back(buyoancy);
	//force_registry->addRegistry(fg[1], pl);
	_particles.push_back(pl);
}