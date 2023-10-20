#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(const Vector3& g ) {
	_gravity = g;
	createFireworkSystem();
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
}
void ParticleSystem::update(double t) {
	auto c = _particles.begin();
	while (c != _particles.end()) {
		auto v = c;
		++c;
		(*v)->integrate(t);
		//std::cout << (*v)->gettimer() << "\n";
		
			if ((*v)->_type>0 && (*v)->gettimer()>(*v)->getDuration()) {
				Firework* firework = static_cast<Firework*>(*v);
				std::list<Particle*> p = firework->explode();
				for (auto d : p) {
					_particles.push_back(d);
				}
				onParticleDeath(*v);
			}
			else if( (*v)->gettimer() > (*v)->getDuration()) onParticleDeath(*v);
		//fuera pantalla
		 else if ((*v)->GetPos().x > 300 || (*v)->GetPos().x < -200 || (*v)->GetPos().y < -100 || (*v)->GetPos().y>200) {
			onParticleDeath(*v);
		 }

	}
}
void ParticleSystem::generateFirework(unsigned firework_type) {
	//						GetCamera()->getEye(), GetCamera()->getDir() * 30, _gravity, 2, Vector4{ 250 , 150, 150, 1 })

	auto ne = new Firework(GetCamera()->getEye(), GetCamera()->getDir() * 60, _gravity, 2, Vector4{ 0.4 , 0.3 , 0.4,1 },firework_type);
	_particles.push_back(ne);
	switch (firework_type)
	{
	case 1: {
		ne->addGenerator(_firework_generator);
		
		
		break;
	}
	case 2: {
		//ne->addGenerator(g2);
		ne->addGenerator(fire);
		
		
		break;
	}
	case 3:{
		ne->addGenerator(g3);
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
