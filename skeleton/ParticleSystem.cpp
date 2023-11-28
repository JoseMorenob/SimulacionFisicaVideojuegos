#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(const Vector3& g ) {
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
	eg = new ExplosionForceGenerator({-50,-50,-50},{90,90,90},900,1);
	Vector3 centre(-50, -50, -50);
	fg.push_back(wf);
	fg.push_back(tg);
	fg.push_back(eg);

	//genreamos particulas para luego la explosion
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
		Particle* newParticle = new Firework(Vector3(x, y, z), direction, _gravity, 2, Vector4{ 0.4f, 0.3f, 0.4f, 1.0f }, 0);
		_particles.push_back(newParticle);
		explosion_parts.push_back(newParticle);
	}
	//_firework_generator = new ParticleGenerator();
}
ParticleSystem::~ParticleSystem() {
	auto c = _particles.begin();
	while (c != _particles.end()) {
		auto v = c;
		++c;
		onParticleDeath(*v);
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
				for (auto d : p) {
					_particles.push_back(d);
					force_registry->addRegistry(gr, d);
					force_registry->addRegistry(wf, d);
				}
				onParticleDeath(*v);
			}
			else if( finish) onParticleDeath(*v);
		//fuera pantalla
		 else if ((*v)->GetPos().x > 800 || (*v)->GetPos().x < -800 || (*v)->GetPos().y < -800 || (*v)->GetPos().y>800) {
			onParticleDeath(*v);
		 }
			

	}
	
}
void ParticleSystem::generateFirework(unsigned firework_type) {
	//						GetCamera()->getEye(), GetCamera()->getDir() * 30, _gravity, 2, Vector4{ 250 , 150, 150, 1 })

	auto ne = new Firework(Vector3(GetCamera()->getEye().x-50, GetCamera()->getEye().y-50, GetCamera()->getEye().z-50), Vector3(GetCamera()->getDir().x *100, GetCamera()->getDir().y*80, GetCamera()->getDir().z*(80)), _gravity, 2, Vector4{ 0.4 , 0.3 , 0.4,1 },firework_type);
	_particles.push_back(ne);


	/*Vector3 g2(GetCamera()->getDir().x * 4, 0, GetCamera()->getDir().z * 4);
	force_registry->addRegistry(new GravityForceGenerator(g2), ne);*/
	switch (firework_type)
	{
	case 1: {
		ne->addGenerator(_firework_generator);
		/*Vector3 p = ne->GetPos();
		ne->setPos({ p.x - 40,p.y,p.z-40 });*/
		force_registry->addRegistry(fg[1], ne);
		force_registry->addRegistry(tg, ne);
		break;
	}
	case 2: {
		//ne->addGenerator(g2);
		ne->addGenerator(fire);
		
		force_registry->addRegistry(wf, ne);
		force_registry->addRegistry(gr, ne);
		break;
	}
	case 3:{
		ne->addGenerator(g3);
		force_registry->addRegistry(gr, ne);
		
		break;
	}

	default:
		break;
	}



}
ParticleGenerator* ParticleSystem::getParticleGenerator(const std::string& n) {
	if (n == "fireworkGenerator") {
		return _firework_generator;
	}
	else {
		return _firework_generator;
	}
}
void ParticleSystem::onParticleDeath(Particle* p) {
	delete(p);
	_particles.remove(p);
	



}
void ParticleSystem::createFireworkSystem() {
	_firework_generator = new GaussianParticleGenerator();
	_firework_generator->setGravity(_gravity);
	_particle_generators.push_back(_firework_generator);
	

	g2 = new UniformParticleGenerator();
	_particle_generators.push_back(g2);
	g2->setGravity(_gravity);
	g2->pos_width = Vector3(3, 3,3);
	g2->vel_width = Vector3(2, 5, 1);



	 g3 = new GaussianParticleGenerator();
	_particle_generators.push_back(g3);
	g3->setGravity(0*_gravity);
	 g3->dev_pos = Vector3(1, 1,1);
	g3->dev_vel = Vector3(60, 1, 50);

	fire = new MiniFirework_Generator();
	_particle_generators.push_back(fire);
	fire->setGravity(10*_gravity);
	fire->pos_width = Vector3(7, 3, 7);
	fire->vel_width = Vector3(16, 12, 11);
	fire->setNParticles(10);
	fire->setgenerator(g3);

}


void ParticleSystem::generateSpringDemo() {

	// First one standard spring uniting 2 particles
				//10.0, 10.0, 0.0 3, (0.0, 0.0, 0.0 3, (0.0, 0.0, 0.0 3, 0.85, 60)
								//Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color,int c
	Particle* pl = new Particle(Vector3{ -10.0,50.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0);

	Particle * p2 = new Particle(Vector3{ 10.0,50.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0);
	
	SpringForceGenerator * f1 = new SpringForceGenerator(1, 10, p2);
	force_registry->addRegistry(f1, pl);

	SpringForceGenerator * f2 = new SpringForceGenerator(1, 10, pl);
	force_registry->addRegistry(f2, p2);

	fg.push_back(f1);

	fg.push_back(f2);

	_particles.push_back(pl);

	_particles.push_back(p2);


	WindForceGenerator* wind = new WindForceGenerator(Vector3(0,100,0),{0,-30,0},{100,60,300},0.5,0);
	force_registry->addRegistry(wind, pl);
	force_registry->addRegistry(wind, p2);
	force_registry->addRegistry(fg[1], p2);
	force_registry->addRegistry(fg[1], pl);
	fg.push_back(wind);

}
void ParticleSystem::P4_ejercicio1() {
	Particle* pl = new Particle(Vector3{ -11.0,30.0,0.0 }, Vector3{ 0.0, 0.0, 0.0 }, Vector3{ 0.0, 0.0, 0.0 }, 1, Vector4{ 0.4, 0.4, 0.4,0.3 }, 0);
	anche= new AnchoredSpringFG(1, 30, { -10,29,0 });

	force_registry->addRegistry(anche, pl);
	fg.push_back(anche);
	_particles.push_back(pl);
}
